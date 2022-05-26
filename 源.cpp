#include"binary.h"
#include"AVL.h"
#include"RBTree.h"
#include"BTree.h"
#include"B_Plus_Tree.h"
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define seed 50
#define sphere 100


void func(int* arr, int algorithm, int n, int operation)
{
	//控制函数，调用不同子文件中的函数
	switch (algorithm) {
	case 1:
		binary(arr, algorithm, n, operation);
		break;
	case 2:
		AVL(arr, algorithm, n, operation);
		break;
	case 3:
		RB(arr, algorithm, n, operation);
		break;
	case 4:
		B(arr, algorithm, n, operation);
		break;
	case 5:
		B_Plus(arr, algorithm, n, operation);
		break;
	default:
		cout << "重新输入!" << endl;
	}
	return;
}

int main()
{
	int n, operation;
	//cout << "输入数据规模、操作（插入=1，删除=2，搜索=3）" << endl;
	//cin >> n >> operation;
	cin >> n;
	srand(seed);
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		arr[i] = (rand() % (sphere - 1) + 1);
	for (int algorithm = 1; algorithm < 6; algorithm++)
		for (int operation = 1; operation < 4; operation++)
			func(arr, algorithm, n, operation);
	//func(arr, 3, n, operation);
	return 0;
}