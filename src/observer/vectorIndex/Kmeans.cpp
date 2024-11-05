#include "Kmeans.h"

// ! out interface

// * 创建向量索引
// * 1 设置 KMEANS 中有关向量维度、簇数、搜索时返回簇、距离函数数等参数
// * 2 将表格中已有向量录入
// * 3 运行 KMEANS 算法，生成指定数量的簇
// * 4 维护类内其他参数并生成倒排文件索引
RC KMEANS::createIndex(vector<RID_AND_VALUE> vectors, int dimension, int list, int probes, DistanceFuncType type, string index_name) {
  // * 1 设置 KMEANS 中有关向量维度、簇数、搜索时返回簇、距离函数数等参数
  this->type_ = type;
  this->lists_ = list;
  this->probes_ = probes;
  this->vecTotal_ = vectors.size();
  this->vecDimension_ = dimension;
  this->index_name_ = index_name;
  this->invertedIndex_.clear();
  for (int i = 0; i < lists_; i++) this->invertedIndex_.insert(make_pair(i, vector<int>()));

  // * 2 将表格中已有向量录入
  dataSet.clear();
  dataSet.resize(0);
  dataSet = vectors;

  // * 4 维护类内其他参数并生成倒排文件索引
  this->distanceFunc = type_ == DistanceFuncType::L2_DISTANCE       ? L2_DISTANCE
                       : type_ == DistanceFuncType::COSINE_DISTANCE ? COSINE_DISTANCE
                       : type_ == DistanceFuncType::INNER_PRODUCT   ? INNER_PRODUCT
                                                                    : L2_DISTANCE;

  // * 3 运行 KMEANS 算法，生成指定数量的簇
  kmeans();

  return RC::SUCCESS;
}

// * 插入向量
// * 1 插入最接近的簇中
// * 2 更新簇和倒排文件索引
// * 3 维护类内其他参数
/*
?   input  pair<RID, Value> vector_
?   output void/RC          rc_
*/
RC KMEANS::insertVector(RID_AND_VALUE Ivector) {
  dataSet.push_back(Ivector);
  vecTotal_++;

  // * 1 插入最接近的簇中
  // * 2 更新簇和倒排文件索引
  vector<float> vec = Ivector.second.get_vector();
  float minNum = INT16_MAX;
  int minIndex = 0;
  for (int j = 0; j < lists_; j++) {
    if (distanceFunc(vec, centroids[j]) < minNum) {
      minNum = distanceFunc(vec, centroids[j]);
      minIndex = j;
    }
  }
  invertedIndex_[minIndex].push_back(vecTotal_ - 1);

  // * 3 维护类内其他参数
  for (int i = 0; i < vecDimension_; i++) {
    this->minNum[i] = std::min(this->minNum[i], vec[i]);
    this->maxNum[i] = std::max(this->maxNum[i], vec[i]);
  }
  kmeans();
  return RC::SUCCESS;
}

// * 删除向量
// * 1 找到该向量离得最近的簇
// * 2 在该簇中线性查找找到目标向量
// * 3 删除该向量
// * 4 更新簇和倒排文件索引
// * 5 维护类内其他参数
/*
?   input  pair<RID, Value> vector_
?   output RC               rc_
*/
RC KMEANS::deleteVector(RID_AND_VALUE Dvector) {
  // * 1 找到该向量离得最近的簇
  vector<float> vec = Dvector.second.get_vector();
  float minNum = INT16_MAX;
  int minIndex = 0;
  for (int j = 0; j < lists_; j++) {
    if (distanceFunc(vec, centroids[j]) < minNum) {
      minNum = distanceFunc(vec, centroids[j]);
      minIndex = j;
    }
  }

  // * 2 在该簇中线性查找找到目标向量s
  bool find = false;
  for (int i = 0; i < (int)invertedIndex_[minIndex].size(); i++) {
    int index = invertedIndex_[minIndex][i];
    if (dataSet[index].second.get_vector() == vec) {
      find = true;
      // * 3 删除该向量
      dataSet.erase(dataSet.begin() + index);
      invertedIndex_[minIndex].erase(invertedIndex_[minIndex].begin() + i);

      // * 5 维护类内其他参数
      vecTotal_--;
    }
  }

  if (find == false) return RC::INVALID_ARGUMENT;

  // * 4 更新簇和倒排文件索引
  kmeans();
  return RC::SUCCESS;
}

