#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
using namespace std;
template <typename ElemType,typename WeightType>
void minalpath_dfs_pointtopoint(const AdjListDirNetwork<ElemType, WeightType>& g, int vs, int ve)
{
	if (vs < 0 || vs >= g.GetVexNum()) {
		throw Error("vs�±겻�Ϸ�!");
	}
	else if (ve < 0 || ve >= g.GetVexNum()) {
		throw Error("ve�±겻�Ϸ�!");
	}
	else if (ve == vs) {
		throw Error("������vs==ve�����!");
	}
	else {
		ElemType* path=new ElemType[g.GetVexNum()]; int ct = 0; int* vexpos=new int[g.GetVexNum()]; int minmin = INT_FAST32_MAX;
		minalpath_dfs(g, 0, vs, ve, minmin, path,vexpos);
		cout<<"��̳���Ϊ : " <<minmin<< endl;
		delete[] path; delete[] vexpos;
	}
}
template <typename ElemType, typename WeightType>
void minalpath_dfs(const AdjListDirNetwork<ElemType, WeightType>& g, int ct, int v, int ve,int& minmin,ElemType* path,int* vexpos)
{
	ElemType e; g.GetElem(v, e);
	path[ct] = e; vexpos[ct] = v;
	g.SetTag(v, VISITED);
	if (v == ve) {//�����������
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
		cout << "��·���ĳ���Ϊ : " << pathweight << endl;
		return;
	}
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (g.GetTag(u) == UNVISITED) {
			//״̬����
			//dfs�ݹ����
			minalpath_dfs(g, ct + 1, u, ve, minmin, path, vexpos);
			//״̬����
			g.SetTag(u, UNVISITED);
		}
	}
	return;
}

