#include"Hash.h"
int main()
{
	//int a[] = { 19,30,52,63,11,22 };
	int a[] = { 19,30,5,36,13,20,21,12 };
	dziuGaaSoen::HashTable<int, int> ht;
	for (auto e : a)
	{
		ht.Insert({ e, e });
	}

	//ht.Insert({ 15, 15 });

	ht.Erase(30);
	if (ht.Find(20))
	{
		cout << "�ҵ���" << endl;
	}

	if (ht.Find(30))
	{
		cout << "�ҵ���" << endl;
	}
	else
	{
		cout << "û���ҵ�" << endl;
	}

	return 0;
}