#pragma once
#include"AVL.h"
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void AVL_left_rotate(AVL_Tree* mytree)
{
	//左旋操作，T1-T3代表的含义和ppt上相同，mytree是根节点，node表示原来的根节点
	AVL_Tree* node = mytree;
	AVL_Tree* T1 = mytree->lchild;
	AVL_Tree* T2 = mytree->rchild->lchild;
	AVL_Tree* T3 = mytree->rchild->rchild;
	mytree = mytree->rchild;
	mytree->parent = node->parent;
	mytree->rchild = T3;
	mytree->lchild = node;
	node->lchild = T1;
	node->rchild = T2;
	node->parent = mytree;
	T1->parent = T2->parent = node;
	T3->parent = mytree;
	node->update_height();
	mytree = node;
}

void AVL_right_rotate(AVL_Tree* mytree)
{
	AVL_Tree* node = mytree;
	AVL_Tree* T1 = mytree->lchild->lchild;
	AVL_Tree* T2 = mytree->lchild->rchild;
	AVL_Tree* T3 = mytree->rchild;
	mytree = mytree->lchild;
	mytree->parent = node->parent;
	mytree->lchild = T1;
	mytree->rchild = node;
	node->lchild = T2;
	node->rchild = T3;
	node->parent = mytree;
	T3->parent = T2->parent = node;
	T1->parent = mytree;
	node->update_height();
	mytree = node;
}


