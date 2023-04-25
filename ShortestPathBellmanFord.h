#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
#include <stack>
using namespace std;
template <typename ElemType,typename WeightType>
void ShortestPathBellmanFord(const AdjListDirNetwork<ElemType, WeightType>& g, int v0, int* path, WeightType* dist)
{
	WeightType minVal, infinity = g.GetInfinity();
	int v, u, vexNum = g.GetVexNum();
	WeightType* distTemp = new WeightType[vexNum];
	//step1 ��ʼ��path��set,dist����
	for (v = 0; v < g.GetVexNum(); v++) {
		//������ģ���е�tag����䵱set����Ĺ���
		g.SetTag(v, UNVISITED);
		if (v == v0) {
			path[v] = -1; dist[v] = 0; continue;
		}
		else {
			dist[v] = g.GetWeight(v0, v);
			if (dist[v] == infinity) {
				path[v] = -1;
			}
			else {
				path[v] = v0;
			}
		}
	}
	for (int k = 2; k < vexNum; k++) {
		//���Ƶ�distTemp������
		for (v = 0; v < vexNum; v++) {
			distTemp[v] = dist[v];
		}
		for (u = 0; u < vexNum; u++) {
			if (u != v0) {
				for (v = 0; v < vexNum; v++) {
					if ((v != u) && (distTemp[u] > dist[v] + g.GetWeight(v, u))) {//����һ�����ϸ��µĹ���,ѭ��������ɸѡ����С·���Լ�path[u]��ֵ
						distTemp[u]=dist[v]+g.GetWeight(v,u);
						path[u]=v;
					}
				}
			}
		}
		for (v = 0; v < vexNum; v++) {
			dist[v] = distTemp[v];
		}
	}
}
