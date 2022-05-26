#pragma once
#include"binary.h"
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void tree_print(Binary_Tree* mytree, int level, char* temp)
{
	//csdn
	int i;
	if (level < 127) {
		for (i = 1; i < level; ++i) {
			printf(temp[i] ? "| " : "  ");
		}
		if (level) {
			printf("+-");
		}
		if (mytree == NULL) {
			printf("\n");
		}
		else {
			printf("%d\n", mytree->value);
			if (mytree->lchild != NULL || mytree->rchild != NULL) {
				temp[level + 1] = 1;
				tree_print(mytree->rchild, level + 1, temp);
				temp[level + 1] = 0;
				tree_print(mytree->lchild, level + 1, temp);
			}
		}
	}
	return;
}


void binary_insert(Binary_Tree* mytree, int value)
{
	//newAVL_Tree表示待插入节点，AVL_Tree_pointer寻找插入位置，直接用新节点代替叶子节点
	Binary_Tree* newBinary_Tree = new Binary_Tree;
	Binary_Tree* Binary_Tree_pointer = mytree;
	newBinary_Tree->value = value;
	while (1)
	{
		if (value <= Binary_Tree_pointer->value)
		{
			if (Binary_Tree_pointer->lchild == NULL)
			{
				Binary_Tree_pointer->lchild = newBinary_Tree;
				newBinary_Tree->parent = Binary_Tree_pointer;
				return;
			}
			else
				Binary_Tree_pointer = Binary_Tree_pointer->lchild;
		}
		else
		{
			if (Binary_Tree_pointer->rchild == NULL)
			{
				Binary_Tree_pointer->rchild = newBinary_Tree;
				newBinary_Tree->parent = Binary_Tree_pointer;
				return;
			}
			else
				Binary_Tree_pointer = Binary_Tree_pointer->rchild;
		}
	}

}

Binary_Tree* binary_search(Binary_Tree* mytree, int value)
{
	//递归前序遍历查找，找不到会返回提示
	if (mytree == NULL)
	{
		cout << "cannot find!" << endl;
		return NULL;
	}
	if (mytree->value == value)
		return mytree;
	else if (mytree->value < value)
		return binary_search(mytree->rchild, value);
	else
		return binary_search(mytree->lchild, value);
}


void binary_delete(Binary_Tree* mytree, int value)
{
	//先搜索待删除节点，如果是叶子直接删除，如果只有左孩子或右孩子，则用左孩子和右孩子代替他本身
	//如果有两个孩子，且后继是右孩子（表示右孩子没有左孩子），直接用后继代替他本身
	//如果右孩子有左孩子，找到后继，用后继代替本身，再用后继的右子树代替后继
	Binary_Tree* to_be_deleted = binary_search(mytree, value);
	if (to_be_deleted == NULL)  //找不到
		return;
	if (to_be_deleted->rchild == NULL)
	{
		if (to_be_deleted->lchild == NULL)		//叶子
		{
			if (to_be_deleted->value == to_be_deleted->parent->lchild->value)
				to_be_deleted->parent->lchild = NULL;
			else
				to_be_deleted->parent->rchild = NULL;
			return;
		}
		else									//只有左孩子
		{
			if (to_be_deleted->value == to_be_deleted->parent->lchild->value)
				to_be_deleted->parent->lchild = to_be_deleted->lchild;
			else
				to_be_deleted->parent->rchild = to_be_deleted->lchild;
			return;
		}

	}
	else if (to_be_deleted->lchild == NULL)				//只有右孩子
	{
		if (to_be_deleted->value == to_be_deleted->parent->lchild->value)
		{
			to_be_deleted->parent->lchild = to_be_deleted->rchild;
			to_be_deleted->rchild->parent = to_be_deleted->parent;
		}
		else
		{
			to_be_deleted->parent->rchild = to_be_deleted->rchild;
			to_be_deleted->rchild->parent = to_be_deleted->parent;
		}
		return;
	}
	else														//两个孩子
	{
		if (to_be_deleted->rchild->lchild == NULL)				//后继是右孩子
		{
			to_be_deleted->value = to_be_deleted->rchild->value;
			to_be_deleted->rchild = to_be_deleted->rchild->rchild;
			to_be_deleted->rchild->parent = to_be_deleted;
			return;
		}
		else													//后继是其它
		{
			Binary_Tree* next_node = to_be_deleted->rchild;
			while (next_node->lchild != NULL)
				next_node = next_node->lchild;
			to_be_deleted->value = next_node->value;
			if (next_node->rchild == NULL)
				next_node->parent == NULL;
			else
			{
				next_node->value = next_node->rchild->value;
				next_node->rchild = next_node->rchild->rchild;
				next_node->rchild->parent = next_node;
			}
			return;

		}
	}
}





Binary_Tree* binary_build(int* arr, int n)
{
	//通过n次插入实现树的建造
	Binary_Tree* mytree = new Binary_Tree;
	mytree->value = arr[0];
	for (int i = 1; i < n; i++) {
		binary_insert(mytree, arr[i]);
	}
	return mytree;
}



void binary(int* arr, int algorithm, int n, int operation)
{
	//控制函数，功能包括计时，树的建造以及插入，删除，搜索
	clock_t start, end;
	start = clock();
	Binary_Tree* root = binary_build(arr, n);
	char temp[128];
	//tree_print(root, 0, temp);
	int value;
	switch (operation) {
	case 1:
		//cout << "输入要插入的数" << endl;
		//cin >> value;
		binary_insert(root, 12);
		break;
	case 2:
		//cout << "输入要删除的数" << endl;
		//cin >> value;
		binary_delete(root, 62);
		break;
	case 3:
		//cout << "输入要搜索的数" << endl;
		//cin >> value;
		binary_search(root, 11);
		break;
	default:
		cout << "重新输入!" << endl;
	}
	end = clock();
	cout << "algorithm = " << algorithm << "    operation = " << operation << "    time = " << double(end - start) << "units" << endl;

	//tree_print(root, 0, temp);
}


