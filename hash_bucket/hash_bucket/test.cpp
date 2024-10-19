#include<time.h>
#include"hash_bucket.h"

int main()
{
	srand(time(0));
	
	dziuGaaSoen::HashTable<int> ht;
	int arr[] = { 89,234,35,4,25,23,4,234,234,23,5,6 };
	int i = 100;
	while (i--)
	{
		ht.Insert(rand());
	}
	return 0;
}