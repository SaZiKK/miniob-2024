#include "Kmeans.h"

// * 获取某个维度的最大值和最小值
KMEANS::MinMax KMEANS::getMinMax(int idx) {
  float min, max;
  dataSet[0].at(idx) > dataSet[1].at(idx) ? (max = dataSet[0].at(idx), min = dataSet[1].at(idx))
                                          : (max = dataSet[1].at(idx), min = dataSet[0].at(idx));

  for (int i = 2; i < rowLen; i++) {
    if (dataSet[i].at(idx) < min)
      min = dataSet[i].at(idx);
    else if (dataSet[i].at(idx) > max)
      max = dataSet[i].at(idx);
    else
      continue;
  }

  tMinMax tminmax(min, max);
  return tminmax;
}

// * 随机的生成 Kmean 算法的簇的中心
void KMEANS::randCent() {
  // ? 将簇数组初始化为若干个零向量
  centroids.clear();
  vector<float> vec(colLen, 0);
  for (int i = 0; i < k; i++) centroids.push_back(vec);

  // ? 在每个维度随机生成一个值作为簇的值，随机生成的值夹在该维度最大值最小值之间
  srand(time(NULL));
  for (int j = 0; j < colLen; j++) {
    tMinMax tminmax = getMinMax(j);
    float rangeIdx = tminmax.Max - tminmax.Min;
    for (int i = 0; i < k; i++) {
      centroids[i].at(j) = tminmax.Min + rangeIdx * (rand() / (double)RAND_MAX);
    }
  }
}

// * 三种计算距离的函数，默认为第一个
double KMEANS::L2_DISTANCE(vector<float> &left_vec, vector<float> &right_vec) {
  float sum = 0;
  int size = (int)left_vec.size();
  for (int i = 0; i < size; i++) {
    sum += pow((left_vec[i] - right_vec[i]), 2);
  }
  sum = sqrt(sum);
  return sum;
}
double KMEANS::COSINE_DISTANCE(vector<float> &left_vec, vector<float> &right_vec) {
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
double KMEANS::INNER_PRODUCT(vector<float> &left_vec, vector<float> &right_vec) {
  int size = (int)left_vec.size();
  // A * B
  float sum = 0;
  for (int i = 0; i < size; i++) sum += left_vec[i] * right_vec[i];
  return sum;
}

KMEANS::KMEANS(int distance_flag, int clusterNum) {
  k = clusterNum;
  colLen = 0;
  rowLen = 0;
  distEclud = distance_flag == 1 ? L2_DISTANCE : distance_flag == 2 ? COSINE_DISTANCE : distance_flag == 3 ? INNER_PRODUCT : L2_DISTANCE;
}

KMEANS::~KMEANS() {}

// * 设置 Kmean 算法的数据集
// * 注意，使用 Kmean 算法并不会改变原有的数据集
void KMEANS::loadData(vector<vector<float>> data) {
  this->dataSet = data;
  this->rowLen = data.capacity();
  this->colLen = data.at(0).capacity();
}

// * 运行 Kmean 算法
void KMEANS::kmeans() {
  // initial clusterAssment
  this->clusterAssment.clear();
  tNode node(-1, -1);
  for (int i = 0; i < rowLen; i++) clusterAssment.push_back(node);

  // initial cluster center
  this->randCent();

  bool clusterChanged = true;
  // the termination condition can also be the loops less than	some number such as 1000
  while (clusterChanged) {
    clusterChanged = false;
    // ? 遍历全部向量
    for (int i = 0; i < rowLen; i++) {
      int minIndex = -1;
      double minDist = INT_MAX;
      // ? 遍历每个簇，找到最近的那个（通过距离函数算出）
      for (int j = 0; j < k; j++) {
        double distJI = distEclud(centroids[j], dataSet[i]);
        if (distJI < minDist) {
          minDist = distJI;
          minIndex = j;
        }
      }
      // ? 记录该向量属于的簇
      if (clusterAssment[i].minIndex != minIndex) {
        clusterChanged = true;
        clusterAssment[i].minIndex = minIndex;
        clusterAssment[i].minDist = minDist;
      }
    }

    // ? 遍历更新全部簇的中心向量
    for (int cent = 0; cent < k; cent++) {
      vector<float> vec(colLen, 0);
      int cnt = 0;
      for (int i = 0; i < rowLen; i++) {
        if (clusterAssment[i].minIndex == cent) {
          ++cnt;
          // sum of two vectors
          for (int j = 0; j < colLen; j++) {
            vec[j] += dataSet[i].at(j);
          }
        }
      }

      // ? 将向量的簇改为属于该簇的全部向量的均值
      for (int i = 0; i < colLen; i++) {
        if (cnt != 0) vec[i] /= cnt;
        centroids[cent].at(i) = vec[i];
      }
    }
  }
}

void KMEANS::insertVec(vector<float> vec) {}
void KMEANS::deleteVec(vector<float> vec) {}
