#ifndef _YKMEANS_H_
#define _YKMEANS_H_

#include <cstdlib>   //for rand()
#include <vector>    //for vector<>
#include <time.h>    //for srand
#include <limits.h>  //for INT_MIN INT_MAX
#include <cmath>     //for pow, sqrt...
#include <unordered_map>
#include "common/rc.h"
#include "common/value.h"
#include "storage/record/record.h"
#include "vectorIndex/distanceType.h"
using namespace std;

// * 一个 KMEANS 类对应一个向量索引
// * 简单来说，一张表格最多有一个向量索引，所以一个 Table 最多有一个 KMEANS
// * KMEANS 需要提供的接口有：
// *    创建向量索引
// *    插入向量
// *    删除向量
// *    搜索向量

class KMEANS {
 public:
  using RID_AND_VALUE = pair<RID, Value>;

 public:
  string index_name_;

  // * vecDimension 向量的维度
  // * vecTotal 向量的数量
  int vecDimension_, vecTotal_;

  // * Kmean 算法的簇数
  int lists_;
  // * Kmean 算法搜索返回的向量数
  int probes_;

  // * 倒排文件索引，key 为簇的索引，value 为属于该簇的向量的索引集合
  unordered_map<int, vector<int>> invertedIndex_;

  // * 距离函数类型
  DistanceFuncType type_;

  // * 存储向量中某个维度的最大值和最小值
  vector<float> maxNum;
  vector<float> minNum;

  // * 全部向量
  vector<RID_AND_VALUE> dataSet;
  // * 簇中心
  vector<vector<float>> centroids;

  // * 计算距离函数指针
  double (*distanceFunc)(vector<float> v1, vector<float> v2);

  // * 获取某个维度的最大值和最小值
  pair<float, float> getMinMax(int idx);

  // * 随机的生成 lists_mean 算法的簇的中心
  void randCent();

  // * 三种计算距离的函数，默认为第一个
  static double L2_DISTANCE(vector<float> left_vec, vector<float> right_vec);
  static double COSINE_DISTANCE(vector<float> left_vec, vector<float> right_vec);
  static double INNER_PRODUCT(vector<float> left_vec, vector<float> right_vec);

 public:
  KMEANS() = default;
  ~KMEANS() = default;

  // * 创建向量索引
  // * 1 设置 KMEANS 中有关向量维度、簇数、搜索时返回簇、距离函数数等参数
  // * 2 将表格中已有向量录入
  // * 3 运行 KMEANS 算法，生成指定数量的簇
  // * 4 维护类内其他参数并生成倒排文件索引
  /*
  ?   input  vector<pair<RID, Value>> vectors_
  ?   input  int                      lists_
  ?   input  int                      probes_
  ?   input  DistanceFuncType type_
  ?   output void/RC                  rc_
  */
  RC createIndex(vector<RID_AND_VALUE> vectors, int list, int probes, DistanceFuncType type, string index_name);

  // * 插入向量
  // * 1 插入最接近的簇中
  // * 2 更新簇和倒排文件索引
  // * 3 维护类内其他参数
  /*
  ?   input  pair<RID, Value> vector_
  ?   output void/RC          rc_
  */
  RC insertVector(RID_AND_VALUE Ivector);

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
  RC deleteVector(RID_AND_VALUE Dvector);

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
  RC searchVector(Value para, int limit, vector<RID> &results);

  // * 运行 Kmean 算法
  // * 将每个向量录入对应的簇中，并优化簇向量
  void kmeans();
};
#endif  // _YKMEANS_H_
