#pragma once
#include <iostream>
#include "Assistance.h"
#include "AdjListDirNetwork.h"
#include <stack>
using namespace std;
//�Ͻ�˹�����㷨
template <typename ElemType,typename WeightType>
void ShortestPathDij(const AdjListDirNetwork<ElemType, WeightType>& g, int v0, int* path, WeightType* dist)
{
	WeightType minVal, infinity = g.GetInfinity();
	int v, u;
	//step1��ʼ��path��dist�Լ�set����
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
	g.SetTag(v0, VISITED);//�����ʼU={v0};
	//step2ѡȡ��С�߲�������������и���
	for (int i = 1; i < g.GetVexNum(); i++) {
		minVal = infinity; u = v0;
		for (v = 0; v < g.GetVexNum(); v++) {
			if (g.GetTag(v) == UNVISITED && dist[v] < minVal) {
				u = v; minVal = dist[v];//ѭ������ʱ�ҵ���ʱ��С��;
			}
		}
		g.SetTag(u, VISITED);//��u�㲢��U����
		//����
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v)) {
			if (g.GetTag(v) == UNVISITED && (minVal + g.GetWeight(u, v) < dist[v])) {		//����������������и���
				dist[v]=minVal+g.GetWeight(u,v);path[v]=u;
			}
		}
	}
}

//��ӡ������·����dist�����path����;
template <typename ElemType, typename WeightType>
void DisplayPathAndDist(const AdjListDirNetwork<ElemType, WeightType>& g, int v0, int* path, WeightType* dist)
{
	ElemType e1, e2;
	WeightType infinity = g.GetInfinity();
	g.GetElem(v0, e1);
	for (int v1 = 0; v1 < g.GetVexNum(); v1++) {
		g.GetElem(v1, e2);
		if (v1 != v0) {
			if (dist[v1] < infinity) {//�����������·��
				cout << "�Ӷ��� " << e1 << " �� " << e2 << ":" << endl;
				cout << "·������ = " << dist[v1] << endl;
				cout << " ·��:";
				stack<int> s; int v = v1;
				while (v != v0) {
					s.push(v); v = path[v];
				}
				s.push(v0);
				while (!s.empty()) {
					v = s.top();
					s.pop();
					g.GetElem(v, e2);//����e2;
					cout << e2 << "->" << " ";
				}
				cout << "End" << endl;
			}
			else
				cout << "�Ӷ��� " << e1 << " �� " << e2 << "��·��" << endl;
		}
	}
}


