#pragma once
#include"RBTree.h"
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
extern RB_Tree* nil = new RB_Tree;

void RB_left_rotate(RB_Tree* mytree)
{
	//与AVL树类似，但是不需要更新平衡因子
	RB_Tree* node = mytree;
	RB_Tree* T1 = mytree->lchild;
	RB_Tree* T2 = mytree->rchild->lchild;
	RB_Tree* T3 = mytree->rchild->rchild;
	mytree = mytree->rchild;
	mytree->parent = node->parent;
	mytree->rchild = T3;
	mytree->lchild = node;
	node->lchild = T1;
	node->rchild = T2;
	node->parent = mytree;
	T1->parent = T2->parent = node;
	T3->parent = mytree;
	mytree = node;
}

void RB_right_rotate(RB_Tree* mytree)
{
	RB_Tree* node = mytree;
	RB_Tree* T1 = mytree->lchild->lchild;
	RB_Tree* T2 = mytree->lchild->rchild;
	RB_Tree* T3 = mytree->rchild;
	mytree = mytree->lchild;
	mytree->parent = node->parent;
	mytree->lchild = T1;
	mytree->rchild = node;
	node->lchild = T2;
	node->rchild = T3;
	node->parent = mytree;
	T3->parent = T2->parent = node;
	T1->parent = mytree;
	mytree = node;
}


void tree_print(RB_Tree* mytree, int level, char* temp)
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
		if (mytree->value == 0) {
			printf("\n");
		}
		else {
			printf("%d\n", mytree->value);
			if (mytree->lchild != nil || mytree->rchild != nil) {
				temp[level + 1] = 1;
				tree_print(mytree->rchild, level + 1, temp);
				temp[level + 1] = 0;
				tree_print(mytree->lchild, level + 1, temp);
			}
		}
	}
	return;
}



void RB_insert_fix(RB_Tree* node)
{							
	//分6种情况，如果叔叔是红色，把parent和叔叔涂黑，爷爷变红
	//如果叔叔是黑色，本身是左孩子的左孩子，需要一次旋转
	//如果叔叔是黑色，本身是左孩子的右孩子，需要两次旋转
	//其余情况完全对称
	//深度至少为3，否则不会进入函数
	if (node->parent->value == 0)				//上升到根
	{
		node->black = false;
		return;
	}
	RB_Tree* uncle;
	if (node->parent->left)
	{
		uncle = node->parent->parent->rchild;
		if (!uncle->black)						// Case1：z的叔叔是红色
		{
			uncle->black = true;
			uncle->parent->black = false;
			node->parent->black = true;
			RB_insert_fix(uncle->parent);
		}
		else if (node->left)						 //Case3： z的叔叔是黑色，且z是双亲p[z]的左孩子
		{
			RB_Tree* temp = node->parent->parent;			//rotate传进去的指针被污染了
			RB_right_rotate(node->parent->parent);
			node->parent->parent = temp;
			node->parent->black = true;
			node->parent->rchild->black = false;
		}
		else											// Case2： z的叔叔是黑色，且z是双亲p[z]的右孩子
		{
			RB_Tree* temp = node->parent;					//rotate传进去的指针被污染了
			RB_left_rotate(node->parent);
			node->parent = temp;
			temp = node->parent->parent;					//rotate传进去的指针被污染了
			RB_right_rotate(node->parent->parent);
			node->parent->parent = temp;
			node->parent->black = true;
			node->parent->rchild->black = false;
		}
	}
	else
	{
		uncle = node->parent->parent->lchild;
		if (!uncle->black)						// Case4：z的叔叔是红色
		{
			uncle->black = true;
			uncle->parent->black = false;
			node->parent->black = true;
			RB_insert_fix(uncle->parent);
		}
		else if (node->left)						 //Case6： z的叔叔是黑色，且z是双亲p[z]的右孩子
		{
			RB_Tree* temp = node->parent->parent;			//rotate传进去的指针被污染了
			RB_left_rotate(node->parent->parent);
			node->parent->parent = temp;
			node->parent->black = true;
			node->parent->lchild->black = false;
		}
		else											// Case5： z的叔叔是黑色，且z是双亲p[z]的左孩子
		{
			RB_Tree* temp = node->parent;					//rotate传进去的指针被污染了
			RB_right_rotate(node->parent);
			node->parent = temp;
			temp = node->parent->parent;					//rotate传进去的指针被污染了
			RB_left_rotate(node->parent->parent);
			node->parent->parent = temp;
			node->parent->black = true;
			node->parent->lchild->black = false;
		}
	}




}


