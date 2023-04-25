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
		Define_Visited[i] = -1;			//-1��ʾδ����4�ʣ�0��ʾ���ڷ��ʣ�1��ʾ���׷��ʽ���
	}
	stack<ElemType> s; int v = 0;
	for (v = 0; v < g.GetVexNum(); v++) {
		if (Define_Visited[v] == -1) {
			if (dfs_topsort(g, Define_Visited, v, s) == false) {
				cout << "������ͼ���������˽ṹ!��Ϊ�������½ṹ�Ļ�!" << endl;
				while (!s.empty()) {
					ElemType e = s.top(); s.pop(); cout << e << "-->";
				}
				cout << "End." << endl;
				break;
			}
		}
	}
	if (v == g.GetVexNum()) {
		cout << "������ͼ����dfs���Ѳ��Ե�����������ڣ�������ʾ!" << endl;
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
	Define_Visited[v] = 0; ElemType e; g.GetElem(v, e);		//���ڶ���v����Ϊ���ڷ���״̬
	for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) {
		if (Define_Visited[u] == 0) {		//�����˻������
			ElemType e2; g.GetElem(u, e2); s.push(e2);		//ջ�б��滷��״̬
			s.push(e);
			return false;
		}
		if (Define_Visited[u] == -1) {
			//״̬����
			//dfs�ݹ����
			bool flag=dfs_topsort(g, Define_Visited, u, s);
			if (flag == false) {		//��ʱ�������˻���flag=false��Ҫ�����Ľṹ����
				s.push(e);
				return false;
			}
		}
	}
	Define_Visited[v] = 1;//��ʱ��ʾ���׷��ʽ���
	s.push(e);//Ԫ��ѹ��ջ��
	return true;
}