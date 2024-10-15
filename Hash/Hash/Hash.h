#pragma once
#include<iostream>
#include<vector>
//#include<pair>
using namespace std;
namespace dziuGaaSoen
{
	enum State
	{
		EXIST,
		EMPTY,
		DELETE

	};
	template<class K>
	struct HashFunc
	{
		bool operator()(const K& data1, const K& data2)
		{
			return data1 == data2;
		}
	};
	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = EMPTY;
		/*HashData(pair<K, V> kv=make_pair(K(),V()), State state = EMPTY)
			:_kv(kv)
			,_state(state)
		{

		}*/
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
	public:
		HashTable(int n=10)
		{
			_tables.resize(n);

		}

		bool Insert(const pair<K, V>& kv)
		{
			if (10 * _n / _tables.size() >= 7)
			{
				//扩容
				HashTable<K, V, Hash> h(2*_tables.size());
				for (auto e : _tables)
				{
					if (e._state == EXIST)
					{
						h.Insert(e._kv);
					}
				}
				//
				// swap(_table, h._table);//????
				swap(_tables, h._tables);
			}
			if (Find(kv.first)!=nullptr)
				return false;
			HashData<K, V> cur;
			cur._kv = kv;
			cur._state = EXIST;
			int Hash0 = kv.first % _tables.size();
			while (_tables[Hash0]._state == EXIST)
			{
				Hash0++;
				if (Hash0 > _tables.size())
					Hash0 = Hash0 % _tables.size();
			}
			_tables[Hash0] = cur;
			_n++;
			return true;
		}
		HashData<K, V>* Find(const K& key)
		{
			int Hash0 = key % _tables.size();
			while (_tables[Hash0]._state != EMPTY)
			{
				
				if (_tables[Hash0]._state==EXIST&&com(key, _tables[Hash0]._kv.first))
				{
					return &(_tables[Hash0]);
				}
				Hash0++;
				if (Hash0 > _tables.size())
					Hash0 %= _tables.size();
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			if (Find(key) == nullptr)
				return false;
			Find(key)->_state = DELETE;
			--_n;
			return true;
		}

	private:
		vector<HashData<K, V>> _tables;
		size_t _n = 0;  // 表中存储数据个数
		Hash com;
	};
}