void RB_insert(RB_Tree* mytree, int value)
{	//在二叉搜索树的基础上加入fixup					//根节点默认就是黑的
	RB_Tree* newRB_Tree = new RB_Tree;
	newRB_Tree->lchild = newRB_Tree->rchild = nil;
	RB_Tree* RB_Tree_pointer = mytree;
	newRB_Tree->black = false;
	newRB_Tree->value = value;
	while (1)
	{
		if (value <= RB_Tree_pointer->value)
		{
			if (RB_Tree_pointer->lchild->value == 0)
			{
				RB_Tree_pointer->lchild = newRB_Tree;
				newRB_Tree->parent = RB_Tree_pointer;
				return;
			}
			else
				RB_Tree_pointer = RB_Tree_pointer->lchild;
		}
		else
		{
			if (RB_Tree_pointer->rchild->value == 0)
			{
				RB_Tree_pointer->rchild = newRB_Tree;
				newRB_Tree->parent = RB_Tree_pointer;
				newRB_Tree->left = false;
				return;
			}
			else
				RB_Tree_pointer = RB_Tree_pointer->rchild;
		}
	}
	if (newRB_Tree->parent->black == true)
		return;
	else
		RB_insert_fix(newRB_Tree);
}

RB_Tree* RB_search(RB_Tree* mytree, int value)
{
	//搜索操作与二叉搜索树一致
	if (mytree->value == 0)
	{
		cout << "cannot find!" << endl;
		return nil;
	}
	if (mytree->value == value)
		return mytree;
	else if (mytree->value < value)
		return RB_search(mytree->rchild, value);
	else
		return RB_search(mytree->lchild, value);
}

void RB_delete_fix(RB_Tree* node)
{
	//来自ppt
	RB_Tree* temp;
	RB_Tree* root = node;
	while (root->parent->value != 0)
		root = root->parent;
	while (node->parent != nil && node->black)
	{
		if (node->left)
		{
			temp = node->parent->rchild;
			if (!temp->black)
			{
				temp->black = true;
				node->parent->black = false;
				RB_left_rotate(node->parent);
				temp = node->parent->rchild;
			}
			if (temp->lchild->black && temp->rchild->black)
			{
				temp->black = false;
				node = node->parent;
			}
			else if (temp->rchild->black)
			{
				temp->lchild->black = true;
				temp->black = false;
				RB_right_rotate(temp);
				temp = node->parent->rchild;
			}
			temp->black = node->parent->black;
			node->parent->black = true;
			temp->rchild->black = true;
			RB_left_rotate(node->parent);
			node = root;
		}
		else
		{
			temp = node->parent->lchild;
			if (!temp->black)
			{
				temp->black = true;
				node->parent->black = false;
				RB_right_rotate(node->parent);
				temp = node->parent->lchild;
			}
			if (temp->rchild->black && temp->lchild->black)
			{
				temp->black = false;
				node = node->parent;
			}
			else if (temp->lchild->black)
			{
				temp->rchild->black = true;
				temp->black = false;
				RB_left_rotate(temp);
				temp = node->parent->lchild;
			}
			temp->black = node->parent->black;
			node->parent->black = true;
			temp->lchild->black = true;
			RB_right_rotate(node->parent);
			node = root;
		}
	}
	node->black = true;


}


