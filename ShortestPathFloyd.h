#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
#include <stack>
using namespace std;
template <typename ElemType,typename WeightType>
void ShortestPathFloyd(const AdjListDirNetwork<ElemType, WeightType>& g, int** path, WeightType** dist)
{
	//step1 初始化path和dist二维数组
	for (int u = 0; u < g.GetVexNum(); u++) {
		for (int v = 0; v < g.GetVexNum(); v++) {
			if (u == v) {
				dist[u][v] = 0; path[u][v] = -1;
			}
			else {
				dist[u][v] = g.GetWeight(u, v);
				if (dist[u][v] == g.GetInfinity()) {
					path[u][v] = -1;
				}
				else {
					path[u][v] = u;
				}
			}
		}
	}
	// step2弗洛依德forforfor算法
	for (int k = 0; k < g.GetVexNum(); k++) {
		for (int i = 0; i < g.GetVexNum(); i++) {
			for (int j = 0; j < g.GetVexNum(); j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];//注意此时非k
				}
			}
		}
	}
}
template <typename ElemType, typename WeightType>
void Floyd_DisplayPathAndDist(const AdjListDirNetwork<ElemType, WeightType>& g, int** path, WeightType** dist)
{
	ElemType e1, e2; stack<int> s;
	for (int v1 = 0; v1 < g.GetVexNum(); v1++) {
		for (int v2 = 0; v2 < g.GetVexNum(); v2++) {
			if (v1 != v2) {
				g.GetElem(v1, e1); g.GetElem(v2, e2);
				if (dist[v1][v2] < g.GetInfinity()) {
					cout << "顶点 " << e1 << " 到顶点 " << e2 << " 的最短路径长度: " << dist[v1][v2] << endl;
					cout << "最短路径为: ";
					s.push(v2);int x=path[v1][v2];
					while (x!=v1) {
						s.push(x);
						x = path[v1][x]; 
					}
					s.push(v1);
					while (!s.empty()) {
						x = s.top(); s.pop();
						cout << x << "->" << " ";
					}
					cout << "End" << endl;
				}
				else {
					cout << "顶点 " << e1 << " 到顶点 " << e2 << " 不存在路径!" << endl;
				}
			}
		}
	}
}