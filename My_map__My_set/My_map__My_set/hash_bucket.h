#pragma once
#include<iostream>
#include<vector>
using namespace std;
namespace dziuGaaSoen
{
	template<class K,class T>
	struct HashNode
	{
		T _data;
		HashNode<K,T>* _next;
		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};


	// K 为 T 中key的类型
	// T 可能是键值对，也可能是K
	// KeyOfT: 从T中提取key
	// Hash将key转化为整形，因为哈市函数使用除留余数法
	inline unsigned long __stl_next_prime(unsigned long n)
	{
		// Note: assumes long is at least 32 bits.
		static const int __stl_num_primes = 28;
		static const unsigned long __stl_prime_list[__stl_num_primes] =

		{
		 53, 97, 193, 389, 769,
			1543, 3079, 6151, 12289, 24593,
			49157, 98317, 196613, 393241, 786433,
			 1572869, 3145739, 6291469, 12582917, 25165843,
			 50331653, 100663319, 201326611, 402653189, 805306457,
			 1610612741, 3221225473, 4294967291
		};

		return *upper_bound(__stl_prime_list, __stl_prime_list+ __stl_num_primes, n);
	}
	
	template<class K, class T, class keyOfT, class Hash>
	class HashTable;
	template<class K,class T,class ref,class ptr,class keyOfT,class Hash>
	class HTIterator
	{
	public:
		typedef HashNode<K, T> Node;
		                        //T*  T&  
		typedef HTIterator<K, T, ref, ptr, keyOfT, Hash> Self;
		HTIterator(Node* node,vector<Node*>& table)
			:_node(node)
			,_table(table)
		{}
		Self& operator++()
		{
			if (_node->_next)
				_node = _node->_next;
			else
			{
				keyOfT kot;
				Hash hash;
				int hash0 = hash(kot(_node->_data)) % _table.size();
				hash0++;
				while (hash0 < _table.size())
				{
					if (_table[hash0])
					{
						_node = _table[hash0];
						break;
					}
					++hash0;
				}
				if (hash0 == _table.size())
				{
					_node = nullptr;
				}

			}
			return *this;
		}
		//Self operator++(int);
		ref operator*()
		{
			return _node->_data;
		}
		ptr operator->()
		{
			return &(_node->_data);
		}
		bool operator==(const Self& it) const
		{
			return _node == it._node;
		}
		bool operator!=(const Self& it) const
		{
			return _node != it._node;
		}
	
		Node* _node;
		vector<Node*> _table;
		
	};
	template<class K,class T,class keyOfT,class Hash>
	class HashTable
	{
		typedef HashNode<K,T> Node;
	public:
		typedef HTIterator<K, T, T&, T*, keyOfT, Hash> Iterator;
		typedef HTIterator<K, T, const T&, const T*, keyOfT, Hash> ConstIterator;
	public:
		Iterator begin()
		{
			int i = 0;
			while (i < _tables.size())
			{
				if (_tables[i])
					return{ _tables[i],_tables };
				++i;
			}
			return { nullptr,_tables };
		}
		Iterator end()
		{
			return { nullptr,_tables };
		}
		size_t size()
		{
			return _n;
		}
		bool empty()
		{
			return _n == 0;
		}
		size_t BucketCount()
		{
			return _tables.size();
		}
		Iterator Erase(Iterator position)
		{
			keyOfT kot;
			Hash hash;
			int hash0=hash(kot(*position)) % _tables.size();
			Iterator tmp = position;
			++position;
			Node* prev = nullptr;
			Node* cur = _tables[hash0];
			while (cur)
			{
				if (cur == tmp._node)
				{
					if (prev == nullptr)
					{
						_tables[hash0] = cur->_next;
						delete cur;
					}
					else
					{
						prev->_next = cur->_next;
						delete cur;
					}
					break;
				}
				else
				{
					cur = cur->_next;
				}
			}
			return position;
		}
		HashTable(int n=29)
		{
			_tables.resize(n);
		}

		// 哈希桶的销毁
		~HashTable()
		{
			for (int i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* node = cur;
					cur = cur->_next;
					delete node;
				}

			}
		}

		// 插入值为data的元素，如果data存在则不插入
		pair<Iterator,bool> Insert(const T& data)
		{
			keyOfT kot;
			Hash hash;
			if (Find(kot(data))!=end())
				return {Find(kot(data)),false};
			if (_n == _tables.size())
			{
				vector<Node*> newtable(__stl_next_prime(_tables.size()));
				for (int i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* node = cur;
						cur = cur->_next;
						node->_next = nullptr;
						int hash0 = hash(kot(node->_data)) % newtable.size();
						if (newtable[hash0] == nullptr)
						{
							newtable[hash0] = node;
						}
						else
						{
							node->_next = newtable[hash0];
							newtable[hash0] = node;
						}
					}
				}
				swap(_tables, newtable);
			}
			Node* newNode = new Node(data);
			int hash0 = hash(kot(data)) % _tables.size();
			if (_tables[hash0] == nullptr)
			{
				_tables[hash0] = newNode;
			}
			else
			{
				newNode->_next = _tables[hash0];
				_tables[hash0] = newNode;
			}
			_n++;
			Iterator it(newNode, _tables);
			return{ it,true };
		}

		// 在哈希桶中查找值为key的元素，存在返回true否则返回false﻿
		Iterator Find(const K& key)
		{
			Hash hash;
			int hash0 = hash(key) % _tables.size();
			Node* cur = _tables[hash0];
			keyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
					return { cur, _tables};
				cur = cur->_next;
			}
			return { nullptr,_tables };
		}

		// 哈希桶中删除key的元素，删除成功返回true，否则返回false
		bool Erase(const K& key)
		{
			Node* prev = nullptr;
			keyOfT kot;
			Hash hash;
			int hash0 = hash(key) % _tables.size();
			Node* cur = _tables[hash0];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (prev == nullptr)
					{
						_tables[hash0] = cur->_next;
						delete cur;
						--_n;
						return true;
					}
					else
					{
						prev->_next = cur->_next;
						delete cur;
						--_n;
						return true;
					}
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}

	private:

		vector<Node*> _tables;  // 指针数组
		size_t _n = 0;			// 表中存储数据个数
	};
}