void RB_delete(RB_Tree* mytree, int value)
{
	//来自ppt
	RB_Tree* to_be_deleted = RB_search(mytree, value); 
	RB_Tree* next_node = nil;        //ppt里的x
	RB_Tree* temp = nil;
	if (to_be_deleted->value == 0)  //找不到
		return;
	if (to_be_deleted->rchild->value == 0)
	{
		if (to_be_deleted->lchild->value == 0)		//叶子
		{
			if (to_be_deleted->left)
				to_be_deleted->parent->lchild = nil;
			else
				to_be_deleted->parent->rchild = nil;
		}
		else									//只有左孩子
		{
			next_node = to_be_deleted->lchild;
			if (to_be_deleted->left == true)
			{
				to_be_deleted->parent->lchild = to_be_deleted->lchild;
				to_be_deleted->lchild->parent = to_be_deleted->parent;
			}
			else
			{
				to_be_deleted->parent->rchild = to_be_deleted->lchild;
				to_be_deleted->lchild->parent = to_be_deleted->parent;
			}
		}

	}
	else if (to_be_deleted->lchild->value == 0)				//只有右孩子
	{
		next_node = to_be_deleted->rchild;
		if (to_be_deleted->left == true)
		{
			to_be_deleted->parent->lchild = to_be_deleted->rchild;
			to_be_deleted->rchild->parent = to_be_deleted->parent;
		}
		else
		{
			to_be_deleted->parent->rchild = to_be_deleted->rchild;
			to_be_deleted->rchild->parent = to_be_deleted->parent;
		}
	}
	else														//两个孩子
	{
		if (to_be_deleted->rchild->lchild->value == 0)				//后继是右孩子
		{
			next_node = to_be_deleted->rchild->rchild;
			to_be_deleted->value = to_be_deleted->rchild->value;
			to_be_deleted->rchild = to_be_deleted->rchild->rchild;
			to_be_deleted->rchild->parent = to_be_deleted;
		}
		else													//后继是其它
		{
			next_node = to_be_deleted->rchild;
			while (next_node->lchild != nil)
				next_node = next_node->lchild;
			to_be_deleted->value = next_node->value;
			if (next_node->rchild->value == 0)
			{
				temp = next_node->parent;
				next_node->parent->lchild = nil;
				next_node = temp;
			}
			else
			{
				next_node->value = next_node->rchild->value;
				next_node->rchild = next_node->rchild->rchild;
				next_node->rchild->parent = next_node;
			}
		}
		RB_delete_fix(next_node);
		return;
	}
}




RB_Tree* RB_build(int* arr, int n)
{
	//通过n次插入实现树的建造
	RB_Tree* mytree = new RB_Tree;
	mytree->parent = mytree->lchild = mytree->rchild = nil;
	mytree->value = arr[0];
	for (int i = 1; i < n; i++) {
		RB_insert(mytree, arr[i]);
	}
	return mytree;
}



void RB(int* arr, int algorithm, int n, int operation)
{
	//控制函数，功能包括计时，树的建造以及插入，删除，搜索
	clock_t start, end;
	start = clock();
	RB_Tree* root = RB_build(arr, n);
	char temp[128];
	//tree_print(root, 0, temp);
	int value;
	switch (operation) {
	case 1:
		//cout << "输入要插入的数" << endl;
		//cin >> value;
		RB_insert(root, 12);
		break;
	case 2:
		//cout << "输入要删除的数" << endl;
		//cin >> value;
		RB_delete(root, 62);
		break;
	case 3:
		//cout << "输入要搜索的数" << endl;
		//cin >> value;
		RB_search(root, 11);
		break;
	default:
		cout << "重新输入!" << endl;
	}
	end = clock();
	cout << "algorithm = " << algorithm << "    operation = " << operation << "    time = " << double(end - start) << "units" << endl;

	//tree_print(root, 0, temp);
}


