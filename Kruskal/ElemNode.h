#pragma once
#include <iostream>
#include "Assistance.h"
using namespace std;
template <typename ElemType> class UFSets;
template <typename ElemType>
class ElemNode
{
private:
	ElemType data; int parent;
public:
	ElemNode();
	ElemNode(const ElemType& data, int parent = -1);
	virtual ~ElemNode();
	ElemNode<ElemType>& operator=(const ElemNode<ElemType>& elemnode);
	friend class UFSets<ElemType>;//友类
	friend void DisplayTWithConcaveShape(const UFSets<ElemType>& t, int r, int level);//友元函数
};
template <typename ElemType>
ElemNode<ElemType>::ElemNode() {
	parent = -1;
}
template <typename ElemType>
ElemNode<ElemType>::ElemNode(const ElemType& data, int parent) {
	this->data = data; this->parent = parent;
}
template <typename ElemType>
ElemNode<ElemType>::~ElemNode() {
	//空实现
}
template <typename ElemType>
ElemNode<ElemType>& ElemNode<ElemType>::operator=(const ElemNode<ElemType>& elemnode) {
	this->data = elemnode.data; this->parent = elemnode.parent;
}
//Arthur Shiyu Lu.Dream big!
