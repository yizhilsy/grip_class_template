#pragma once
#include <iostream>
#include "AdjListDirNetworkArc.h"//����������Ѱ���
using namespace std;
template <typename ElemType,typename WeightType>
class AdjListDirNetworkVex
{
public:
	ElemType data;
	AdjListDirNetworkArc<WeightType>* firstarc;//ָ��߽���ָ��
public:
	AdjListDirNetworkVex();
	AdjListDirNetworkVex(ElemType d,AdjListDirNetworkArc<WeightType>* first=NULL);
	virtual ~AdjListDirNetworkVex();
};
template <typename ElemType, typename WeightType>
AdjListDirNetworkVex<ElemType, WeightType>::AdjListDirNetworkVex()
{
	firstarc = NULL;
}
template <typename ElemType, typename WeightType>
AdjListDirNetworkVex<ElemType, WeightType>::AdjListDirNetworkVex(ElemType d, AdjListDirNetworkArc<WeightType>* first)
{
	data = d; firstarc = first;
}
template <typename ElemType, typename WeightType>
AdjListDirNetworkVex<ElemType, WeightType>::~AdjListDirNetworkVex()
{
	//��ʵ��
}