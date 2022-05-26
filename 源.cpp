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
	//���ƺ��������ò�ͬ���ļ��еĺ���
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
		cout << "��������!" << endl;
	}
	return;
}

int main()
{
	int n, operation;
	//cout << "�������ݹ�ģ������������=1��ɾ��=2������=3��" << endl;
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