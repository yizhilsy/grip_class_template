#pragma once
#include <iostream>
#include "Assistance.h"
using namespace std;
template <typename WeightType>
class AdjListDirNetworkArc
{
public:
	int adjVex;//有向边末尾顶点序号
	WeightType weight;
	AdjListDirNetworkArc<WeightType>* nextarc;
public:
	AdjListDirNetworkArc();
	AdjListDirNetworkArc(int v,WeightType w,AdjListDirNetworkArc<WeightType>* next=NULL);
	virtual ~AdjListDirNetworkArc();
};
template <typename WeightType>
AdjListDirNetworkArc<WeightType>::AdjListDirNetworkArc()
{
	adjVex = -1; weight = 0;nextarc = NULL;
}
template <typename WeightType>
AdjListDirNetworkArc<WeightType>::AdjListDirNetworkArc(int v, WeightType w, AdjListDirNetworkArc<WeightType>* next)
{
	this->adjVex = v; this->weight = w; this->nextarc = next;
}
template <typename WeightType>
AdjListDirNetworkArc<WeightType>::~AdjListDirNetworkArc()
{
	//空实现
}