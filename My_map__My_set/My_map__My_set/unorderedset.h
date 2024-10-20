#pragma once
#include"hash_bucket.h"
namespace dziuGaaSoen
{
	template<class K>
	struct DefHashF;
	template<>
	struct DefHashF<string>;
	template<class K,class T>
	struct KeyOfKey
	{
		const K& operator()(const T& data)
		{
			return data;
		}
	};
	template<class K, class HF = DefHashF<K>>
	class unordered_set
	{
		typedef HashTable<const K, const K, KeyOfKey<const K,const K>, HF> HT;
		// 通过key获取value的操作

	public:
		typename typedef HT::Iterator iterator;
		typename typedef HT::ConstIterator const_iterator;
	public:
		unordered_set() : _ht()
		{}
		////////////////////////////////////////////////////
		iterator begin() { return _ht.begin(); }
		iterator end() { return _ht.end(); }
		////////////////////////////////////////////////////////////
		// capacity
		size_t size()const { return _ht.size(); }
		bool empty()const { return _ht.empty(); }
		///////////////////////////////////////////////////////////
		// lookup
		iterator find(const K& key) { return _ht.Find(key); }
		size_t count(const K& key) { return _ht.Count(key); }
		/////////////////////////////////////////////////
		// modify
		pair<iterator, bool> insert(const K& valye)
		{
			return _ht.Insert(valye);
		}

		iterator erase(iterator position)
		{
			return _ht.Erase(position);
		}
		////////////////////////////////////////////////////////////
		// bucket
		size_t bucket_count() { return _ht.BucketCount(); }
		size_t bucket_size(const K& key) { return _ht.BucketSize(key); }
	private:
		HT _ht;
	};
	void print(unordered_set<int>& s)
	{
		unordered_set<int>::const_iterator it = s.begin();
		while (it != s.end())
		{
			//*it = 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	void test_set1()
	{
		int a[] = { 3,11,86,7,88,82,1,881,5,6,7,6 };
		unordered_set<int> s;
		for (auto e : a)
		{
			s.insert(e);
		}

		unordered_set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			//*it = 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;

		print(s);
	}
}
