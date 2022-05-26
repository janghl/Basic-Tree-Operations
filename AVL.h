#pragma once
#include<stdio.h>
#include<algorithm>
using namespace std;

class AVL_Tree {
public:
	AVL_Tree* lchild = NULL;
	AVL_Tree* parent = NULL;
	AVL_Tree* rchild = NULL;
	int value = 0;
	int height = 1;
	int balance_factor = 0;
	bool left = true;		//是左孩子还是右孩子
	void update_height()
	{													//输入插入的叶子节点的父节点
		AVL_Tree* node = this;
		while (node != NULL)
		{
			if (node->lchild == NULL)
			{
				if (node->rchild == NULL)
				{
					node->height = 1;
					node->balance_factor = 0;
					node = node->parent;
					continue;
				}
				else
				{
					node->height = node->rchild->height + 1;
					node->balance_factor = -node->rchild->height;
					node = node->parent;
					continue;
				}
			}
			else
			{
				if(node->rchild == NULL)
				{
					node->height = node->lchild->height + 1;
					node->balance_factor = node->lchild->height;
					node = node->parent;
					continue;
				}
				else
				{
					node->height = max(node->lchild->height, node->rchild->height);
					node->balance_factor = node->lchild->height - node->rchild->height;
					node = node->parent;
					continue;
				}
			}
		}
		return;
	}
	bool legal()
	{
		if (balance_factor == 1 || balance_factor == 0 || balance_factor == -1)
			return true;
		else
			return false;
	}		

};


void AVL(int* arr, int algorithm, int n, int operation);