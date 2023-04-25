#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
#include "TopSort.h"
#include <queue>
#include <stack>
using namespace std;
//��Ҫ��ͳ�Ƹ���������,��"TopSort.h"�ļ����Ѿ�ʵ��
template <typename ElemType,typename WeightType>
Status CriticalPath(const AdjListDirNetwork<ElemType, WeightType>& g)
{
	int* indegree = new int[g.GetVexNum()];
	WeightType* vearly = new WeightType[g.GetVexNum()];
	WeightType* vlast = new WeightType[g.GetVexNum()];
	queue<int> q; stack<int> s;
	int ee, el, u, v, count = 0;
	ElemType e1, e2;
	for (v = 0; v < g.GetVexNum(); v++) {
		vearly[v] = 0;
	}
	StatIndegree(g, indegree);
	for (v = 0; v < g.GetVexNum(); v++) {
		if (indegree[v] == 0) {
			q.push(v);
		}
	}
	//��������
	while (!q.empty()) {
		u = q.front(); q.pop();
		s.push(u);//��������������
		count++;
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v)) {
			indegree[v]--;
			if (indegree[v] == 0) {
				q.push(v);
			}
			if (vearly[u] + g.GetWeight(u, v) > vearly[v]) {
				vearly[v] = vearly[u] + g.GetWeight(u, v);
			}
		}
	}
	if (count != g.GetVexNum()) {//��ǰ�ж��Ƿ�������������
		delete[] indegree; delete[] vearly; delete[] vlast;
		cout << "���������·,���Ϸ�!" << endl;
		return FAIL;
	}
	u = s.top(); s.pop();
	for (v = 0; v < g.GetVexNum(); v++) {
		vlast[v] = vearly[u];
	}
	while (!s.empty()) {
		u = s.top(); s.pop();
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v)) {
			if (vlast[v] - g.GetWeight(u, v) < vlast[u]) {
				vlast[u] = vlast[v] - g.GetWeight(u, v);
			}
		}
	}
	for (u = 0; u < g.GetVexNum(); u++) {
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v)) {
			ee = vearly[u]; el = vlast[v] - g.GetWeight(u, v);
			if (ee == el) {
				g.GetElem(u, e1); g.GetElem(v, e2);
				cout << "< " << e1 << " -> " << e2 <<" >" << " ��һ���ؼ�·��" << endl;
			}
		}
	}
	delete[] indegree; delete[] vearly; delete[] vlast;
	return SUCCESS;
}

