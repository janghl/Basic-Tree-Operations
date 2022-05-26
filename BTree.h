#pragma once
#include<stdio.h>

class B_Tree {
public:
	B_Tree** child = new B_Tree * [6] { NULL, NULL, NULL, NULL, NULL };			//如果超出数量，先插入再处理
	B_Tree* parent = NULL;
	int which_child = 0;			//第几个孩子
	int* value = new int[5]();		//如果超出数量，先插入再处理
	bool is_leaf = true;
	int value_num = 0;
};


void B(int* arr, int algorithm, int n, int operation);