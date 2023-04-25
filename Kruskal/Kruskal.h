#include <iostream>
#include "AdjMatrixUndirNetwork.h"//引入无向网络
#include "Assistance.h"//引入辅助包
#include "MineHeap.h"//引入最小堆
#include "KruskalEdge.h"//引入克鲁斯卡尔边
#include "UFSets.h"//引入并查集
using namespace std;
template <typename ElemType,typename WeightType>
void MiniSpanTreeKruskal(const AdjMatrixUndirNetwork<ElemType, WeightType>& g)
{
	int VexNum = g.GetVexNum();
	MinHeap<KruskalEdge<ElemType, WeightType>> minheap(g.GetEdgeNum());//构建一个最大容量为无向网络图g的边数的最小堆
	ElemType* kVex, v1, v2; KruskalEdge<ElemType, WeightType> kedge;
	kVex = new ElemType[VexNum];
	for (int i = 0; i < VexNum; i++) {
		g.GetElem(i, kVex[i]);//存取无向网络图中的顶点数据
	}
	UFSets<ElemType> ufsets(kVex, VexNum);//构建无向网络图中的顶点的并查集
	for (int u = 0; u < g.GetVexNum(); u++) {//选取u小于v的边插入进最小堆
		for (int v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v)) {
			if (u < v) {
				g.GetElem(u, kedge.vertex1); g.GetElem(v, kedge.vertex2); kedge.weight=g.GetWeight(u, v);
				minheap.Insert(kedge);
			}
		}
	}
	int count = 0;//初始化已经选取的边数为0
	while ( count< VexNum - 1) {//共进行VexNum-1次操作
		minheap.DeleteTop(kedge);
		v1 = kedge.vertex1; v2 = kedge.vertex2;
		if (ufsets.Differ(v1, v2)) {
			ufsets.Union(v1, v2);//如果顶点v1,v2分属不同的等价类,则在并查集ufsets进行两者的合并
			cout << "无向边: " << "( " << v1<<" , "<< v2 << " )" << " 其权重: " << kedge.weight << endl;
			count++;
		}
	}
}
