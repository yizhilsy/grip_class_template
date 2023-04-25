#include <iostream>
#include "AdjListDirNetwork.h"
#include "ShortestPathDij.h"
#include "ShortestPathBellmanFord.h"
#include "ShortestPathFloyd.h"
#include "TopSort.h"
#include "CriticalPath.h"
#include "dfs_search_pointtopoint_minpath.h"//暴力搜索点对点的最短路径
#include "Longest_Path.h"
#include "DFS_TopSort.h"
#include "Real_DFS_TopSort.h"
using namespace std;
void test01();//测试上机题第1，2题
void test02();//测试迪杰斯特拉算法
void test03();//测试贝尔曼福特算法
void test04();//测试弗洛伊德算法
void test05();//测试拓扑排序算法
void test06();//测试关键路径算法
void test07();//测试上机题第六题最长路径算法
void test08();//测试上机题第七题
int main()
{
	int intarray[7] = {0,1,2,3,4,5,6};
	AdjListDirNetwork<int,int> G1(intarray, 7);
	G1.InsertArc(0, 1, 8); G1.InsertArc(0, 3, 4); G1.InsertArc(0, 4, 5);
	G1.InsertArc(1, 2, 3); G1.InsertArc(2, 6, 6); G1.InsertArc(3, 4, 1);
	G1.InsertArc(4, 1, 2); G1.InsertArc(4, 2, 7); G1.InsertArc(4, 5, 2);
	G1.InsertArc(5, 2, 3); G1.InsertArc(5, 6, 9);
	G1.testprint();
	cout << "该有向图的深度优先遍历顺序为：" << endl;
	DFSTraverse(G1, VisitNode);
	cout << "该有向图的广度优先遍历顺序为：" << endl;
	BFSTraverse(G1, VisitNode);
	G1.testprint();
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	//test07();
	cout << "-----------------------" << endl;
	test08();
	system("pause");
	return 0;
}
void test08() 
{
	int intarray[7] = { 0,1,2,3,4,5,6 };
	AdjListDirNetwork<int, int> G1(intarray, 7);
	G1.InsertArc(0, 1, 8); G1.InsertArc(0, 3, 4); G1.InsertArc(0, 4, 5);
	G1.InsertArc(1, 2, 3); G1.InsertArc(2, 6, 6); G1.InsertArc(3, 4, 1);
	G1.InsertArc(4, 1, 2); G1.InsertArc(4, 2, 7); G1.InsertArc(4, 5, 2);
	G1.InsertArc(5, 2, 3); G1.InsertArc(5, 6, 9);
	G1.testprint();
	DFS_TopSort(G1);
	Real_DFS_TopSort(G1);
	char charray[4] = { 'A','B','C','D'};
	AdjListDirNetwork<char, int> G2(charray, 4);
	G2.InsertArc(0, 1, 10); G2.InsertArc(1, 2, 10); G2.InsertArc(2, 3, 10); G2.InsertArc(3, 1, 10);
	G2.testprint();
	DFS_TopSort(G2);
	Real_DFS_TopSort(G2);
	char charray2[9] = { 'A','B','C','D','E','F','G','H','I' };
	AdjListDirNetwork<char, int> G3(charray2, 9);
	G3.InsertArc(0, 1, 10); G3.InsertArc(1, 6, 10); G3.InsertArc(1, 2, 10); G3.InsertArc(2, 3, 10);
	G3.InsertArc(2, 5, 10); G3.InsertArc(3, 4, 10); G3.InsertArc(4, 2, 10); G3.InsertArc(7, 8, 10);
	G3.InsertArc(8, 5, 10);
	G3.testprint();
	DFS_TopSort(G3);
	Real_DFS_TopSort(G3);
	char charray3[6] = { 'A','B','C','D','E','F' };
	AdjListDirNetwork<char, int> G4(charray3, 6);
	G4.InsertArc(0, 1, 10); G4.InsertArc(1, 2, 10); G4.InsertArc(3, 4, 10); G4.InsertArc(4, 2, 10); 
	G4.InsertArc(4, 5, 10); G4.InsertArc(5, 3, 10);
	G4.testprint();
	DFS_TopSort(G4);
	Real_DFS_TopSort(G4);
	char charray4[12] = { 'A','B','C','D','E','F','G','H','I','J','K','L' };
	cout << "=====================G5====================" << endl;
	AdjListDirNetwork<char, int> G5(charray4, 12);
	G5.InsertArc(0, 1, 10); G5.InsertArc(1, 2, 10); G5.InsertArc(1, 3, 10); G5.InsertArc(3, 4, 10); G5.InsertArc(4, 5, 10);
	G5.InsertArc(4, 6, 10); G5.InsertArc(5, 3, 10);  G5.InsertArc(7, 8, 10); G5.InsertArc(8, 9, 10); G5.InsertArc(9, 5, 10); 
	G5.InsertArc(9, 10, 10);G5.InsertArc(10, 11, 10); G5.InsertArc(11, 9, 10);
	G5.testprint();
	DFS_TopSort(G5);
	Real_DFS_TopSort(G5);
}
void test07()
{
	int intarray[7] = { 0,1,2,3,4,5,6 };
	AdjListDirNetwork<int, int> G1(intarray, 7);
	G1.InsertArc(0, 1, 8); G1.InsertArc(0, 3, 4); G1.InsertArc(0, 4, 5);
	G1.InsertArc(1, 2, 3); G1.InsertArc(2, 6, 6); G1.InsertArc(3, 4, 1);
	G1.InsertArc(4, 1, 2); G1.InsertArc(4, 2, 7); G1.InsertArc(4, 5, 2);
	G1.InsertArc(5, 2, 3); G1.InsertArc(5, 6, 9);
	G1.testprint();
	Longest_Path(G1);
	DpLongestPath(G1);
}
void test06()
{
	int intarray[9] = { 0,1,2,3,4,5,6,7,8 };
	AdjListDirNetwork<int, int> G1(intarray, 9);
	G1.InsertArc(0, 1, 6); G1.InsertArc(0, 2, 4); G1.InsertArc(0, 3, 5); G1.InsertArc(1, 4, 1);
	G1.InsertArc(2, 4, 1); G1.InsertArc(3, 5, 2); G1.InsertArc(4, 6, 9); G1.InsertArc(4, 7, 7);
	G1.InsertArc(5, 7, 4); G1.InsertArc(6, 8, 2); G1.InsertArc(7, 8, 4);
	CriticalPath(G1);
}
void test05()
{
	char charray[6] = { 'A','B','C','D','E','F' };
	AdjListDirNetwork<char, int> G1(charray, 6);
	G1.InsertArc(1, 0, 10); G1.InsertArc(1, 3, 10); G1.InsertArc(2, 0, 10); G1.InsertArc(2, 3, 10);
	G1.InsertArc(3, 0, 10); G1.InsertArc(3, 5, 10); G1.InsertArc(4, 2, 10); G1.InsertArc(4, 3, 10);
	G1.InsertArc(4, 5, 10);
	TopSort(G1);
}
void test04()
{
	char charray[4] = { 'A','B','C','D' };
	AdjListDirNetwork<char, int> G1(charray, 4);
	G1.InsertArc(0, 1, 54); G1.InsertArc(0, 2, 19); G1.InsertArc(0, 3, 12); G1.InsertArc(1, 2, 18); G1.InsertArc(2, 0, 15);
	G1.InsertArc(3, 0, 23); G1.InsertArc(3, 1, 6); G1.InsertArc(3, 2, 42);
	G1.testprint();
	int** dist = new int* [4]; int** path = new int* [4];
	for (int i = 0; i < 4; i++) {
		dist[i] = new int[4]; path[i] = new int[4];
	}
	ShortestPathFloyd(G1, path, dist);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << path[i][j] << " ";
		}
		cout << endl;
	}
	Floyd_DisplayPathAndDist(G1, path, dist);
}
void test03()
{
	char charray[7] = { 'A','B','C','D','E','F','G' };
	AdjListDirNetwork<char, int> G1(charray, 7);
	G1.InsertArc(0, 1, 60); G1.InsertArc(0, 2, 50); G1.InsertArc(0, 3, 50); G1.InsertArc(1, 4, -10); G1.InsertArc(2, 1, -20);
	G1.InsertArc(2, 4, 10); G1.InsertArc(2, 6, 70); G1.InsertArc(3, 2, -20); G1.InsertArc(3, 5, -10); G1.InsertArc(4, 6, 30);
	G1.InsertArc(5, 6, 30);
	G1.testprint();
	int dist[7]; int path[7];
	ShortestPathBellmanFord(G1, 0, path, dist);
	for (int i = 0; i < 7; i++) {
		cout << "\t" << dist[i];
	}
	cout << endl;
	for (int i = 0; i < 7; i++) {
		cout << "\t" << path[i];
	}
	cout << endl;
	DisplayPathAndDist(G1, 0, path, dist);
}

