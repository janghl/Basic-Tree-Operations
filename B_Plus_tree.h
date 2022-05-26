#pragma once
#include<stdio.h>

class B_Plus_Tree {
public:
	B_Plus_Tree** child = new B_Plus_Tree * [6]{ NULL, NULL, NULL, NULL, NULL };			//如果超出数量，先插入再处理
	B_Plus_Tree* parent = NULL;
	B_Plus_Tree* link_list_pointer = NULL;
	int which_child = 0;			//第几个孩子
	int* value = new int[5]();		//如果超出数量，先插入再处理
	bool is_leaf = true;
	int value_num = 0;
};


void B_Plus(int* arr, int algorithm, int n, int operation);