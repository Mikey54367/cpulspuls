﻿#include<vector>
#include"AVLTree.h"

void TestAVLTree1()
{
	AVLTree<int> t;
	// 常规的测试⽤例
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// 特殊的带有双旋场景的测试⽤例
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
	cout << t.IsAVLTree() << endl;
}
void TestAVLTree2()
{
	const int N = 100000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
	}
	
		size_t begin2 = clock();
	AVLTree<int> t;
	for (auto e : v)
	{
		t.Insert(e);
	}
	size_t end2 = clock();
	cout << "Insert:" << end2 - begin2 << endl;
	cout << t.IsAVLTree() << endl;
	cout << "Height:" << t.Height() << endl;
	//cout << "Size:" << t.Size() << endl;
	size_t begin1 = clock();
	// 确定在的值
	/*for (auto e : v)
	{
	t.Find(e);
	}*/
	// 随机值
	for (size_t i = 0; i < N; i++)
	{
		t.Find((rand() + i));
	}
	size_t end1 = clock();
	cout << "Find:" << end1 - begin1 << endl;
}
int main()
{
	TestAVLTree2();
	return 0;
}
