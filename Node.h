#pragma once
#include <iostream>
#include "Assistance.h"
using namespace std;
template <typename ElemType>class LinkQueue;
template <typename ElemType> class Node
{
public:
	Node();
	Node(ElemType e, Node<ElemType>* pe = NULL);
	Node(const Node<ElemType>& node);
	~Node() {}
	Node<ElemType>& operator=(const Node<ElemType>& node);
	friend class LinkQueue<ElemType>;
private:
	ElemType data;
	Node<ElemType>* next;
};
template <typename ElemType>
Node<ElemType>::Node()
{
	next = NULL;
}
template <typename ElemType>
Node<ElemType>::Node(ElemType e, Node<ElemType>* pe)
{
	data = e; next = pe;
}
template <typename ElemType>
Node<ElemType>::Node(const Node<ElemType>& node)
{
	*(this) = node;//采用深赋值的方式协助完成
}
template <typename ElemType>
Node<ElemType>& Node<ElemType>::operator=(const Node<ElemType>& node)
{
	data = node.data; next = node.next;
}
