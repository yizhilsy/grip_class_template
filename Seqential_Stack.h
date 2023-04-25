#pragma once
#include <iostream>
#include "Assistance.h"
using namespace std;
template<typename ElemType> class SeqStack
{
protected:
	int top;
	int maxSize;
	ElemType* elems;
public:
	SeqStack();
	SeqStack(int size);
	SeqStack(const SeqStack<ElemType>& seqstack);
	SeqStack<ElemType>& operator=(const SeqStack<ElemType>& seqstack);
	virtual ~SeqStack();
	int GetLength() const;
	bool IsEmpty() const;
	void Clear();
	void Print();
	Status Push(const ElemType& e);
	Status Top(ElemType& e) const;
	Status Pop();
};
template<typename ElemType>
SeqStack<ElemType>::SeqStack() { maxSize = 0; top = -1; elems = NULL; }
template<typename ElemType>
SeqStack<ElemType>::SeqStack(int size) { maxSize = size; top = -1; elems = new ElemType[maxSize]; }
template<typename ElemType>
SeqStack<ElemType>::SeqStack(const SeqStack<ElemType>& seqstack)
{
	maxSize = seqstack.maxSize; top = seqstack.top;
	if (maxSize == 0) { elems = NULL; }
	else
	{
		elems = new ElemType[maxSize];
		for (int i = 0; i < top + 1; i++) { elems[i] = seqstack.elems[i]; }
	}
}
template<typename ElemType>
SeqStack<ElemType>& SeqStack<ElemType>::operator=(const SeqStack<ElemType>& seqstack)
{
	if (this == &seqstack) { return *this; }
	else
	{
		if (elems != NULL) { delete[] elems; elems = NULL; }
		maxSize = seqstack.maxSize; top = seqstack.top; elems = new ElemType[maxSize];
		for (int i = 0; i < top + 1; i++) { elems[i] = seqstack.elems[i]; }
		return *this;
	}
}
template<typename ElemType>
SeqStack<ElemType>::~SeqStack() { delete[] elems; elems = NULL; top = -1; maxSize = 0; }
template<typename ElemType>
int SeqStack<ElemType>::GetLength() const { return top + 1; }
template<typename ElemType>
bool SeqStack<ElemType>::IsEmpty() const { return (top == -1 ? true : false); }
template<typename ElemType>
void SeqStack<ElemType>::Clear() { top = -1; }
template<typename ElemType>
void SeqStack<ElemType>::Print()
{
	cout << "The SeqStack struct:" << endl;
	for (int i = top; i >= 0; i--) { cout << elems[i] << endl; cout << "=====" << endl; }
	cout << "The maxSize of the SeqStack is " << maxSize << ".Used " << top + 1 << " size, remain " << maxSize - top - 1 << " size." << endl;
}
template<typename ElemType>
Status SeqStack<ElemType>::Push(const ElemType& e)
{
	if (top == maxSize - 1) { return OVER_FLOW; }
	else { top++; elems[top] = e; return SUCCESS; }
}
template<typename ElemType>
Status SeqStack<ElemType>::Top(ElemType& e) const
{
	if (IsEmpty()) { cout << "It is an empty SeqStack!Neglect Top." << endl; return UNDER_FLOW; }
	else
	{
		e = elems[top]; return SUCCESS;
	}
}
template<typename ElemType>
Status SeqStack<ElemType>::Pop()
{
	if (IsEmpty()) { cout << "It is an empty SeqStack!Neglect Pop." << endl; return UNDER_FLOW; }
	else { top--; return SUCCESS; }
}
