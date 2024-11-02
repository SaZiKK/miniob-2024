#ifndef _YKMEANS_H_
#define _YKMEANS_H_

#include <cstdlib>   //for rand()
#include <vector>    //for vector<>
#include <time.h>    //for srand
#include <limits.h>  //for INT_MIN INT_MAX
#include <cmath>     //for pow, sqrt...
using namespace std;

class KMEANS {
 public:
  // * colLen 向量的维度
  // * rowLen 向量的数量
  int colLen, rowLen;

  // * Kmean 算法的簇数
  int k;

  // * 存储向量中某个维度的最大值和最小值
  typedef struct MinMax {
    float Min;
    float Max;
    MinMax(float min, float max) : Min(min), Max(max) {}
  } tMinMax;

  typedef struct Node {
    int minIndex;
    double minDist;
    Node(int idx, double dist) : minIndex(idx), minDist(dist) {}
  } tNode;

  // * 全部向量
  vector<vector<float>> dataSet;
  // * 簇中心
  vector<vector<float>> centroids;
  // * 标记某个向量应当属于哪个簇
  vector<tNode> clusterAssment;

  // * 计算距离函数指针
  double (*distEclud)(vector<float> &v1, vector<float> &v2);

  // * 获取某个维度的最大值和最小值
  tMinMax getMinMax(int idx);

  // * 随机的生成 Kmean 算法的簇的中心
  void randCent();

  // * 三种计算距离的函数，默认为第一个
  static double L2_DISTANCE(vector<float> &left_vec, vector<float> &right_vec);
  static double COSINE_DISTANCE(vector<float> &left_vec, vector<float> &right_vec);
  static double INNER_PRODUCT(vector<float> &left_vec, vector<float> &right_vec);

 public:
  KMEANS(int distance_flag, int clusterCount);
  ~KMEANS();

  // * 设置 Kmean 算法的数据集
  // * 注意，使用 Kmean 算法并不会改变原有的数据集
  void loadData(vector<vector<float>> data);

  // * 运行 Kmean 算法
  // * 将每个向量录入对应的簇中，并优化簇向量
  void kmeans();

  // * 插入向量
  void insertVec(vector<float> vec);
  // * 删除向量
  void deleteVec(vector<float> vec);
};

#endif  // _YKMEANS_H_