void tree_print(AVL_Tree* mytree, int level, char* temp)
{
	//树的打印，来自csdn
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


void AVL_insert(AVL_Tree* mytree, int value)
{
	//newAVL_Tree表示待插入节点，AVL_Tree_pointer寻找插入位置，找到最小子树根后分四种情况旋转
	AVL_Tree* newAVL_Tree = new AVL_Tree;
	AVL_Tree* AVL_Tree_pointer = mytree;
	newAVL_Tree->value = value;
	while (1)
	{
		AVL_Tree_pointer->height++;				//后面还会更新
		if (value <= AVL_Tree_pointer->value)
		{
			if (AVL_Tree_pointer->lchild == NULL)
			{
				AVL_Tree_pointer->lchild = newAVL_Tree;
				newAVL_Tree->parent = AVL_Tree_pointer;
				return;
			}
			else
				AVL_Tree_pointer = AVL_Tree_pointer->lchild;
		}
		else
		{
			if (AVL_Tree_pointer->rchild == NULL)
			{
				AVL_Tree_pointer->rchild = newAVL_Tree;
				newAVL_Tree->parent = AVL_Tree_pointer;
				newAVL_Tree->left = false;
				return;
			}
			else
				AVL_Tree_pointer = AVL_Tree_pointer->rchild;
		}
	}
	AVL_Tree_pointer->update_height();
	while (newAVL_Tree->parent->parent->legal() == true&& newAVL_Tree->parent->parent !=NULL)
		newAVL_Tree = newAVL_Tree->parent;				//最小子树根是newAVL_Tree->parent->parent
	if (newAVL_Tree->parent->parent == NULL)
		return;
	else
	{
		if (newAVL_Tree->left == true && newAVL_Tree->parent->left == true)
			AVL_right_rotate(newAVL_Tree);
		else if (newAVL_Tree->parent->left == true && newAVL_Tree->left == false)
		{
			AVL_left_rotate(newAVL_Tree->lchild);
			AVL_right_rotate(newAVL_Tree);
		}
		else if (newAVL_Tree->parent->left == false && newAVL_Tree->left == false)
			AVL_left_rotate(newAVL_Tree);
		else if (newAVL_Tree->parent->left == false && newAVL_Tree->left == true)
		{
			AVL_right_rotate(newAVL_Tree->rchild);
			AVL_left_rotate(newAVL_Tree);
		}
	}
}

AVL_Tree* AVL_search(AVL_Tree* mytree, int value)
{
	//搜索操作与二叉搜索树一致
	if (mytree == NULL)
	{
		cout << "cannot find!" << endl;
		return NULL;
	}
	if (mytree->value == value)
		return mytree;
	else if (mytree->value < value)
		return AVL_search(mytree->rchild, value);
	else
		return AVL_search(mytree->lchild, value);
}


void AVL_delete_fix(AVL_Tree* node)
{
	//通过左旋和右旋向上调整平衡因子
	node->update_height();
	while (node != NULL)
	{
		if (node->legal() == false)
		{
			if (node->balance_factor > 0)
				AVL_right_rotate(node);
			else
				AVL_left_rotate(node);
		}
		node = node->parent;

	}
	return;
}



void AVL_delete(AVL_Tree* mytree, int value)
{
	//在二叉搜索树基础上加入fixup，调整平衡因子
	AVL_Tree* to_be_deleted = AVL_search(mytree, value);
	if (to_be_deleted == NULL)  //找不到
		return;
	AVL_Tree* parent = to_be_deleted->parent;
	if (to_be_deleted->rchild == NULL)
	{
		if (to_be_deleted->lchild == NULL)		//叶子
		{
			if (to_be_deleted->left == true)
				to_be_deleted->parent->lchild = NULL;
			else
				to_be_deleted->parent->rchild = NULL;
			AVL_delete_fix(parent);
			return;
		}
		else									//只有左孩子
		{
			if (to_be_deleted->left == true)
				to_be_deleted->parent->lchild = to_be_deleted->lchild;
			else
				to_be_deleted->parent->rchild = to_be_deleted->lchild;
			AVL_delete_fix(parent);
			return;
		}

	}
	else if (to_be_deleted->lchild == NULL)				//只有右孩子
	{
		if (to_be_deleted->left == true)
			to_be_deleted->parent->lchild = to_be_deleted->rchild;
		else
			to_be_deleted->parent->rchild = to_be_deleted->rchild;
		AVL_delete_fix(parent);
		return;
	}
	else														//两个孩子
	{
		if (to_be_deleted->rchild->lchild == NULL)				//后继是右孩子
		{
			to_be_deleted->value = to_be_deleted->rchild->value;
			to_be_deleted->rchild = to_be_deleted->rchild->rchild;
			AVL_delete_fix(to_be_deleted);
			return;
		}
		else													//后继是其它
		{
			AVL_Tree* next_node = to_be_deleted->rchild;
			while (next_node->lchild != NULL)
				next_node = next_node->lchild;
			to_be_deleted->value = next_node->value;
			if (next_node->rchild == NULL)
				next_node->parent == NULL;
			else
			{
				next_node->value = next_node->rchild->value;
				next_node->rchild = next_node->rchild->rchild;
			}
			//AVL_delete_fix(next_node);
			return;

		}
	}
}




AVL_Tree* AVL_build(int* arr, int n)
{
	//通过n次插入实现树的建造
	AVL_Tree* mytree = new AVL_Tree;
	mytree->value = arr[0];
	for (int i = 1; i < n; i++) {
		AVL_insert(mytree, arr[i]);
	}
	return mytree;
}



void AVL(int* arr, int algorithm, int n, int operation)
{
	//控制函数，功能包括计时，树的建造以及插入，删除，搜索
	clock_t start, end;
	start = clock();
	AVL_Tree* root = AVL_build(arr, n);
	char temp[128];
	//tree_print(root, 0, temp);
	int value;
	switch (operation) {
	case 1:
		//cout << "输入要插入的数" << endl;
	//	cin >> value;
		AVL_insert(root, 12);
		break;
	case 2:
	//	cout << "输入要删除的数" << endl;
	//	cin >> value;
		AVL_delete(root, 62);
		break;
	case 3:
		//cout << "输入要搜索的数" << endl;
		//cin >> value;
		AVL_search(root, 11);
		break;
	default:
		cout << "重新输入!" << endl;
	}
	end = clock();
	cout << "algorithm = " << algorithm << "    operation = " << operation << "    time = " << double(end - start) << "units" << endl;

	//tree_print(root, 0, temp);
}


