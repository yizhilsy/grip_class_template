#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
#include "Assistance.h"
using namespace std;
template <typename ElemType,typename WeightType>
void StatIndegree(const AdjListDirNetwork<ElemType, WeightType>& g, int* indegree)
{
	for (int i = 0; i < g.GetVexNum(); i++) {
		indegree[i] = 0;
	}
	for (int v = 0; v < g.GetVexNum(); v++) {
		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
			indegree[u]++;
		}
	}
}
template <typename ElemType, typename WeightType>
Status TopSort(const AdjListDirNetwork<ElemType, WeightType>& g)
{
	int* indegree = new int[g.GetVexNum()];
	int v, u, count = 0; int top = -1;
	StatIndegree(g, indegree);
	for (v = 0; v < g.GetVexNum(); v++) {
		if (indegree[v] == 0) {
			indegree[v] = top; top = v;
		}
	}
	while (top != -1) {
		int temp = top;
		ElemType e; g.GetElem(top, e);
		top = indegree[top]; count++;
		cout << e << "->";
		for (u = g.FirstAdjVex(temp); u != -1; u = g.NextAdjVex(temp, u)) {
			indegree[u]--;
			if (indegree[u] == 0) {
				indegree[u] = top;
				top = u;
			}
		}
	}
	cout << "->End" << endl;
	delete [] indegree;
	return (count == g.GetVexNum() ? SUCCESS : FAIL);
}