#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
using namespace std;
template <typename ElemType,typename WeightType>
void minalpath_dfs_pointtopoint(const AdjListDirNetwork<ElemType, WeightType>& g, int vs, int ve)
{
	if (vs < 0 || vs >= g.GetVexNum()) {
		throw Error("vs下标不合法!");
	}
	else if (ve < 0 || ve >= g.GetVexNum()) {
		throw Error("ve下标不合法!");
	}
	else if (ve == vs) {
		throw Error("不考虑vs==ve的情况!");
	}
	else {
		ElemType* path=new ElemType[g.GetVexNum()]; int ct = 0; int* vexpos=new int[g.GetVexNum()]; int minmin = INT_FAST32_MAX;
		minalpath_dfs(g, 0, vs, ve, minmin, path,vexpos);
		cout<<"最短长度为 : " <<minmin<< endl;
		delete[] path; delete[] vexpos;
	}
}
template <typename ElemType, typename WeightType>
void minalpath_dfs(const AdjListDirNetwork<ElemType, WeightType>& g, int ct, int v, int ve,int& minmin,ElemType* path,int* vexpos)
{
	ElemType e; g.GetElem(v, e);
	path[ct] = e; vexpos[ct] = v;
	g.SetTag(v, VISITED);
	if (v == ve) {//处理搜索结果
		int pathweight = 0;
		for (int i = 0; i <= ct; i++) {
			cout << path[i] << "-->";
		}
		cout << "End." ;
		for (int i = 0; i < ct; i++) {
			pathweight = pathweight + g.GetWeight(vexpos[i], vexpos[i + 1]);
		}
		if (pathweight < minmin) {
			minmin = pathweight;
		}
		cout << "此路径的长度为 : " << pathweight << endl;
		return;
	}
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (g.GetTag(u) == UNVISITED) {
			//状态更新
			//dfs递归调用
			minalpath_dfs(g, ct + 1, u, ve, minmin, path, vexpos);
			//状态回溯
			g.SetTag(u, UNVISITED);
		}
	}
	return;
}

