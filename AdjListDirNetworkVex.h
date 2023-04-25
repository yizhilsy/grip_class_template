#pragma once
#include <iostream>
#include "AdjListDirNetworkArc.h"//辅助软件包已包含
using namespace std;
template <typename ElemType,typename WeightType>
class AdjListDirNetworkVex
{
public:
	ElemType data;
	AdjListDirNetworkArc<WeightType>* firstarc;//指向边结点的指针
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
	//空实现
}