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
	//直接根据原来的打印改，效果并不理想
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
	//节点内部值排序，但只能用于叶子节点，因为没有考虑到子节点区间的排序
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
	//将一个key的数目大于5的节点拆成两个
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
	//插入时先根据区间搜索，直到找到叶子插入。
	//如果插入后超出规模，则调用crack
	int i;
	B_Tree* leaf = mytree;
	while (leaf->is_leaf != true)		//找到叶子节点
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
	crack(leaf, mytree);			//传入根节点mytree,防止增加新根节点
	return;
}

B_Tree* B_search(B_Tree* mytree, int value)
{
	//根据B树区间搜索的特性查找
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
	//从所有其他叶子节点中找到第一个key的数目大于2的，借调
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
	//如果待删除结点不是叶子，将值与后继叶子元素交换
	//找到叶子，删除值，并重新排序，再从其他叶子节点借调
	B_Tree* to_be_deleted = B_search(mytree, value);
	if (to_be_deleted == NULL)
		return;
	int temp = 0;						//先考虑中间节点的情况
	B_Tree* temp_node = new B_Tree;
	temp_node = to_be_deleted;
	while (value > to_be_deleted->value[temp])
		temp++;
	int place = temp;					//记下value是to_be_deleted的第几个元素
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
		to_be_deleted = temp_node;	//这两行保证了两种情况都处理to_be_deleted[temp]
		temp = 0;
	}
			
	//考虑叶子节点
	to_be_deleted->value[temp] = 0;
	to_be_deleted->value_num--;
	if (to_be_deleted->value_num == 0)
		to_be_deleted->parent->child[to_be_deleted->which_child] = NULL;
	sort(to_be_deleted);
	if (to_be_deleted->value_num >= 2)
		return;
	temp_node = find_redundant_leaf(mytree);		//从其他叶子节点借调
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
	//多次插入建立B树
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
		//cout << "输入要插入的数" << endl;
		//cin >> value;
		B_insert(root, 12);
		break;
	case 2:
	//	cout << "输入要删除的数" << endl;
	//	cin >> value;
		B_delete(root, 62);
		break;
	case 3:
	//	cout << "输入要搜索的数" << endl;
	//	cin >> value;
		B_search(root, 11);
		break;
	default:
		cout << "重新输入!" << endl;
	}
	end = clock();
	cout << "algorithm = " << algorithm << "    operation = " << operation << "    time = " << double(end - start) << "units" << endl;
	//tree_print(root, 0, temp);
	

}


