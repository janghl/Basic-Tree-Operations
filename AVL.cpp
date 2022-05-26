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
	//����������T1-T3����ĺ����ppt����ͬ��mytree�Ǹ��ڵ㣬node��ʾԭ���ĸ��ڵ�
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
	//���Ĵ�ӡ������csdn
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
	//newAVL_Tree��ʾ������ڵ㣬AVL_Tree_pointerѰ�Ҳ���λ�ã��ҵ���С������������������ת
	AVL_Tree* newAVL_Tree = new AVL_Tree;
	AVL_Tree* AVL_Tree_pointer = mytree;
	newAVL_Tree->value = value;
	while (1)
	{
		AVL_Tree_pointer->height++;				//���滹�����
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
		newAVL_Tree = newAVL_Tree->parent;				//��С��������newAVL_Tree->parent->parent
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
	//�������������������һ��
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
	//ͨ���������������ϵ���ƽ������
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
	//�ڶ��������������ϼ���fixup������ƽ������
	AVL_Tree* to_be_deleted = AVL_search(mytree, value);
	if (to_be_deleted == NULL)  //�Ҳ���
		return;
	AVL_Tree* parent = to_be_deleted->parent;
	if (to_be_deleted->rchild == NULL)
	{
		if (to_be_deleted->lchild == NULL)		//Ҷ��
		{
			if (to_be_deleted->left == true)
				to_be_deleted->parent->lchild = NULL;
			else
				to_be_deleted->parent->rchild = NULL;
			AVL_delete_fix(parent);
			return;
		}
		else									//ֻ������
		{
			if (to_be_deleted->left == true)
				to_be_deleted->parent->lchild = to_be_deleted->lchild;
			else
				to_be_deleted->parent->rchild = to_be_deleted->lchild;
			AVL_delete_fix(parent);
			return;
		}

	}
	else if (to_be_deleted->lchild == NULL)				//ֻ���Һ���
	{
		if (to_be_deleted->left == true)
			to_be_deleted->parent->lchild = to_be_deleted->rchild;
		else
			to_be_deleted->parent->rchild = to_be_deleted->rchild;
		AVL_delete_fix(parent);
		return;
	}
	else														//��������
	{
		if (to_be_deleted->rchild->lchild == NULL)				//������Һ���
		{
			to_be_deleted->value = to_be_deleted->rchild->value;
			to_be_deleted->rchild = to_be_deleted->rchild->rchild;
			AVL_delete_fix(to_be_deleted);
			return;
		}
		else													//���������
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
	//ͨ��n�β���ʵ�����Ľ���
	AVL_Tree* mytree = new AVL_Tree;
	mytree->value = arr[0];
	for (int i = 1; i < n; i++) {
		AVL_insert(mytree, arr[i]);
	}
	return mytree;
}



void AVL(int* arr, int algorithm, int n, int operation)
{
	//���ƺ��������ܰ�����ʱ�����Ľ����Լ����룬ɾ��������
	clock_t start, end;
	start = clock();
	AVL_Tree* root = AVL_build(arr, n);
	char temp[128];
	//tree_print(root, 0, temp);
	int value;
	switch (operation) {
	case 1:
		//cout << "����Ҫ�������" << endl;
	//	cin >> value;
		AVL_insert(root, 12);
		break;
	case 2:
	//	cout << "����Ҫɾ������" << endl;
	//	cin >> value;
		AVL_delete(root, 62);
		break;
	case 3:
		//cout << "����Ҫ��������" << endl;
		//cin >> value;
		AVL_search(root, 11);
		break;
	default:
		cout << "��������!" << endl;
	}
	end = clock();
	cout << "algorithm = " << algorithm << "    operation = " << operation << "    time = " << double(end - start) << "units" << endl;

	//tree_print(root, 0, temp);
}


