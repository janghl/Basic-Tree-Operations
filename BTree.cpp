#pragma once
#include"BTree.h"
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void tree_print(B_Tree* mytree, int level, char* temp)
{
	//ֱ�Ӹ���ԭ���Ĵ�ӡ�ģ�Ч����������
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


void sort(B_Tree* mytree)			
{
	//�ڵ��ڲ�ֵ���򣬵�ֻ������Ҷ�ӽڵ㣬��Ϊû�п��ǵ��ӽڵ����������
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

void crack(B_Tree* node, B_Tree* root)
{
	//��һ��key����Ŀ����5�Ľڵ�������
	if (node->which_child == 0)
	{
		B_Tree* left_node = new B_Tree;
		B_Tree* right_node = new B_Tree;
		B_Tree* root = new B_Tree;
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
	B_Tree* left_node = new B_Tree;
	B_Tree* right_node = new B_Tree;
	B_Tree* parent = new B_Tree;
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


void B_insert(B_Tree* mytree, int value)
{
	//����ʱ�ȸ�������������ֱ���ҵ�Ҷ�Ӳ��롣
	//�������󳬳���ģ�������crack
	int i;
	B_Tree* leaf = mytree;
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
		return;
	crack(leaf, mytree);			//������ڵ�mytree,��ֹ�����¸��ڵ�
	return;
}

B_Tree* B_search(B_Tree* mytree, int value)
{
	//����B���������������Բ���
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
	return B_search(mytree->child[i], value);
}

B_Tree* find_redundant_leaf(B_Tree* mytree)
{
	//����������Ҷ�ӽڵ����ҵ���һ��key����Ŀ����2�ģ����
	if(mytree==NULL)
		return NULL;
	if (mytree->is_leaf == true && mytree->value_num > 2)
		return mytree;
	for (int i = 0; i < 5; i++)
		if (find_redundant_leaf(mytree->child[i]) != NULL)
			return find_redundant_leaf(mytree->child[i]);
	return NULL;


}


	

void B_delete(B_Tree* mytree, int value)
{
	//�����ɾ����㲻��Ҷ�ӣ���ֵ����Ҷ��Ԫ�ؽ���
	//�ҵ�Ҷ�ӣ�ɾ��ֵ�������������ٴ�����Ҷ�ӽڵ���
	B_Tree* to_be_deleted = B_search(mytree, value);
	if (to_be_deleted == NULL)
		return;
	int temp = 0;						//�ȿ����м�ڵ�����
	B_Tree* temp_node = new B_Tree;
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
		to_be_deleted->parent->child[to_be_deleted->which_child] = NULL;
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





B_Tree* B_build(int* arr, int n)
{
	//��β��뽨��B��
	B_Tree* mytree = new B_Tree;
	mytree->value[0] = arr[0];
	mytree->value_num = 1;
	for (int i = 1; i < n; i++) {
		B_insert(mytree, arr[i]);
	}
	return mytree;
}



void B(int* arr, int algorithm, int n, int operation)
{
	clock_t start, end;
	start = clock();
	B_Tree* root = new B_Tree;
	root = B_build(arr, n);
	char temp[128];
	//tree_print(root, 0, temp);
	int value;
	switch (operation) {
	case 1:
		//cout << "����Ҫ�������" << endl;
		//cin >> value;
		B_insert(root, 12);
		break;
	case 2:
	//	cout << "����Ҫɾ������" << endl;
	//	cin >> value;
		B_delete(root, 62);
		break;
	case 3:
	//	cout << "����Ҫ��������" << endl;
	//	cin >> value;
		B_search(root, 11);
		break;
	default:
		cout << "��������!" << endl;
	}
	end = clock();
	cout << "algorithm = " << algorithm << "    operation = " << operation << "    time = " << double(end - start) << "units" << endl;
	//tree_print(root, 0, temp);
	

}


