#pragma once
#include <iostream>
#include "AdjListDirNetworkVex.h"
#include "LinkQueue.h"
#include <vector>
using namespace std;
//������������׼����ģ��
template <typename ElemType,typename WeightType>
class AdjListDirNetwork
{
public:
	int vexNum; int vexMaxNum; int arcNum;
	AdjListDirNetworkVex<ElemType, WeightType>* vexTable;
	mutable Status* tag;
	WeightType infinity;
public:
	//����,������������
	AdjListDirNetwork(int vertexMaxNum = DEFAULT_SIZE,WeightType infinit = (WeightType)DEFAULT_INFINITY);
	AdjListDirNetwork(ElemType* es, int vertexNum, int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	virtual ~AdjListDirNetwork();
	//���ܺ�������
	int GetOrder(ElemType& e) const;
	void testprint() const;
	void InsertArc(int v1, int v2, WeightType w);	// ����Ӷ���Ϊv1��v2��Ȩ��Ϊw�ı�;
	void InsertVex(const ElemType& e);				// ����һ�����㣬��Ԫ��ֵΪe;
	void DeleteArc(int v1, int v2);					// ɾ��v1->v2�������;
	void DeleteVex(const ElemType& e);							// ɾ���������ж���v;
	void Clear();									// ���������;
	void IsEmpty() const;							// �ж��������Ƿ�Ϊ��;
	Status GetElem(int v, ElemType& d) const;		// �󶥵��Ԫ��ֵ	
	Status SetElem(int v, const ElemType& d);		// ���ö����Ԫ��ֵ
	int FirstAdjVex(int v) const;					// ���������ж���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;			// ���������ж���v1�������v2����һ���ڽӵ�
	WeightType GetWeight(int v1, int v2) const;		// ��Ӷ���Ϊv1��v2�ıߵ�Ȩֵ
	void SetWeight(int v1, int v2, WeightType w);	// ���ôӶ���Ϊv1��v2�ıߵ�Ȩֵ
	int GetVexNum() const;							// ���������Ķ������			 
	int GetArcNum() const;							// ���������ı�������
	void SetTag(int v,Status val) const;			// �����������ж���ķ������
	Status GetTag(int v) const;						// ��ȡ�������ж���ķ������
	WeightType GetInfinity() const;					// ��ȡ��������������ֵ
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
		cout << "���ڴ� " << i << " �� " << j << " ��·��!" << endl;
	}
	else {
		cout << "�������ڴ� " << i << " �� " << j << " ��·��!" << endl;
	}
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, UNVISITED);
	}
	//ʹ������������������ж�ʼ��i���յ�j֮����ڵ�����·��,
	cout<<"�� "<<i<<" �� "<<j<<" ������·����:" << endl;
	DFS_AllPath(g, posi, ct, path,j);
	for (int i = 0; i < g.GetVexNum(); i++) {
		g.SetTag(i, UNVISITED);
	}
	cout << "Used BFS Search define whether connected..." << endl;
	if (BFS_IsConnected(g, posi, j) == true) {
		cout << "���ڴ� " << i << " �� " << j << " ��·��!" << endl;
	}
	else {
		cout << "�������ڴ� " << i << " �� " << j << " ��·��!" << endl;
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
	return false;//�����붥��result֮�䲻��ͨ
}
template <typename ElemType,typename WeightType>
bool DFS_IsConnected(const AdjListDirNetwork<ElemType, WeightType>& g, int v, ElemType result)
{
	ElemType e; g.GetElem(v, e); g.SetTag(v, VISITED);
	if (e == result) {//�����������
		return true;
	}
	bool flag=false;
	
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w)) {
		if (g.GetTag(w) == UNVISITED) {
			flag=DFS_IsConnected(g, w, result);
			if (flag == true) {
				return flag;//�ҵ��յ㣬���ݹ鷵��
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
	path[ct] = e;//�����ʱ��������·��
	g.SetTag(v, VISITED);//���ʽ�㲢��Ϊ�ѷ���
	if (e == result) {//�����������:��ʾ��ʱ�Ѿ��ҵ���i->j��һ��ͨ·
		for (int i = 0; i <= ct; i++) {
			cout << path[i] << "--->";
		}
		cout <<"END." << endl; return;
	}
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w)) {//�ݹ�������ȱ���
		if (g.GetTag(w) == UNVISITED) {
			//״̬����
			//DFS��������ݹ����
			DFS_AllPath(g, w, ct+1,path,result);
			//����ȫ������·����Ҫ״̬����
			g.SetTag(w, UNVISITED);
		}
	}
}
//�����������DFS�㷨
template<typename ElemType,typename WeightType>
void DFS(const AdjListDirNetwork<ElemType, WeightType>& g, int v,void (*Visit)(const ElemType&))
{
	ElemType e;
	g.GetElem(v, e);
	(*Visit)(e);
	g.SetTag(v, VISITED);//���ʽ�㲢��Ϊ�ѷ���
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w)) {//�ݹ�������ȱ���
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
	cout << "������������ " << ct << " ����ͨ����" << endl;
}
template <typename ElemType,typename WeightType>
void BFS(const AdjListDirNetwork<ElemType, WeightType>& g,int v,void(*Visit)(const ElemType&))
{
	//���ʽ��
	ElemType e;
	g.GetElem(v, e);
	(*Visit)(e);
	g.SetTag(v, VISITED);
	LinkQueue<int> lq; lq.EnQueue(v); int u, w;
	while (!lq.IsEmpty()) {
		lq.DelQueue(u);
		for (w = g.FirstAdjVex(u); w != -1; w = g.NextAdjVex(u, w)) {
			if (g.GetTag(w) == UNVISITED) {
				g.GetElem(w, e);//����e���ܽ��Ԫ��ֵ,���ʽ��
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
	cout << "������������ " << ct << " ����ͨ����" << endl;
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
	return -1;//��ʾû�ҵ�
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::testprint() const
{
	cout << "VexTable:" << endl;
	for (int i = 0; i < vexNum; i++) {
		cout <<i<<"th : " << "����:" << vexTable[i].data << "  ";
		AdjListDirNetworkArc<WeightType>* p = vexTable[i].firstarc;
		while (p != NULL) {
			cout<<"( "<<i<<"-->" << p->adjVex <<" ,weight: " << p->weight << " )" << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
	cout << "������������: " << this->vexNum << " �����; ������������: " << this->arcNum << " �������;"<<endl;
	cout << "���������Ķ���������:" << endl;
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
void AdjListDirNetwork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)//v1->v2�����,Ȩ��Ϊw;
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("��������v1Ϊ�±�ĵ�......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("��������v2Ϊ�±�ĵ�......");
	}
	else if (v1 == v2) {
		throw Error("��ͼ�������л�......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = vexTable[v1].firstarc;
		while (p != NULL) {
			if (p->adjVex == v2) {
				throw Error("�Ѿ����ڴ�v1->v2�ıߣ�����������׼������ƽ�б�......");
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
		throw Error("��ͼ�Ķ�����Ŀ�Ѿ��ﵽ���������......");
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
		throw Error("��������v1Ϊ�±�Ķ���......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("��������v2Ϊ�±�Ķ���......");
	}
	else if (v1 == v2) {
		throw Error("�����������������ڻ�......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = this->vexTable[v1].firstarc;
		AdjListDirNetworkArc<WeightType>* temp;
		if (p != NULL) {
			if (p->adjVex == v2) {
				this->vexTable[v1].firstarc = p->nextarc; delete p; arcNum--;
				return;//��Ϊ����ѭ�����������ƣ����ȼ���һ�����
			}
			while (p != NULL && p->nextarc != NULL) {//��ѭ������������Ҫ���������ϵĽ��
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
		throw Error("��������vΪ�±�Ķ���......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* find = vexTable[v].firstarc;
		while (find != NULL) {//ɾ��v��Ϊ���ȵı�
			vexTable[v].firstarc = find->nextarc; delete find;
			find = vexTable[v].firstarc; arcNum--;
		}
		for (int i = 0; i < vexNum; i++) {//������ɾ��v��Ϊ��ȵı�
			AdjListDirNetworkArc<WeightType>* head = new AdjListDirNetworkArc<WeightType>;
			head->nextarc = vexTable[i].firstarc;
			AdjListDirNetworkArc<WeightType>* p = head; AdjListDirNetworkArc<WeightType>* temp;
			while (p->nextarc != NULL) {
				if (p->nextarc->adjVex == v) {
					temp = p->nextarc;
					p->nextarc = temp->nextarc;
					delete temp; arcNum--; continue;//�����Ա�����©����
				}
				p = p->nextarc;
			}
			vexTable[i].firstarc = head->nextarc;
		}
		if (v == vexNum - 1) {
			vexNum--; return;//���vԭ������vexTable�����һ��Ԫ��,vexNum-1����;
		}
		else {//v����vexTable�����һ��Ԫ��,��Ҫ����
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
		while (p != NULL) {//��ѭ������,ʹ����vexTable[i].firstarcȫ����ΪNULL;
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
		return -1;//��ʾ������,û����v��Ϊ��β�ı�;
	}
	else {
		return p->adjVex;
	}
}
template <typename ElemType, typename WeightType>
int AdjListDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("��������v1Ϊ�±�Ķ���......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("��������v2Ϊ�±�Ķ���......");
	}
	else if (v1==v2) {
		throw Error("�������������ڻ�......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = vexTable[v1].firstarc;
		while (p != NULL) {
			if (p->adjVex == v2) {
				if (p->nextarc != NULL) {
					return p->nextarc->adjVex;
				}
				else {
					return -1;//����-1,��ʾv1->v2������ߴ��ڵ�v2�ĺ�̶��㲻����
				}
			}
			p = p->nextarc;
		}
		return -1;//����-1,��ʾ������v1->v2�������
	}
}
template <typename ElemType, typename WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("��������v1Ϊ�±�Ķ���......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("��������v2Ϊ�±�Ķ���......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = vexTable[v1].firstarc;
		while (p != NULL) {
			if (p->adjVex == v2) {
				return p->weight;
			}
			p = p->nextarc;
		}
		//��ʱ��ʾ�����������ı�,ֱ�ӷ���infinity,������throw error��;
		return this->infinity;
	}
}
template <typename ElemType, typename WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
{
	if (v1 < 0 || v1 >= vexNum) {
		throw Error("��������v1Ϊ�±�Ķ���......");
	}
	else if (v2 < 0 || v2 >= vexNum) {
		throw Error("��������v2Ϊ�±�Ķ���......");
	}
	else if (v1 == v2) {
		throw Error("�������������ڻ�......");
	}
	else {
		AdjListDirNetworkArc<WeightType>* p = vexTable[v1].firstarc;
		while (p != NULL) {
			if (p->adjVex == v2) {
				p->weight = w; return;//�ҵ��˱߲����޸����;
			}
			p = p->nextarc;
		}
		//��ʱ��ʾ�����������ı�;
		throw Error("�����������ı�......");
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
		throw Error("��������vΪ�±�Ķ���......");
	}
	else {
		tag[v] = val;
	}
}
template <typename ElemType, typename WeightType>
Status AdjListDirNetwork<ElemType, WeightType>::GetTag(int v) const
{
	if (v < 0 || v >= vexNum) {
		throw Error("��������vΪ�±�Ķ���......");
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