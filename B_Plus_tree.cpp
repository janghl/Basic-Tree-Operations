#pragma once
#include"B_Plus_Tree.h"
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
B_Plus_Tree* pre_leaf = NULL;				//ǰ���������������

void tree_print(B_Plus_Tree* mytree, int level, char* temp)
{
	//����B������
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
			int flag = 0;
			for(int i=0;i<mytree->value_num;i++)
				printf("%d\n", mytree->value[i]);
			for (int i = 0; i < mytree->value_num + 1; i++)
				if (mytree->child[i] != NULL)
					flag = 1;
			if(flag==1)
				temp[level + 1] = 1;
				tree_print(mytree->child[i], level + 1, temp);
			
		}
	}
	return;
}

void make_chain(B_Plus_Tree* root)
{
	//��ͷ��ʼǰ�������ȷ��ÿ��Ҷ��ָ����һ��Ҷ�ӽڵ�
	if (root->is_leaf == true)
	{
		if (pre_leaf != NULL)
			pre_leaf->link_list_pointer = root;
		pre_leaf = root;
		return;
	}
	for (int i = 0; i < 5; i++)
		if (root->child[i] != NULL)
			make_chain(root->child[i]);
	return;
}


void sort(B_Plus_Tree* mytree)			
{
	//����B������
	int* a = mytree->value;
	for (int j = 1; j < 4; j++)
	{
		int key = a[j];
		int i = j - 1;
		while (i >= 0 && a[i] > key)
		{
			a[i + 1] = a[i];
			i--;
		}
		a[i + 1] = key;
	}
	int zero = 0;
	for (int j = 0; j < 4; j++)
		if (a[j] == 0)
			zero++;
	for (int j = zero; j < 4; j++)
		a[j - zero] = a[j];
	for (int j = 4 - zero; j < 4; j++)
		a[j] = 0;
	return;
}

void crack(B_Plus_Tree* node, B_Plus_Tree* root)
{
	//����B������
	if (node->which_child == 0)
	{
		B_Plus_Tree* left_node = new B_Plus_Tree;
		B_Plus_Tree* right_node = new B_Plus_Tree;
		B_Plus_Tree* root = new B_Plus_Tree;
		root->is_leaf = false;
		root->value_num = 1;
		root->value[0] = node->value[2];
		root->child[0] = left_node;
		root->child[1] = right_node;
		left_node->which_child = 0;
		left_node->is_leaf = false;
		left_node->value_num = 2;
		left_node->value[0] = node->value[0];
		left_node->value[1] = node->value[1];
		left_node->value[2] = node->value[2];			//��ԭ������parent�ģ����ڷ�����߽ڵ㣬��parent����Ȼ��������������
		left_node->child[0] = node->child[0];
		left_node->child[1] = node->child[1];
		left_node->child[2] = node->child[2];
		left_node->parent = root;
		right_node->which_child = 1;
		right_node->is_leaf = false;
		right_node->value_num = 2;
		right_node->value[0] = node->value[3];
		right_node->value[1] = node->value[4];
		right_node->child[0] = node->child[3];
		right_node->child[1] = node->child[4];
		right_node->child[2] = node->child[5];
		right_node->parent = root;
		return;
	}
	int temp = node->which_child;
	B_Plus_Tree* left_node = new B_Plus_Tree;
	B_Plus_Tree* right_node = new B_Plus_Tree;
	B_Plus_Tree* parent = new B_Plus_Tree;
	parent = node->parent;
	parent->value_num++;
	for (int i = parent->value_num - 1; i > temp; i--)
		parent->value[i] = parent->value[i - 1];
	for (int i = parent->value_num; i > temp + 1; i--)
		parent->child[i] = parent->child[i - 1];
	parent->value[temp] = node->value[2];
	parent->child[temp] = left_node;
	parent->child[temp + 1] = right_node;
	left_node->which_child = temp;
	left_node->is_leaf = node->is_leaf;
	left_node->value_num = 2;
	left_node->value[0] = node->value[0];
	left_node->value[1] = node->value[1];
	left_node->value[2] = node->value[2];
	left_node->child[0] = node->child[0];
	left_node->child[1] = node->child[1];
	left_node->child[2] = node->child[2];
	left_node->parent = parent;
	right_node->which_child = temp + 1;
	right_node->is_leaf = node->is_leaf;
	right_node->value_num = 2;
	right_node->value[0] = node->value[3];
	right_node->value[1] = node->value[4];
	right_node->child[0] = node->child[3];
	right_node->child[1] = node->child[4];
	right_node->child[2] = node->child[5];
	right_node->parent = parent;
	if (node->parent->value_num > 4)
		crack(node->parent, root);
	return;

}


