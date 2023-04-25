#pragma once
#include <iostream>
#include "AdjListDirNetwork.h"
#include <vector>
#include "TopSort.h"
#include <stack>
using namespace std;
template <typename ElemType, typename WeightType>
void DpLongestPath(const AdjListDirNetwork<ElemType, WeightType>& g)
{
	int* topsort = new int[g.GetVexNum()];//存储的是拓扑排序顶点的序号
	WeightType * dp = new WeightType[g.GetVexNum()];
	WeightType infinity = g.GetInfinity();
	int* path = new int[g.GetVexNum()];
	int* result = new int[g.GetVexNum()];
	DPTopSort(g, topsort);
	int imax = 0; int imaxpos = 0;
	for (int u = 0; u < g.GetVexNum(); u++) {
		for (int v = 0; v < g.GetVexNum(); v++) {
			dp[v] = 0;
		}
		dp[topsort[u]] = 0; path[topsort[u]] = -1;
		for (int i = u + 1; i < g.GetVexNum(); i++) {
			for (int j = 0; j <= i - 1; j++) {
				if ((g.GetWeight(topsort[j], topsort[i]) != infinity) && (dp[topsort[j]] + g.GetWeight(topsort[j], topsort[i]) > dp[topsort[i]])) {
					dp[topsort[i]] = dp[topsort[j]] + g.GetWeight(topsort[j], topsort[i]);
					path[topsort[i]] = topsort[j];
				}
			}
		}
		int max = dp[topsort[u]]; int maxpos = topsort[u];
		for (int i = 0; i < g.GetVexNum(); i++) {
			if (max < dp[i]) {
				max = dp[i]; maxpos = i;
			}
		}
		if (imax < max) {
			imax = max; imaxpos = maxpos;
			for (int i = 0; i < g.GetVexNum(); i++) {
				result[i] = path[i];
			}
		}
	}
	cout << "最长路径长度为: " << imax << " 最长路径为: " << endl;
	stack<int> s;
	while (imaxpos != -1) {
		s.push(imaxpos);
		imaxpos = result[imaxpos];
	}
	while (!s.empty()) {
		ElemType e;
		int x = s.top(); s.pop();
		g.GetElem(x, e);
		cout << e << "-->";
	}
	cout << "End." << endl;
	delete[] topsort; delete[] dp; delete[] path; delete[] result;
}
template <typename ElemType, typename WeightType>
Status DPTopSort(const AdjListDirNetwork<ElemType, WeightType>& g,int* topsort)
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
		int temp = top; topsort[count] = top;
		ElemType e; g.GetElem(top, e);
		top = indegree[top]; count++;
		//cout << e << "->";
		for (u = g.FirstAdjVex(temp); u != -1; u = g.NextAdjVex(temp, u)) {
			indegree[u]--;
			if (indegree[u] == 0) {
				indegree[u] = top;
				top = u;
			}
		}
	}
	//cout << "->End." << endl;
	delete[] indegree;
	return (count == g.GetVexNum() ? SUCCESS : FAIL);
}
//使用dfs暴搜所有路径的方法
template <typename ElemType,typename WeightType>
void Longest_Path(const AdjListDirNetwork<ElemType, WeightType>& g)
{
	int max = -1000; vector<ElemType> path; vector<ElemType> result;
	for (int u = 0; u < g.GetVexNum(); u++) {
		dfs_Longest_Path(g, u, path, result,max);
		path.clear(); g.SetTag(u, UNVISITED);
	}
	cout<<"该有向无环图中长度最长的路径长为: "<<max<<" 其路径为:" << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << "-->";
	}
	cout << "End." << endl;
}
template <typename ElemType, typename WeightType>
void dfs_Longest_Path(const AdjListDirNetwork<ElemType, WeightType>& g, int s,vector<ElemType>& path,vector<ElemType>& result,int& max)
{
	ElemType e; g.GetElem(s, e); path.push_back(e); g.SetTag(s, VISITED);//访问图中顶点
	int flagcount = 0;
	for (int u = g.FirstAdjVex(s); u != -1; u = g.NextAdjVex(s, u)) {
		if (g.GetTag(u) == UNVISITED) {
			flagcount++;
			//状态更新
			//dfs递归函数调用
			dfs_Longest_Path(g, u, path, result, max);
			//状态回溯
			g.SetTag(u, UNVISITED); path.pop_back();
		}
	}
	if (flagcount == 0) {			//表明此时搜索到最深的情况了,需要处理
		int longest = 0; int len = 0; vector<ElemType> temp; vector<ElemType> heremaxlongpath;
		for (int i = 1; i < path.size(); i++) {
			len = 0; temp.clear(); int j;
			for (j = 0; j < i; j++) {
				int posu, posv;
				posu = g.GetOrder(path[j]); posv = g.GetOrder(path[j + 1]);
				len = len + g.GetWeight(posu, posv);temp.push_back(path[j]);
			}
			temp.push_back(path[j]);
			if (len > longest) {
				longest = len; heremaxlongpath = temp;
			}
		}
		if (longest > max) {
			max = longest;
			result = heremaxlongpath;
		}
	}
}