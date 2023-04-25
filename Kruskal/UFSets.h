#pragma once
#include <iostream>
#include "ElemNode.h"//"ElemNode.h"�Ѿ�������"Assistance.h"
using namespace std;
template <typename ElemType>
class UFSets
{
protected:
	ElemNode<ElemType>* nodes;
	int size;
	int Find(const ElemType& e) const;//���Ҹ�Ԫ�����ڵȼ���ĸ������±�
	int HeightSubTree(int r)	const;//��һ���ȼ�������ĸ�
	//int CollapsingFind(const ElemType& e) const;//ʹ���۵�˼��Ĳ���
public:
	UFSets();
	UFSets(ElemType* es, int n);//��ʼ�����쵥Ԫ�ؼ��ϣ���n���ȼ���
	virtual ~UFSets();
	Status GetElem(int pos, ElemType& e) const;
	Status SetElem(int pos, const ElemType& e);
	void Union(const ElemType& a, const ElemType& b);
	void WeightUnion(const ElemType& a, const ElemType& b);	//�Եȼ���ĸ�����Ϊ˭��˫�׵����б�׼
	void HeightUnion(const ElemType& a, const ElemType& b);
	void testPrint() const;
	void Printall_Equivalence() const;
	int GetOrder(const ElemType& e) const;
	void PreOrderSubTree(int r, void (*Visit)(const ElemType&)) const;
	int FirstChild(int r) const;//r���������ڲ����±�
	int RightSibling(int r) const;//r���������ڲ����±�
	int GetSize() const;
	bool IsRootNode(int pos) const;//������������±�
	int CollapsingFind(const ElemType& e) const;//ʹ���۵�˼��Ĳ���
	bool Differ(const ElemType& e1, const ElemType& e2);
};
//�ⲿ����ģ������
template <typename ElemType>
void DisplayTWithConcaveShape(const UFSets<ElemType>& t, int r, int level);//�����ӡ����ӡ��

template <typename ElemType>
UFSets<ElemType>::UFSets()
{
	nodes = NULL; size = 0;
}
template <typename ElemType>
UFSets<ElemType>::UFSets(ElemType* es, int n)
{
	size = n; nodes = new ElemNode<ElemType>[size];
	for (int i = 0; i < size; i++) {
		nodes[i].data = es[i]; nodes[i].parent = -1;
	}
}
template <typename ElemType>
void UFSets<ElemType>::testPrint() const
{
	cout << "��ӡ�˲��鼯����:" << endl;
	for (int i = 0; i < this->size; i++) {
		cout << "\t" << nodes[i].data << " ";
	}
	cout << endl;
	for (int i = 0; i < this->size; i++) {
		cout << "\t" << nodes[i].parent << " ";
	}
	cout << endl;
}
template <typename ElemType>
int UFSets<ElemType>::Find(const ElemType& e) const
{
	int pos = GetOrder(e);
	if (pos == -1) {
		return -1;//Ԫ��e�����ǲ��鼯�е�Ԫ��
	}
	else {
		while (nodes[pos].parent >= 0) {
			pos = nodes[pos].parent;
		}
		return	pos;
	}
}
template <typename ElemType>
int UFSets<ElemType>::HeightSubTree(int r) const
{
	int maxheight = 0;
	for (int r_child = this->FirstChild(r); r_child != -1; r_child = RightSibling(r_child)) {
		int heresubtreeheight = HeightSubTree(r_child);
		if (maxheight < heresubtreeheight) {
			maxheight = heresubtreeheight;
		}
	}
	return maxheight + 1;
}
template <typename ElemType>
int UFSets<ElemType>::CollapsingFind(const ElemType& e) const
{
	int pos = this->GetOrder(e);
	if (pos == -1) {
		return -1; //-1��ʾû�ҵ�������������Ԫ�����κ�һ���ȼ�����
	}
	else {
		int temp = pos; int k;
		while (nodes[pos].parent >= 0) {
			pos = nodes[pos].parent;
		}
		while (nodes[temp].parent >= 0) {
			if (nodes[temp].parent != pos) {
				k = nodes[temp].parent;
				nodes[temp].parent = pos;
				temp = k;
			}
			else {
				k = nodes[temp].parent;
				temp = k;
			}
		}
		return pos;//���ظ�Ԫ�������ȼ���ĸ��ڵ�������±�,��������۵�
	}
}

