#pragma once
#include<stdio.h>

class B_Plus_Tree {
public:
	B_Plus_Tree** child = new B_Plus_Tree * [6]{ NULL, NULL, NULL, NULL, NULL };			//��������������Ȳ����ٴ���
	B_Plus_Tree* parent = NULL;
	B_Plus_Tree* link_list_pointer = NULL;
	int which_child = 0;			//�ڼ�������
	int* value = new int[5]();		//��������������Ȳ����ٴ���
	bool is_leaf = true;
	int value_num = 0;
};


void B_Plus(int* arr, int algorithm, int n, int operation);