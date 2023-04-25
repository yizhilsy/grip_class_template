#include <iostream>
#include "Kruskal.h"
using namespace std;
int main()
{
	char charray[6] = { 'A','B','C','D','E','F' };
	AdjMatrixUndirNetwork<char, int> G1(charray, 6);
	G1.InsertArc(0, 1, 34); G1.InsertArc(0, 2, 46); G1.InsertArc(0, 5, 19); G1.InsertArc(1, 4, 12);
	G1.InsertArc(2, 3, 17); G1.InsertArc(2, 5, 25); G1.InsertArc(3, 4, 38); G1.InsertArc(3, 5, 25);
	G1.InsertArc(4, 5, 26);
	G1.Display();
	MiniSpanTreeKruskal(G1);
	system("pause");
	return 0;
}