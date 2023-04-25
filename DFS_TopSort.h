#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
#include <stack>
using namespace std;
template <typename ElemType,typename WeightType>
void DFS_TopSort(const AdjListDirNetwork<ElemType, WeightType>& g)
{
	int* Define_Visited = new int[g.GetVexNum()];
	for (int i = 0; i < g.GetVexNum(); i++) {
		Define_Visited[i] = -1;			//-1表示未被访4问，0表示正在访问，1表示彻底访问结束
	}
	stack<ElemType> s; int v = 0;
	for (v = 0; v < g.GetVexNum(); v++) {
		if (Define_Visited[v] == -1) {
			if (dfs_topsort(g, Define_Visited, v, s) == false) {
				cout << "此有向图不存在拓扑结构!因为存在如下结构的环!" << endl;
				while (!s.empty()) {
					ElemType e = s.top(); s.pop(); cout << e << "-->";
				}
				cout << "End." << endl;
				break;
			}
		}
	}
	if (v == g.GetVexNum()) {
		cout << "该有向图采用dfs深搜策略的拓扑排序存在，如下所示!" << endl;
		while (!s.empty()) {
			ElemType e = s.top(); s.pop(); cout << e << "-->";
		}
		cout << "End." << endl;
	}
	delete[] Define_Visited;
}
template <typename ElemType, typename WeightType>
bool dfs_topsort(const AdjListDirNetwork<ElemType, WeightType>& g, int* Define_Visited,int v,stack<ElemType>& s)
{
	Define_Visited[v] = 0; ElemType e; g.GetElem(v, e);		//对于顶点v设置为正在访问状态
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (Define_Visited[u] == 0) {		//出现了环的情况
			ElemType e2; g.GetElem(u, e2); s.push(e2);		//栈中保存环的状态
			s.push(e);
			return false;
		}
		if (Define_Visited[u] == -1) {
			//状态更新
			//dfs递归调用
			bool flag=dfs_topsort(g, Define_Visited, u, s);
			if (flag == false) {		//此时搜索到了环，flag=false需要将环的结构保存
				s.push(e);
				return false;
			}
		}
	}
	Define_Visited[v] = 1;//此时表示彻底访问结束
	s.push(e);//元素压入栈中
	return true;
}