#pragma once
#include<stdio.h>
#include<algorithm>
using namespace std;

class RB_Tree {
public:
	RB_Tree* lchild = NULL;
	RB_Tree* parent = NULL;
	RB_Tree* rchild = NULL;
	int value = 0;
	int black = true;
	bool left = true;		//�����ӻ����Һ���
};


void RB(int* arr, int algorithm, int n, int operation);