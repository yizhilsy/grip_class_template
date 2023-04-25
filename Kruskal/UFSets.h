#pragma once
#include <iostream>
#include "ElemNode.h"//"ElemNode.h"已经包含了"Assistance.h"
using namespace std;
template <typename ElemType>
class UFSets
{
protected:
	ElemNode<ElemType>* nodes;
	int size;
	int Find(const ElemType& e) const;//查找该元素所在等价类的根结点的下标
	int HeightSubTree(int r)	const;//求一个等价类的树的高
	//int CollapsingFind(const ElemType& e) const;//使用折叠思想的查找
public:
	UFSets();
	UFSets(ElemType* es, int n);//初始化构造单元素集合，即n个等价类
	virtual ~UFSets();
	Status GetElem(int pos, ElemType& e) const;
	Status SetElem(int pos, const ElemType& e);
	void Union(const ElemType& a, const ElemType& b);
	void WeightUnion(const ElemType& a, const ElemType& b);	//以等价类的个数作为谁是双亲的评判标准
	void HeightUnion(const ElemType& a, const ElemType& b);
	void testPrint() const;
	void Printall_Equivalence() const;
	int GetOrder(const ElemType& e) const;
	void PreOrderSubTree(int r, void (*Visit)(const ElemType&)) const;
	int FirstChild(int r) const;//r是在数组内部的下标
	int RightSibling(int r) const;//r是在数组内部的下标
	int GetSize() const;
	bool IsRootNode(int pos) const;//传入的是数组下标
	int CollapsingFind(const ElemType& e) const;//使用折叠思想的查找
	bool Differ(const ElemType& e1, const ElemType& e2);
};
//外部函数模板声明
template <typename ElemType>
void DisplayTWithConcaveShape(const UFSets<ElemType>& t, int r, int level);//凹入打印法打印树

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
	cout << "打印此并查集数组:" << endl;
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
		return -1;//元素e并不是并查集中的元素
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
		return -1; //-1表示没找到不存在这样的元素在任何一个等价类中
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
		return pos;//返回该元素所属等价类的根节点的数组下标,并且完成折叠
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
	return -1;//	-1在GetOrder函数中表示没找到
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
	int roota = Find(a); int rootb = Find(b);//首先回溯找各自等价类的根结点下标
	if (roota != -1 && rootb != -1 && roota != rootb) {//默认b所在的等价类的根节点作为a所在的等价类的根节点的孩子
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
int UFSets<ElemType>::FirstChild(int r) const//r是在数组内部的下标
{
	if (r < 0 || r >= this->size) {
		return -1;//表示下标错误
	}
	for (int i = 0; i < this->size; i++) {
		if (nodes[i].parent == r) {
			return i;
		}
	}
	return -1;//表示没找到
}
template <typename ElemType>
int UFSets<ElemType>::RightSibling(int r) const
{
	if (r < 0 || r >= this->size) {
		return -1;//表示下标错误
	}
	for (int i = r + 1; i < this->size; i++) {
		if (nodes[r].parent == nodes[i].parent) {
			return i;
		}
	}
	return -1;//表示右兄弟已经到了末尾或者根本没有右兄弟
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
		for (int i = 1; i < level; i++) cout << "  ";//打印层次
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
		return false;//两个元素所处等价类的根节点下标相同，表示这两个元素并不是处于两个不同的等价类
	}
	else {
		return true;//此时处于两个不同的等价类了
	}
}
//Arthur Shiyu Lu.Dream big!