// ! most most important
// * 搜索向量
// * 1 遍历全部簇，找到最近的指定数量的簇
// * 2 将这些簇中的向量放入临时集
// * 3 将临时集中的向量进行排序
// * 4 返回指定数量的 RID
// * 5 维护类内其他参数
/*
?   input  Value       para_
?   input  int         limit_
?   output vector<RID> results_
?   output RC          rc_
*/
RC KMEANS::searchVector(Value para, int limit, vector<RID> &results) {
  // * 1 遍历全部簇，找到最近的指定数量的簇
  vector<int> nearCentroids;
  for (int i = 0; i < std::min(lists_, probes_); i++) {
    float minNum = INT16_MAX;
    int minIndex = 0;
    for (int j = 0; j < lists_; j++) {
      if (distanceFunc(para.get_vector(), centroids[j]) < minNum) {
        if (find(nearCentroids.begin(), nearCentroids.end(), j) == nearCentroids.end()) {
          minNum = distanceFunc(para.get_vector(), centroids[j]);
          minIndex = j;
        }
      }
    }
    nearCentroids.push_back(minIndex);
  }

  // * 2 将这些簇中的向量放入临时集
  vector<RID_AND_VALUE> candicates;
  for (int i = 0; i < (int)nearCentroids.size(); i++) {
    for (int j = 0; j < (int)invertedIndex_[nearCentroids[i]].size(); j++) {
      candicates.push_back(dataSet[invertedIndex_[nearCentroids[i]][j]]);
    }
  }

  // * 3 将临时集中的向量进行排序
  auto comparator = [&](RID_AND_VALUE a, RID_AND_VALUE b) {
    vector<float> veca = a.second.get_vector();
    vector<float> vecb = b.second.get_vector();
    return distanceFunc(veca, para.get_vector()) < distanceFunc(vecb, para.get_vector());
  };

  // * 4 返回指定数量的 RID
  sort(candicates.begin(), candicates.end(), comparator);
  for (int i = 0; i < std::min((int)candicates.size(), limit); i++) {
    results.push_back(candicates[i].first);
  }
  return RC::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// * 将向量分到不同的簇中
void KMEANS::kmeans() {
  // * 生成簇
  this->randCent();

  // * 将向量分到对应的簇中
  for (int i = 0; i < vecTotal_; i++) {
    vector<float> vec = dataSet[i].second.get_vector();
    float minNum = INT16_MAX;
    int minIndex = 0;
    for (int j = 0; j < lists_; j++) {
      if (distanceFunc(vec, centroids[j]) < minNum) {
        minNum = distanceFunc(vec, centroids[j]);
        minIndex = j;
      }
    }
    invertedIndex_[minIndex].push_back(i);
  }

  // * 优化簇，将簇变成簇内向量的平均值
  for (int i = 0; i < lists_; i++) {
    vector<float> vec(vecDimension_, 0);
    for (int j = 0; j < (int)invertedIndex_[i].size(); j++) {
      for (int k = 0; k < vecDimension_; k++) vec[k] += dataSet[invertedIndex_[i][j]].second.get_vector()[k];
    }
    int num = (int)invertedIndex_[i].size();
    for (int j = 0; j < vecDimension_; j++) {
      if (num == 0) continue;
      centroids[i][j] = vec[j] / num;
    }
  }
}

// * 获取某个维度的最大值和最小值
pair<float, float> KMEANS::getMinMax(int idx) {
  float maxNum = INT16_MIN;
  float minNum = INT16_MAX;

  for (auto it : dataSet) {
    maxNum = std::max(maxNum, it.second.get_vector()[idx]);
    minNum = std::min(minNum, it.second.get_vector()[idx]);
  }

  return make_pair(minNum, maxNum);
}

// * 随机生成簇
void KMEANS::randCent() {
  centroids.clear();
  centroids.resize(0);

  vector<float> vec(vecDimension_, 0);
  for (int i = 0; i < lists_; i++) centroids.push_back(vec);

  srand(time(NULL));
  minNum.resize(vecDimension_);
  maxNum.resize(vecDimension_);
  for (int j = 0; j < vecDimension_; j++) {
    minNum[j] = getMinMax(j).first;
    maxNum[j] = getMinMax(j).second;
    float rangeNum = maxNum[j] - minNum[j];
    for (int i = 0; i < lists_; i++) {
      centroids[i][j] = minNum[j] + rangeNum * (rand() / (double)RAND_MAX);
    }
  }
}

// * 三种计算距离的函数，默认为第一个
double KMEANS::L2_DISTANCE(vector<float> left_vec, vector<float> right_vec) {
  float sum = 0;
  int size = (int)left_vec.size();
  for (int i = 0; i < size; i++) {
    sum += pow((left_vec[i] - right_vec[i]), 2);
  }
  sum = sqrt(sum);
  return sum;
}
double KMEANS::COSINE_DISTANCE(vector<float> left_vec, vector<float> right_vec) {
  int size = (int)left_vec.size();
  // A * B
  float sum_up = 0;
  for (int i = 0; i < size; i++) sum_up += left_vec[i] * right_vec[i];

  // A 平方和开根号
  float sum_down_left = 0;
  for (int i = 0; i < size; i++) sum_down_left += left_vec[i] * left_vec[i];
  sum_down_left = sqrt(sum_down_left);

  // B 平方和开根号
  float sum_down_right = 0;
  for (int i = 0; i < size; i++) sum_down_right += right_vec[i] * right_vec[i];
  sum_down_right = sqrt(sum_down_right);

  float sum = 1 - (sum_up) / (sum_down_left * sum_down_right);
  return sum;
}
double KMEANS::INNER_PRODUCT(vector<float> left_vec, vector<float> right_vec) {
  int size = (int)left_vec.size();
  // A * B
  float sum = 0;
  for (int i = 0; i < size; i++) sum += left_vec[i] * right_vec[i];
  return sum;
}