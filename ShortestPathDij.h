#pragma once
#include <iostream>
#include "Assistance.h"
#include "AdjListDirNetwork.h"
#include <stack>
using namespace std;
//迪杰斯特拉算法
template <typename ElemType,typename WeightType>
void ShortestPathDij(const AdjListDirNetwork<ElemType, WeightType>& g, int v0, int* path, WeightType* dist)
{
	WeightType minVal, infinity = g.GetInfinity();
	int v, u;
	//step1初始化path和dist以及set数组
	for (v = 0; v < g.GetVexNum(); v++) {
		//借助类模板中的tag数组充当set数组的功能
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
	g.SetTag(v0, VISITED);//代表初始U={v0};
	//step2选取最小边并对于其他点进行更新
	for (int i = 1; i < g.GetVexNum(); i++) {
		minVal = infinity; u = v0;
		for (v = 0; v < g.GetVexNum(); v++) {
			if (g.GetTag(v) == UNVISITED && dist[v] < minVal) {
				u = v; minVal = dist[v];//循环结束时找到此时最小边;
			}
		}
		g.SetTag(u, VISITED);//将u点并入U集合
		//更新
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v)) {
			if (g.GetTag(v) == UNVISITED && (minVal + g.GetWeight(u, v) < dist[v])) {		//满足更新条件，进行更新
				dist[v]=minVal+g.GetWeight(u,v);path[v]=u;
			}
		}
	}
}

//打印求出最短路径的dist数组和path数组;
template <typename ElemType, typename WeightType>
void DisplayPathAndDist(const AdjListDirNetwork<ElemType, WeightType>& g, int v0, int* path, WeightType* dist)
{
	ElemType e1, e2;
	WeightType infinity = g.GetInfinity();
	g.GetElem(v0, e1);
	for (int v1 = 0; v1 < g.GetVexNum(); v1++) {
		g.GetElem(v1, e2);
		if (v1 != v0) {
			if (dist[v1] < infinity) {//表明存在最短路径
				cout << "从顶点 " << e1 << " 到 " << e2 << ":" << endl;
				cout << "路径长度 = " << dist[v1] << endl;
				cout << " 路径:";
				stack<int> s; int v = v1;
				while (v != v0) {
					s.push(v); v = path[v];
				}
				s.push(v0);
				while (!s.empty()) {
					v = s.top();
					s.pop();
					g.GetElem(v, e2);//复用e2;
					cout << e2 << "->" << " ";
				}
				cout << "End" << endl;
			}
			else
				cout << "从顶点 " << e1 << " 到 " << e2 << "无路径" << endl;
		}
	}
}


