#pragma once
#include"hash_bucket.h"
namespace dziuGaaSoen
{
	

	template<class K>
	struct DefHashF
	{
		size_t operator()(const K& data)
		{
			return (size_t)data;
		}
	};
	template<>
	struct DefHashF<string>
	{
		size_t operator()(const string& s)
		{
			size_t ret = 0;
			for (auto e : s)
			{
				ret += e;
				ret *= 131;
			}
			return ret;
		}
	};
	template<class K,class V>
	struct KeyOfValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};
	template<class K, class V, class HF = DefHashF<K>>
	class unordered_map
	{
		typedef HashTable<const K, pair<const K, V>, KeyOfValue<K,V>, HF> HT;
		// 通过key获取value的操作
		
	public:
		typename typedef HT::Iterator iterator;
		typename typedef HT::ConstIterator const_iterator;
	public:
		unordered_map() : _ht()
		{}
		////////////////////////////////////////////////////
		iterator begin() { return _ht.begin(); }
		iterator end() { return _ht.end(); }
		////////////////////////////////////////////////////////////
		// capacity
		size_t size()const { return _ht.size(); }
		bool empty()const { return _ht.empty(); }
		///////////////////////////////////////////////////////////
		// Acess
		V& operator[](const K& key)
		{
			pair<iterator,bool> p=_ht.Insert({key,V()});
			return (p.first)->second;
		}
		const V& operator[](const K& key)const
		{
			pair<iterator, bool> p = _ht.Insert(key);
			return (p.first)->second;
		}
		//////////////////////////////////////////////////////////
		// lookup
		iterator find(const K& key) { return _ht.Find(key); }
		size_t count(const K& key) { return _ht.Count(key); }
		/////////////////////////////////////////////////
		// modify
		pair<iterator, bool> insert(const pair<K, V>& valye)
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
		//size_t bucket_size(const K& key) { return _ht.BucketSize(key); }
	private:
		HT _ht;
	};
	void test_map1()
	{
		unordered_map<string, string> dict;
		dict.insert({ "sort", "排序" });
		dict.insert({ "字符串", "string" });

		dict.insert({ "sort", "排序" });
		dict.insert({ "left", "左边" });
		dict.insert({ "right", "右边" });

		dict["left"] = "左边，剩余";
		dict["insert"] = "插入";
		dict["string"];
		//dict.erase("sort");
		unordered_map<string, string>::iterator it1 = dict.find("string");
		dict.erase(it1);
		for (auto& kv : dict)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
		cout << endl;

		unordered_map<string, string>::iterator it = dict.begin();
		while (it != dict.end())
		{
			// 不能修改first，可以修改second
			//it->first += 'x';
			it->second += 'x';
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;
	}
}