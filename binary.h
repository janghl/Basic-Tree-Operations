#pragma once
#include<stdio.h>

class Binary_Tree {
public:
	Binary_Tree* lchild = NULL;
	Binary_Tree* parent = NULL;
	Binary_Tree* rchild = NULL;
	int value = 0;
};


void binary(int* arr, int algorithm, int n, int operation);