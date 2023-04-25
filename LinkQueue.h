#pragma once
#include <iostream>
#include "Node.h"
#include "Assistance.h"
using namespace std;
//此是带头结点的标准
template <typename ElemType>class LinkQueue
{
public:
	LinkQueue();
	LinkQueue(const LinkQueue<ElemType>& linkqueue);
	~LinkQueue();
	LinkQueue<ElemType>& operator=(const LinkQueue<ElemType>& linkqueue);
	void Clear();
	int GetLength()const;
	bool IsEmpty()const;
	Status EnQueue(const ElemType& e);
	Status DelQueue(ElemType& e);
	Status GetHead(ElemType& e);
	void Print();
	void Yhways_Print();
protected:
	Node<ElemType>* front, * rear;
};
template <typename ElemType>
LinkQueue<ElemType>::LinkQueue() { front = new Node<ElemType>; rear = front; }
template <typename ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType>& linkqueue)
{
	front = new Node<ElemType>; rear = front; Node<ElemType>* p2 = linkqueue.front->next; Node<ElemType>* p = front;
	while (p2 != NULL)
	{
		p->next = new Node<ElemType>(p2->data);
		p = p->next; p2 = p2->next;
	}
	rear = p;
}
template <typename ElemType>
LinkQueue<ElemType>& LinkQueue<ElemType>::operator=(const LinkQueue<ElemType>& linkqueue)
{
	if (front->next != NULL) { Clear(); }Node<ElemType>* p = front; Node<ElemType>* p2 = linkqueue.front->next;
	while (p2 != NULL)
	{
		p->next = new Node<ElemType>(p2->data);
		p = p->next; p2 = p2->next;
	}
	return *this;
}
template <typename ElemType>
void LinkQueue<ElemType>::Clear()
{
	Node<ElemType>* p = front->next;
	while (p != NULL)
	{
		front->next = p->next; delete p; p = front->next;
	}
	rear = front;
}
template <typename ElemType>
LinkQueue<ElemType>::~LinkQueue() { Clear(); delete front; front = NULL; rear = NULL; }
template <typename ElemType>
int LinkQueue<ElemType>::GetLength()const
{
	int ct = 0; Node<ElemType>* p = front->next;
	while (p != NULL) { ct++; p = p->next; }
	return ct;
}
template <typename ElemType>
bool LinkQueue<ElemType>::IsEmpty()const { return(front->next == NULL ? true : false); }
template <typename ElemType>
Status LinkQueue<ElemType>::EnQueue(const ElemType& e) { rear->next = new Node<ElemType>(e); rear = rear->next; return SUCCESS; }
template <typename ElemType>
Status LinkQueue<ElemType>::DelQueue(ElemType& e)
{
	if (IsEmpty()) { return UNDER_FLOW; }
	else
	{
		Node<ElemType>* p = front->next;
		e = p->data; front->next = p->next; delete p;
		if (GetLength() == 0) { rear = front; }
		return SUCCESS;
	}
}
template <typename ElemType>
Status LinkQueue<ElemType>::GetHead(ElemType& e)
{
	if (IsEmpty()) { return UNDER_FLOW; }
	else
	{
		e = front->next->data;
		return SUCCESS;
	}
}
template <typename ElemType>
void LinkQueue<ElemType>::Print()
{
	Node<ElemType>* p = front->next; cout << "The LinkQueue struct:" << endl;
	cout << "Front: ";
	while (p != NULL)
	{
		cout << p->data << "->"; p = p->next;
	}
	cout << "<-rear" << endl; cout << "The current size of the LinkQueue is " << GetLength() << "." << endl;
}
template <typename ElemType>
void LinkQueue<ElemType>::Yhways_Print()
{
	Node<ElemType>* p = front->next;
	while (p != NULL)
	{
		cout << p->data << "  "; p = p->next;
	}
	cout << endl;
}
//Author Lu Shiyu.Dream Big!