void test02()
{
	char charray[5] = { 'A','B','C','D','E' };
	AdjListDirNetwork<char, int> G1(charray, 5);
	G1.InsertArc(0, 1, 10); G1.InsertArc(0, 3, 30); G1.InsertArc(0, 4, 100); G1.InsertArc(1, 2, 50);
	G1.InsertArc(2, 4, 10); G1.InsertArc(3, 2, 20); G1.InsertArc(3, 4, 60);
	G1.testprint();
	int dist[5]; int path[5];
	ShortestPathDij(G1, 0, path, dist);
	DisplayPathAndDist(G1, 0, path, dist);
}
void test01()
{
	int intarray[7] = { 0,1,2,3,4,5,6 };
	AdjListDirNetwork<int, int> G1(intarray, 7);
	G1.InsertArc(0, 1, 8); G1.InsertArc(0, 3, 4); G1.InsertArc(0, 4, 5);
	G1.InsertArc(1, 2, 3); G1.InsertArc(2, 6, 6); G1.InsertArc(3, 4, 1);
	G1.InsertArc(4, 1, 2); G1.InsertArc(4, 2, 7); G1.InsertArc(4, 5, 2);
	G1.InsertArc(5, 2, 3); G1.InsertArc(5, 6, 9);
	G1.InsertVex(7);
	G1.testprint();
	cout << "请输入始点i的顶点值Vi: " << endl; int i; cin >> i;
	cout << "请输入终点j的顶点值Vj: " << endl; int j; cin >> j;
	if (i == j) {
		cout << "该有向网不允许环!" << endl;
	}
	else {
		//minalpath_dfs_pointtopoint(G1, i, j);
		IsConnected(G1, i, j);
	}
}