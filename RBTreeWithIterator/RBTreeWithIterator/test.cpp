#include"RBTree.h"
int main()
{
	//RBTree<int> t;
	RBTree<int> t;
	// ����Ĳ�������
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// ����Ĵ���˫�������Ĳ�������
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	for (auto e : a)
	{
		t.Insert(e);
	}
	auto it = t.begin();
	while (it != t.end())
	{
		cout << *it << endl;
		++it;
	}
	return 0;
}