void B_Plus_insert(B_Plus_Tree* mytree, int value)
{
	//����B�����룬�м�ڵ���ֵ����ֻ��Ϊ��ȷ����Χ����������key
	int i;
	B_Plus_Tree* leaf = mytree;
	while (leaf->is_leaf != true)		//�ҵ�Ҷ�ӽڵ�
	{
		i = 0;
		while (i < leaf->value_num && value > leaf->value[i])
			i++;
		leaf = leaf->child[i];
	}
	leaf->value[leaf->value_num] = value;
	sort(leaf);
	leaf->value_num++;
	if (leaf->value_num < 5)
	{
		make_chain(mytree);
		return;
	}
	crack(leaf, mytree);			//������ڵ�mytree,��ֹ�����¸��ڵ�
	make_chain(mytree);
	return;
}

B_Plus_Tree* B_Plus_search(B_Plus_Tree* mytree, int value)
{
	//����B������
	if (mytree == NULL)
	{
		cout << "cannot find!" << endl;
		return NULL;
	}
	int i = 0;
	while (i < mytree->value_num&& value >= mytree->value[i])
	{
			if (mytree->value[i] == value)
				return mytree;
			else
				i++;
	}
	return B_Plus_search(mytree->child[i], value);
}

B_Plus_Tree* find_redundant_leaf(B_Plus_Tree* mytree)
{
	//����B������
	if(mytree==NULL)
		return NULL;
	if (mytree->is_leaf == true && mytree->value_num > 2)
		return mytree;
	for (int i = 0; i < 5; i++)
		if (find_redundant_leaf(mytree->child[i]) != NULL)
			return find_redundant_leaf(mytree->child[i]);
	return NULL;


}


	

void B_Plus_delete(B_Plus_Tree* mytree, int value)
{
	//����B������
	B_Plus_Tree* to_be_deleted = B_Plus_search(mytree, value);
	if (to_be_deleted == NULL)
		return;
	int temp = 0;						//�ȿ����м�ڵ�����
	B_Plus_Tree* temp_node = new B_Plus_Tree;
	temp_node = to_be_deleted;
	while (value > to_be_deleted->value[temp])
		temp++;
	int place = temp;					//����value��to_be_deleted�ĵڼ���Ԫ��
	while (temp_node->is_leaf == false)  
	{
		while (value > to_be_deleted->value[temp])
			temp++;
		temp_node = temp_node->child[temp];
	}
	if (to_be_deleted->is_leaf == false)
	{
		temp = temp_node->value[0];
		temp_node->value[0] = to_be_deleted->value[place];
		to_be_deleted->value[place] = temp;
		to_be_deleted = temp_node;	//�����б�֤���������������to_be_deleted[temp]
		temp = 0;
	}
			
	//����Ҷ�ӽڵ�
	to_be_deleted->value[temp] = 0;
	to_be_deleted->value_num--;
	if (to_be_deleted->value_num == 0)
	{
		to_be_deleted->parent->child[to_be_deleted->which_child] = NULL;
		make_chain(mytree);
	}
	sort(to_be_deleted);
	if (to_be_deleted->value_num >= 2)
		return;
	temp_node = find_redundant_leaf(mytree);		//������Ҷ�ӽڵ���
	if (temp_node != NULL)
	{
		temp = temp_node->value[0];
		temp_node->value[0] = to_be_deleted->value[4];
		to_be_deleted->value[4] = temp;
		temp_node->value_num--;
		to_be_deleted->value_num++;
		sort(to_be_deleted);
		sort(temp_node);
		return;
	}
}





B_Plus_Tree* build(int* arr, int n)
{
	B_Plus_Tree* mytree = new B_Plus_Tree;
	mytree->value[0] = arr[0];
	mytree->value_num = 1;
	for (int i = 1; i < n; i++) {
		B_Plus_insert(mytree, arr[i]);
	}
	return mytree;
}



void B_Plus(int* arr, int algorithm, int n, int operation)
{
	clock_t start, end;
	start = clock();
	B_Plus_Tree* root = new B_Plus_Tree;
	root = build(arr, n);
	char temp[128];
	//tree_print(root, 0, temp);
	int value;
	switch (operation) {
	case 1:
		//cout << "����Ҫ�������" << endl;
		//cin >> value;
		B_Plus_insert(root, 12);
		break;
	case 2:
		//cout << "����Ҫɾ������" << endl;
		//cin >> value;
		B_Plus_delete(root, 62);
		break;
	case 3:
		//cout << "����Ҫ��������" << endl;
		//cin >> value;
		B_Plus_search(root, 11);
		break;
	default:
		cout << "��������!" << endl;
	}
	end = clock();
	cout << "algorithm = " << algorithm << "    operation = " << operation << "    time = " << double(end - start) << "units" << endl;
	//tree_print(root, 0, temp);
	

}


