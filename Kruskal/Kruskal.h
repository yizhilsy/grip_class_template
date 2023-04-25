#include <iostream>
#include "AdjMatrixUndirNetwork.h"//������������
#include "Assistance.h"//���븨����
#include "MineHeap.h"//������С��
#include "KruskalEdge.h"//�����³˹������
#include "UFSets.h"//���벢�鼯
using namespace std;
template <typename ElemType,typename WeightType>
void MiniSpanTreeKruskal(const AdjMatrixUndirNetwork<ElemType, WeightType>& g)
{
	int VexNum = g.GetVexNum();
	MinHeap<KruskalEdge<ElemType, WeightType>> minheap(g.GetEdgeNum());//����һ���������Ϊ��������ͼg�ı�������С��
	ElemType* kVex, v1, v2; KruskalEdge<ElemType, WeightType> kedge;
	kVex = new ElemType[VexNum];
	for (int i = 0; i < VexNum; i++) {
		g.GetElem(i, kVex[i]);//��ȡ��������ͼ�еĶ�������
	}
	UFSets<ElemType> ufsets(kVex, VexNum);//������������ͼ�еĶ���Ĳ��鼯
	for (int u = 0; u < g.GetVexNum(); u++) {//ѡȡuС��v�ı߲������С��
		for (int v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v)) {
			if (u < v) {
				g.GetElem(u, kedge.vertex1); g.GetElem(v, kedge.vertex2); kedge.weight=g.GetWeight(u, v);
				minheap.Insert(kedge);
			}
		}
	}
	int count = 0;//��ʼ���Ѿ�ѡȡ�ı���Ϊ0
	while ( count< VexNum - 1) {//������VexNum-1�β���
		minheap.DeleteTop(kedge);
		v1 = kedge.vertex1; v2 = kedge.vertex2;
		if (ufsets.Differ(v1, v2)) {
			ufsets.Union(v1, v2);//�������v1,v2������ͬ�ĵȼ���,���ڲ��鼯ufsets�������ߵĺϲ�
			cout << "�����: " << "( " << v1<<" , "<< v2 << " )" << " ��Ȩ��: " << kedge.weight << endl;
			count++;
		}
	}
}
