#include <iostream>
#include "Assistance.h"
using namespace std;
//��³˹�����㷨�еĿ�³˹��������ģ��;
template <typename ElemType,typename WeightType>
class KruskalEdge
{
public:
	ElemType vertex1, vertex2;
	WeightType weight;
	KruskalEdge();
	KruskalEdge(ElemType v1, ElemType v2, WeightType w);
	KruskalEdge<ElemType, WeightType>& operator=(const KruskalEdge<ElemType, WeightType>& kruskaledge);
	bool operator<=(const KruskalEdge<ElemType, WeightType>& kruskaledge);
	bool operator>(const KruskalEdge<ElemType, WeightType>& kruskaledge);
};
template <typename ElemType, typename WeightType>
KruskalEdge<ElemType, WeightType>::KruskalEdge()
{
	//��ʵ��;
}
template <typename ElemType, typename WeightType>
KruskalEdge<ElemType, WeightType>::KruskalEdge(ElemType v1, ElemType v2, WeightType w)
{
	this->vertex1 = v1; this->vertex2 = v2; this->weight = w; return;
}
template <typename ElemType, typename WeightType>
KruskalEdge<ElemType, WeightType>& KruskalEdge<ElemType, WeightType>::operator=(const KruskalEdge<ElemType, WeightType>& kruskaledge)
{
	if (this == &kruskaledge) {
		return *this;
	}
	else {
		this->vertex1 = kruskaledge.vertex1; this->vertex2 = kruskaledge.vertex2; 
		this->weight = kruskaledge.weight; return *this;
	}
}
template <typename ElemType, typename WeightType>
bool KruskalEdge<ElemType, WeightType>::operator<=(const KruskalEdge<ElemType, WeightType>& kruskaledge)
{
	return this->weight <= kruskaledge.weight;
}
template <typename ElemType, typename WeightType>
bool KruskalEdge<ElemType, WeightType>::operator>(const KruskalEdge<ElemType, WeightType>& kruskaledge)
{
	return this->weight > kruskaledge.weight;
}