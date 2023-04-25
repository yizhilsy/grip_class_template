#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
#include "TopSort.h"
#include <stack>
using namespace std;
template <typename ElemType,typename WeightType>
void Real_DFS_TopSort(const AdjListDirNetwork<ElemType, WeightType>& g)
{
	int* indegree = new int[g.GetVexNum()]; int* hasvisited = new int[g.GetVexNum()]; stack<ElemType> s;
	int v;
	for (v = 0; v < g.GetVexNum(); v++) {	//0表示未访问，1表示可以拓扑访问的顶点,-1表示受环影响不可以拓扑访问的顶点
		hasvisited[v] = 0;
	}
	for (v = 0; v < g.GetVexNum(); v++) {
		if (IsExistLoop(g, v) == true) {
			loop_erase(g, v, hasvisited);
		}
	}
	StatIndegree(g, indegree);
	for (v = 0; v < g.GetVexNum(); v++) {
		if (indegree[v] == 0) {
			real_dfs_topsort(g, hasvisited, v,s);
		}
	}
	while (!s.empty()) {
		ElemType e = s.top(); s.pop();
		cout << e << "-->";
	}
	cout << "End." << endl;
	delete[] indegree; delete[] hasvisited;
}
template <typename ElemType, typename WeightType>
void real_dfs_topsort(const AdjListDirNetwork<ElemType, WeightType>& g, int* hasvisited, int v,stack<ElemType>& s)
{
	if (hasvisited[v] != 0) {
		return;
	}
	ElemType e; g.GetElem(v, e); hasvisited[v] = 1;
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (hasvisited[u] == 0) {
			//状态更新;
			//dfs递归调用;
			real_dfs_topsort(g, hasvisited, u,s);
		}
	}
	s.push(e);
}




template <typename ElemType, typename WeightType>
void loop_erase(const AdjListDirNetwork<ElemType, WeightType>& g, int v,int* hasvisited)
{
	hasvisited[v] = -1;
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (hasvisited[u] != -1) {
			loop_erase(g, u, hasvisited);
		}
	}
}
template <typename ElemType, typename WeightType>
bool IsExistLoop(const AdjListDirNetwork<ElemType, WeightType>& g, int v)
{
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (IsExistLoop_subfunc(g, u, v) == true) {		//此时表示有回路loop
			for (int i = 0; i < g.GetVexNum(); i++) {
				g.SetTag(i, UNVISITED);
			}
			return true;
		}
		for (int i = 0; i < g.GetVexNum(); i++) {
			g.SetTag(i, UNVISITED);
		}
	}
	return false;		//不存在回路loop
}


template <typename ElemType, typename WeightType>
bool IsExistLoop_subfunc(const AdjListDirNetwork<ElemType, WeightType>& g, int v, int vend) //搜索是否存在一条从顶点v到顶点vend之间的通路，从而判断是否有回路loop
{
	g.SetTag(v, VISITED);
	if (v == vend) {	//处理搜索结果,此时搜索到环了;
		return true;
	}
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (g.GetTag(u) == UNVISITED) {
			//状态更新
			//dfs递归调用
			bool flag = IsExistLoop_subfunc(g, u, vend);
			if (flag == true) {
				return true;
			}
			//状态回溯
			g.SetTag(u, UNVISITED);
		}
	}
	return false;		//此时说明并不存在环;
}

