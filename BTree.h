#pragma once
#include<stdio.h>

class B_Tree {
public:
	B_Tree** child = new B_Tree * [6] { NULL, NULL, NULL, NULL, NULL };			//��������������Ȳ����ٴ���
	B_Tree* parent = NULL;
	int which_child = 0;			//�ڼ�������
	int* value = new int[5]();		//��������������Ȳ����ٴ���
	bool is_leaf = true;
	int value_num = 0;
};


void B(int* arr, int algorithm, int n, int operation);