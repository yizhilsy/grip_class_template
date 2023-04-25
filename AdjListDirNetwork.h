#pragma once
#include <iostream>
#include "AdjListDirNetworkVex.h"
#include "LinkQueue.h"
#include <vector>
using namespace std;
//采用有向网标准的类模板
template <typename ElemType,typename WeightType>
class AdjListDirNetwork
{
public:
	int vexNum; int vexMaxNum; int arcNum;
	AdjListDirNetworkVex<ElemType, WeightType>* vexTable;
	mutable Status* tag;
	WeightType infinity;
public:
	//构造,析构函数声明
	AdjListDirNetwork(int vertexMaxNum = DEFAULT_SIZE,WeightType infinit = (WeightType)DEFAULT_INFINITY);
	AdjListDirNetwork(ElemType* es, int vertexNum, int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	virtual ~AdjListDirNetwork();
	//功能函数声明
	int GetOrder(ElemType& e) const;
	void testprint() const;
	void InsertArc(int v1, int v2, WeightType w);	// 插入从顶点为v1到v2、权重为w的边;
	void InsertVex(const ElemType& e);				// 插入一个顶点，其元素值为e;
	void DeleteArc(int v1, int v2);					// 删除v1->v2的有向边;
	void DeleteVex(const ElemType& e);							// 删除有向网中顶点v;
	void Clear();									// 清空有向网;
	void IsEmpty() const;							// 判断有向网是否为空;
	Status GetElem(int v, ElemType& d) const;		// 求顶点的元素值	
	Status SetElem(int v, const ElemType& d);		// 设置顶点的元素值
	int FirstAdjVex(int v) const;					// 求有向网中顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;			// 求有向网中顶点v1的相对于v2的下一个邻接点
	WeightType GetWeight(int v1, int v2) const;		// 求从顶点为v1到v2的边的权值
	void SetWeight(int v1, int v2, WeightType w);	// 设置从顶点为v1到v2的边的权值
	int GetVexNum() const;							// 求有向网的顶点个数			 
	int GetArcNum() const;							// 求有向网的边数个数
	void SetTag(int v,Status val) const;			// 设置有向网中顶点的访问情况
	Status GetTag(int v) const;						// 获取有向网中顶点的访问情况
	WeightType GetInfinity() const;					// 获取有向网中无穷大的值
};
template <typename ElemType,typename WeightType>
void IsConnected(const AdjListDirNetwork<ElemType, WeightType>& g, ElemType i, ElemType j)
{
	ElemType path[DEFAULT_SIZE]; int ct = 0; int posi = g.GetOrder(i);
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, UNVISITED);
	}
	cout << "Used DFS Search define whether connected..." << endl;
	if (DFS_IsConnected(g, posi, j) == true) {
		cout << "存在从 " << i << " 到 " << j << " 的路径!" << endl;
	}
	else {
		cout << "并不存在从 " << i << " 到 " << j << " 的路径!" << endl;
	}
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, UNVISITED);
	}
	//使用深度优先搜索策略判断始点i到终点j之间存在的所有路径,
	cout<<"从 "<<i<<" 到 "<<j<<" 的所有路径是:" << endl;
	DFS_AllPath(g, posi, ct, path,j);
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, UNVISITED);
	}
	cout << "Used BFS Search define whether connected..." << endl;
	if (BFS_IsConnected(g, posi, j) == true) {
		cout << "存在从 " << i << " 到 " << j << " 的路径!" << endl;
	}
	else {
		cout << "并不存在从 " << i << " 到 " << j << " 的路径!" << endl;
	}
}
template <typename ElemType,typename WeightType>
bool BFS_IsConnected(const AdjListDirNetwork<ElemType, WeightType>& g, int v, ElemType result)
{
	int ct = 0;ElemType e; g.GetElem(v, e); 
	g.SetTag(v, VISITED);
	if (e == result) {
		return true;
	}
	LinkQueue<int> linkqueue; linkqueue.EnQueue(v);
	while (!linkqueue.IsEmpty()) {
		int u; linkqueue.DelQueue(u);
		for (int w = g.FirstAdjVex(u); w != -1; w = g.NextAdjVex(u, w)) {
			if (g.GetTag(w) == UNVISITED) {
				linkqueue.EnQueue(w);
				g.SetTag(w, VISITED);
				g.GetElem(w, e);
				if (e == result) {
					return true;
				}
			}
		}
	}
	return false;//表明与顶点result之间不连通
}
template <typename ElemType,typename WeightType>
bool DFS_IsConnected(const AdjListDirNetwork<ElemType, WeightType>& g, int v, ElemType result)
{
	ElemType e; g.GetElem(v, e); g.SetTag(v, VISITED);
	if (e == result) {//处理搜索结果
		return true;
	}
	bool flag=false;
	
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w)) {
		if (g.GetTag(w) == UNVISITED) {
			flag=DFS_IsConnected(g, w, result);
			if (flag == true) {
				return flag;//找到终点，逐层递归返回
			}
		}
	}
	return flag;
}
template<typename ElemType, typename WeightType>
void DFS_AllPath(const AdjListDirNetwork<ElemType, WeightType>& g, int v, int ct,ElemType* path,ElemType result)
{
	ElemType e;
	g.GetElem(v, e);
	path[ct] = e;//保存此时搜索到的路径
	g.SetTag(v, VISITED);//访问结点并置为已访问
	if (e == result) {//处理搜索结果:表示此时已经找到了i->j的一条通路
		for (int i = 0; i <= ct; i++) {
			cout << path[i] << "--->";
		}
		cout <<"END." << endl; return;
	}
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w)) {//递归深度优先遍历
		if (g.GetTag(w) == UNVISITED) {
			//状态更新
			//DFS深度搜索递归调用
			DFS_AllPath(g, w, ct+1,path,result);
			//搜索全部可能路径需要状态回溯
			g.SetTag(w, UNVISITED);
		}
	}
}
//深度优先搜索DFS算法
template<typename ElemType,typename WeightType>
void DFS(const AdjListDirNetwork<ElemType, WeightType>& g, int v,void (*Visit)(const ElemType&))
{
	ElemType e;
	g.GetElem(v, e);
	(*Visit)(e);
	g.SetTag(v, VISITED);//访问结点并置为已访问
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w)) {//递归深度优先遍历
		if (g.GetTag(w) == UNVISITED) {
			DFS(g, w, Visit);
		}
	}
}
template<typename ElemType, typename WeightType>
void DFSTraverse(const AdjListDirNetwork<ElemType, WeightType>& g, void (*Visit)(const ElemType&))
{
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, UNVISITED);
	}
	int ct = 0;
	for (int i = 0; i < g.GetVexNum(); i++) {
		if (g.GetTag(i) == UNVISITED) {
			ct++;
			DFS(g, i, Visit);
		}
	}
	cout << endl;
	cout << "该有向网共有 " << ct << " 个连通分量" << endl;
}
template <typename ElemType,typename WeightType>
void BFS(const AdjListDirNetwork<ElemType, WeightType>& g,int v,void(*Visit)(const ElemType&))
{
	//访问结点
	ElemType e;
	g.GetElem(v, e);
	(*Visit)(e);
	g.SetTag(v, VISITED);
	LinkQueue<int> lq; lq.EnQueue(v); int u, w;
	while (!lq.IsEmpty()) {
		lq.DelQueue(u);
		for (w = g.FirstAdjVex(u); w != -1; w = g.NextAdjVex(u, w)) {
			if (g.GetTag(w) == UNVISITED) {
				g.GetElem(w, e);//复用e接受结点元素值,访问结点
				(*Visit)(e);
				g.SetTag(w, VISITED);
				lq.EnQueue(w);
			}
		}
	}
	cout << endl;
}
template <typename ElemType, typename WeightType>
void BFSTraverse(const AdjListDirNetwork<ElemType, WeightType>& g, void(*Visit)(const ElemType&))
{
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, UNVISITED);
	}
	int ct = 0;
	for (int i = 0; i < g.GetVexNum(); i++) {
		if (g.GetTag(i) == UNVISITED) {
			ct++;
			BFS(g, i, Visit);
		}
	}
	cout << "该有向网共有 " << ct << " 个连通分量" << endl;
}
template <typename ElemType>
void VisitNode(const ElemType& e)
{
	cout << e << " ";
}
template <typename ElemType, typename WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(int vertexMaxNum, WeightType infinit)
{
	vexMaxNum = vertexMaxNum; vexNum = 0; arcNum = 0;
	vexTable = new AdjListDirNetworkVex<ElemType, WeightType>[vexMaxNum];
	tag = new Status[vexMaxNum]; this->infinity = infinit;
}
template <typename ElemType, typename WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(ElemType* es, int vertexNum, int vertexMaxNum,WeightType infinit)
{
	vexMaxNum = vertexMaxNum; vexNum = vertexNum; this->infinity = infinit; arcNum = 0;
	vexTable = new AdjListDirNetworkVex<ElemType, WeightType>[vexMaxNum];
	tag = new Status[vexMaxNum];
	for (int i = 0; i < vertexNum; i++) {
		vexTable[i].data = es[i];
	}
	for (int i = 0; i < vertexNum; i++) {
		tag[i] = UNVISITED;
	}
}
template <typename ElemType, typename WeightType>
AdjListDirNetwork<ElemType, WeightType>::~AdjListDirNetwork()
{
	for (int i = 0; i < vexNum; i++) {
		AdjListDirNetworkArc<WeightType>* temp;
		AdjListDirNetworkArc<WeightType>* p = vexTable[i].firstarc;
		while (p != NULL) {
			temp = p->nextarc; delete p; p = temp;
		}
	}
	delete[] vexTable; delete[] tag;
}
template <typename ElemType, typename WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetOrder(ElemType& e) const
{
	for (int i = 0; i < vexNum; i++) {
		if (vexTable[i].data == e) {
			return i;
		}
	}
	return -1;//表示没找到
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::testprint() const
{
	cout << "VexTable:" << endl;
	for (int i = 0; i < vexNum; i++) {
		cout <<i<<"th : " << "顶点:" << vexTable[i].data << "  ";
		AdjListDirNetworkArc<WeightType>* p = vexTable[i].firstarc;
		while (p != NULL) {
			cout<<"( "<<i<<"-->" << p->adjVex <<" ,weight: " << p->weight << " )" << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
	cout << "该有向网共有: " << this->vexNum << " 个结点; 该有向网共有: " << this->arcNum << " 条有向边;"<<endl;
	cout << "该有向网的顶点访问情况:" << endl;
	for (int i = 0; i < vexNum; i++) {
		if (tag[i] == UNVISITED) {
			cout << i << "th " << "UNVISITED" << " ";
		}
		else {
			cout << i << "th " << "VISITED" << " ";
		}
		
	}
	cout << endl;
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)//v1->v2有向边,权重为w;
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("不存在以v1为下标的点......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("不存在以v2为下标的点......");
	}
	else if (v1 == v2) {
		throw Error("该图不允许有环......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = vexTable[v1].firstarc;
		while (p != NULL) {
			if (p->adjVex == v2) {
				throw Error("已经存在从v1->v2的边，该有向网标准不允许平行边......");
			}
			p = p->nextarc;
		}
		p = vexTable[v1].firstarc;
		if (p != NULL) {
			while (p->nextarc != NULL) {
				p = p->nextarc;
			}
			p->nextarc = new AdjListDirNetworkArc<WeightType>(v2, w); 
			arcNum++;return;
		}
		else {
			this->vexTable[v1].firstarc = new AdjListDirNetworkArc<WeightType>(v2, w); 
			arcNum++;return;
		}
	}
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::InsertVex(const ElemType& e)
{
	if (vexNum == vexMaxNum) {
		throw Error("该图的顶点数目已经达到了最大数量......");
	}
	else {
		this->vexTable[vexNum].data = e;
		this->vexTable[vexNum].firstarc = NULL;
		this->tag[vexNum] = UNVISITED;
		vexNum++;
	}
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DeleteArc(int v1, int v2)
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("不存在以v1为下标的顶点......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("不存在以v2为下标的顶点......");
	}
	else if (v1 == v2) {
		throw Error("该有向网本身即不存在环......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = this->vexTable[v1].firstarc;
		AdjListDirNetworkArc<WeightType>* temp;
		if (p != NULL) {
			if (p->adjVex == v2) {
				this->vexTable[v1].firstarc = p->nextarc; delete p; arcNum--;
				return;//因为后面循环条件的限制，首先检查第一个结点
			}
			while (p != NULL && p->nextarc != NULL) {//此循环条件至少需要两个及以上的结点
				if (p->nextarc->adjVex == v2) {
					temp = p->nextarc->nextarc; delete p->nextarc;
					p->nextarc = temp; arcNum--;
					return;
				}
				p = p->nextarc;
			}
			return;
		}
		return;
	}
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DeleteVex(const ElemType& e)
{
	int v = this->GetOrder(e);
	if (v<=0||v >= vexNum) {
		throw Error("不存在以v为下标的顶点......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* find = vexTable[v].firstarc;
		while (find != NULL) {//删除v作为出度的边
			vexTable[v].firstarc = find->nextarc; delete find;
			find = vexTable[v].firstarc; arcNum--;
		}
		for (int i = 0; i < vexNum; i++) {//搜索并删除v作为入度的边
			AdjListDirNetworkArc<WeightType>* head = new AdjListDirNetworkArc<WeightType>;
			head->nextarc = vexTable[i].firstarc;
			AdjListDirNetworkArc<WeightType>* p = head; AdjListDirNetworkArc<WeightType>* temp;
			while (p->nextarc != NULL) {
				if (p->nextarc->adjVex == v) {
					temp = p->nextarc;
					p->nextarc = temp->nextarc;
					delete temp; arcNum--; continue;//回退以避免遗漏数据
				}
				p = p->nextarc;
			}
			vexTable[i].firstarc = head->nextarc;
		}
		if (v == vexNum - 1) {
			vexNum--; return;//如果v原本便是vexTable的最后一个元素,vexNum-1即可;
		}
		else {//v不是vexTable的最后一个元素,需要调整
			vexTable[v].data = vexTable[vexNum - 1].data;
			vexTable[v].firstarc = vexTable[vexNum - 1].firstarc;
			tag[v] = tag[vexNum - 1];
			for (int i = 0; i < vexNum - 1; i++) {
				AdjListDirNetworkArc<WeightType>* p = vexTable[i].firstarc;
				while (p != NULL) {
					if (p->adjVex == vexNum - 1) {
						p->adjVex = v;
					}
					p = p->nextarc;
				}
			}
			vexNum--;
		}
	}
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::Clear()
{
	for (int i = 0; i < vexNum; i++) {
		AdjListDirNetworkArc<WeightType>* p = vexTable[i].firstarc;
		while (p != NULL) {//该循环结束,使所有vexTable[i].firstarc全部置为NULL;
			vexTable[i].firstarc = p->nextarc;
			delete p; p = vexTable[i].firstarc;
		}
	}
	for (int i = 0; i < vexNum; i++) {
		tag[i] = UNVISITED;
	}
	vexNum = 0; arcNum = 0;
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::IsEmpty() const
{
	if (vexNum == 0 && arcNum == 0) {
		return true;
	}
	else {
		return false;
	}
}
template <typename ElemType, typename WeightType>
Status AdjListDirNetwork<ElemType, WeightType>::GetElem(int v, ElemType& d) const
{
	if (v < 0 || v >= vexNum) {
		return RANGE_ERROR;
	}
	else {
		d = vexTable[v].data; return SUCCESS;
	}
}
template <typename ElemType, typename WeightType>
Status AdjListDirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType& d)
{
	if (v < 0 || v >= vexNum) {
		return RANGE_ERROR;
	}
	else {
		vexTable[v].data=d; return SUCCESS;
	}
}
template <typename ElemType, typename WeightType>
int AdjListDirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
{
	AdjListDirNetworkArc<WeightType>* p = vexTable[v].firstarc;
	if (p == NULL) {
		return -1;//表示不存在,没有以v作为弧尾的边;
	}
	else {
		return p->adjVex;
	}
}
template <typename ElemType, typename WeightType>
int AdjListDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("不存在以v1为下标的顶点......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("不存在以v2为下标的顶点......");
	}
	else if (v1==v2) {
		throw Error("该有向网不存在环......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = vexTable[v1].firstarc;
		while (p != NULL) {
			if (p->adjVex == v2) {
				if (p->nextarc != NULL) {
					return p->nextarc->adjVex;
				}
				else {
					return -1;//返回-1,表示v1->v2的有向边存在但v2的后继顶点不存在
				}
			}
			p = p->nextarc;
		}
		return -1;//返回-1,表示不存在v1->v2的有向边
	}
}
template <typename ElemType, typename WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("不存在以v1为下标的顶点......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("不存在以v2为下标的顶点......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = vexTable[v1].firstarc;
		while (p != NULL) {
			if (p->adjVex == v2) {
				return p->weight;
			}
			p = p->nextarc;
		}
		//此时表示不存在这样的边,直接返回infinity,但不能throw error捏;
		return this->infinity;
	}
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("不存在以v1为下标的顶点......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("不存在以v2为下标的顶点......");
	}
	else if (v1 == v2) {
		throw Error("该有向网不存在环......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = vexTable[v1].firstarc;
		while (p != NULL) {
			if (p->adjVex == v2) {
				p->weight = w; return;//找到此边并且修改完毕;
			}
			p = p->nextarc;
		}
		//此时表示不存在这样的边;
		throw Error("不存在这样的边......");
	}
}
template <typename ElemType, typename WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetVexNum() const
{
	return this->vexNum;
}
template <typename ElemType, typename WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetArcNum() const
{
	return this->arcNum;
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetTag(int v, Status val) const
{
	if (v < 0 || v >= vexNum) {
		throw Error("不存在以v为下标的顶点......");
	}
	else {
		tag[v] = val;
	}
}
template <typename ElemType, typename WeightType>
Status AdjListDirNetwork<ElemType, WeightType>::GetTag(int v) const
{
	if (v < 0 || v >= vexNum) {
		throw Error("不存在以v为下标的顶点......");
	}
	else {
		return this->tag[v];
	}
}
template <typename ElemType, typename WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetInfinity() const
{
	return this->infinity;
}