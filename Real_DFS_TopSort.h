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
	for (v = 0; v < g.GetVexNum(); v++) {	//0��ʾδ���ʣ�1��ʾ�������˷��ʵĶ���,-1��ʾ�ܻ�Ӱ�첻�������˷��ʵĶ���
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
			//״̬����;
			//dfs�ݹ����;
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
		if (IsExistLoop_subfunc(g, u, v) == true) {		//��ʱ��ʾ�л�·loop
			for (int i = 0; i < g.GetVexNum(); i++) {
				g.SetTag(i, UNVISITED);
			}
			return true;
		}
		for (int i = 0; i < g.GetVexNum(); i++) {
			g.SetTag(i, UNVISITED);
		}
	}
	return false;		//�����ڻ�·loop
}


template <typename ElemType, typename WeightType>
bool IsExistLoop_subfunc(const AdjListDirNetwork<ElemType, WeightType>& g, int v, int vend) //�����Ƿ����һ���Ӷ���v������vend֮���ͨ·���Ӷ��ж��Ƿ��л�·loop
{
	g.SetTag(v, VISITED);
	if (v == vend) {	//�����������,��ʱ����������;
		return true;
	}
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (g.GetTag(u) == UNVISITED) {
			//״̬����
			//dfs�ݹ����
			bool flag = IsExistLoop_subfunc(g, u, vend);
			if (flag == true) {
				return true;
			}
			//״̬����
			g.SetTag(u, UNVISITED);
		}
	}
	return false;		//��ʱ˵���������ڻ�;
}