template <typename ElemType>
int UFSets<ElemType>::GetOrder(const ElemType& e) const
{
	for (int i = 0; i < this->size; i++) {
		if (nodes[i].data == e) {
			return i;
		}
	}
	return -1;//	-1��GetOrder�����б�ʾû�ҵ�
}
template <typename ElemType>
UFSets<ElemType>:: ~UFSets()
{
	delete[] nodes; size = 0; nodes = NULL;
}
template <typename ElemType>
Status UFSets<ElemType>::GetElem(int pos, ElemType& e) const
{
	if (pos < 0 || pos >= this->size) {
		return FAIL;
	}
	else {
		e = nodes[pos].data;
	}
}
template <typename ElemType>
Status UFSets<ElemType>::SetElem(int pos, const ElemType& e)
{
	if (pos < 0 || pos >= this->size) {
		return FAIL;
	}
	else {
		nodes[pos].data = e;
	}
}
template <typename ElemType>
void UFSets<ElemType>::Union(const ElemType& a, const ElemType& b)
{
	int roota = Find(a); int rootb = Find(b);//���Ȼ����Ҹ��Եȼ���ĸ�����±�
	if (roota != -1 && rootb != -1 && roota != rootb) {//Ĭ��b���ڵĵȼ���ĸ��ڵ���Ϊa���ڵĵȼ���ĸ��ڵ�ĺ���
		nodes[roota].parent = nodes[roota].parent + nodes[rootb].parent; nodes[rootb].parent = roota;
	}
}
template <typename ElemType>
void UFSets<ElemType>::WeightUnion(const ElemType& a, const ElemType& b)
{
	int posa = this->Find(a); int posb = this->Find(b);
	if (posa != -1 && posb != -1 && posa != posb) {
		int temp = nodes[posa].parent + nodes[posb].parent;
		if (nodes[posa].parent < nodes[posb].parent) {
			nodes[posb].parent = posa; nodes[posa].parent = temp;
		}
		else {
			nodes[posa].parent = posb; nodes[posb].parent = temp;
		}
	}
}
template <typename ElemType>
void UFSets<ElemType>::HeightUnion(const ElemType& a, const ElemType& b)
{
	int posa = Find(a); int posb = Find(b);
	if (posa != -1 && posb != -1 && posa != posb) {
		int temp = nodes[posa].parent + nodes[posb].parent;
		if (HeightSubTree(posa) < HeightSubTree(posb)) {
			nodes[posa].parent = posb; nodes[posb].parent = temp;
		}
		else {
			nodes[posb].parent = posa; nodes[posa].parent = temp;
		}
	}
}
template <typename ElemType>
void UFSets<ElemType>::PreOrderSubTree(int r, void (*Visit)(const ElemType&)) const
{
	(*Visit)(nodes[r].data);
	for (int r_child = FirstChild(r); r_child != -1; r_child = RightSibling(r_child)) {
		PreOrderSubTree(r_child, Visit);
	}
}
template <typename ElemType>
int UFSets<ElemType>::FirstChild(int r) const//r���������ڲ����±�
{
	if (r < 0 || r >= this->size) {
		return -1;//��ʾ�±����
	}
	for (int i = 0; i < this->size; i++) {
		if (nodes[i].parent == r) {
			return i;
		}
	}
	return -1;//��ʾû�ҵ�
}
template <typename ElemType>
int UFSets<ElemType>::RightSibling(int r) const
{
	if (r < 0 || r >= this->size) {
		return -1;//��ʾ�±����
	}
	for (int i = r + 1; i < this->size; i++) {
		if (nodes[r].parent == nodes[i].parent) {
			return i;
		}
	}
	return -1;//��ʾ���ֵ��Ѿ�����ĩβ���߸���û�����ֵ�
}
template <typename ElemType>
void PrintVisit(const ElemType& e) {
	cout << e;
}
template <typename ElemType>
void DisplayTWithConcaveShape(const UFSets<ElemType>& t, int r, int level)
{
	if (r >= 0 && r < t.GetSize())
	{
		for (int i = 1; i < level; i++) cout << "  ";//��ӡ���
		ElemType e; t.GetElem(r, e);
		cout << e << endl;
		for (int r_child = t.FirstChild(r); r_child != -1; r_child = t.RightSibling(r_child)) {
			DisplayTWithConcaveShape(t, r_child, level + 1);
		}
	}
}
template <typename ElemType>
int UFSets<ElemType>::GetSize() const
{
	return this->size;
}
template <typename ElemType>
void UFSets<ElemType>::Printall_Equivalence() const
{
	for (int i = 0; i < this->size; i++) {
		if (this->IsRootNode(i) == true) {
			DisplayTWithConcaveShape((*this), i, 1); cout << "The Height of the tree is " << this->HeightSubTree(i) << endl;
		}
	}
}
template <typename ElemType>
bool UFSets<ElemType>::IsRootNode(int pos) const
{
	return nodes[pos].parent < 0 ? true : false;
}
template <typename ElemType>
bool UFSets<ElemType>::Differ(const ElemType& e1, const ElemType& e2)
{
	int pose1 = Find(e1); int pose2 = Find(e2);
	if (pose1 == pose2) {
		return false;//����Ԫ�������ȼ���ĸ��ڵ��±���ͬ����ʾ������Ԫ�ز����Ǵ���������ͬ�ĵȼ���
	}
	else {
		return true;//��ʱ����������ͬ�ĵȼ�����
	}
}
//Arthur Shiyu Lu.Dream big!
