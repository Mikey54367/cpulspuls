#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
template<class T>
struct AVLTreeNode
{
	AVLTreeNode(const T& data = T())
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _bf(0)
	{}

	AVLTreeNode<T>* _left;
	AVLTreeNode<T>* _right;
	AVLTreeNode<T>* _parent;
	T _data;
	int _bf;   // 节点的平衡因子
};


// AVL: 二叉搜索树 + 平衡因子的限制
template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		: _root(nullptr)
	{}

	// 在AVL树中插入值为data的节点
	bool Insert(const T& data)
	{
		if (_root == nullptr)
		{
			Node* newNode=new Node(data);
			_root = newNode;
			return true;
		}
		else
		{
			Node* newNode = new Node(data);
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_data < newNode->_data)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_data > newNode->_data)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			//插入
			if (parent->_data > newNode->_data)
			{
				parent->_left=newNode;
				newNode->_parent = parent;
			}
			else if (parent->_data < newNode->_data)
			{
				parent->_right=newNode;
				newNode->_parent = parent;
			}
			else
			{
				assert(false);
			}
			//更新_bf
			cur = newNode;
			while (parent)
			{
				if (parent->_left == cur)
				{
					parent->_bf--;
				}
				else if (parent->_right == cur)
				{
					parent->_bf++;
				}
				if (parent->_bf == 0)
					break;
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					//旋转
					if (parent->_bf == -2 && cur->_bf == -1)
					{
						RotateR(cur);
					}
					else if (parent->_bf == 2 && cur->_bf == 1)
					{
						RotateL(cur);
					}
					else if (parent->_bf == -2 && cur->_bf == 1)
					{
						int bf = cur->_right->_bf;
						Node* subLR = cur->_right;
						Node* subL = cur;
						Node* root = parent;
						RotateL(subLR);
						RotateR(subLR);
						if (bf == 0)
						{
							subLR->_bf = subL->_bf = root->_bf = 0;
						}
						else if (bf == 1)
						{
							subL->_bf = -1;
							subLR->_bf = root->_bf = 0;
						}
						else if (bf == -1)
						{
							root->_bf = 1;
							subL->_bf = subLR->_bf = 0;
						}
						else
						{
							assert(false);
						}
					}
					else if (parent->_bf == 2 && cur->_bf == -1)
					{
						int bf = cur->_left->_bf;
						Node* child = cur->_left;
						RotateR(child);
						RotateL(child);
						if (bf == 0)
						{
							cur->_bf = child->_bf = parent->_bf = 0;
						}
						else if (bf == 1)
						{
							parent->_bf = -1;
							cur->_bf = child->_bf = 0;
						}
						else if (bf == -1)
						{
							cur->_bf = 1;
							parent->_bf = child->_bf = 0;
						}
					}
					break;
				}
				else
				{
					assert(false);
				}
			}

			return true;
		}
	}
	void RotateR(Node* cur)
	{
		Node* parent = cur->_parent;
		parent->_left = cur->_right;
		if (cur->_right)
			cur->_right->_parent = parent;
		cur->_right = parent;
		if (parent->_parent)
		{
			if (parent->_parent->_left == parent)
			{
				parent->_parent->_left = cur;
			}
			else
			{
				parent->_parent->_right = cur;
			}
		}
		cur->_parent = parent->_parent;
		parent->_parent = cur;
		if (_root == parent)
			_root = cur;
		parent->_bf = 0;
		cur->_bf = 0;
	}
	void RotateL(Node* cur)
	{
		Node* parent = cur->_parent;
		parent->_right = cur->_left;
		if (cur->_left)
			cur->_left->_parent = parent;
		if (_root == parent)
			_root = cur;
		cur->_parent = parent->_parent;
		if (parent->_parent)
		{
			if (parent->_parent->_left == parent)
				parent->_parent->_left = cur;
			else
				parent->_parent->_right = cur;
		}

		cur->_left = parent;
		parent->_parent = cur;
		cur->_bf = parent->_bf = 0;
	}

	// AVL树的验证
	bool IsAVLTree()
	{
		return _IsAVLTree(_root);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	Node* Find(const T& key)
	{
		Node* cur = _root;
		while (cur)

		{
			if (cur->_data < key)
			{
				cur = cur->_right;
			}
			else if (cur->_data > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}
	size_t Height()
	{
		return _Height(_root);
	}
private:
	// 根据AVL树的概念验证pRoot是否为有效的AVL树
	bool _IsAVLTree(Node* root)
	{
		if (nullptr == root)
			return true;
		// 计算pRoot结点的平衡因⼦：即pRoot左右⼦树的⾼度差
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		int diff = rightHeight - leftHeight;
		
			// 如果计算出的平衡因⼦与pRoot的平衡因⼦不相等，或者
			// pRoot平衡因⼦的绝对值超过1，则⼀定不是AVL树
			if (abs(diff) >= 2)
			{
				cout << root->_data<< "⾼度差异常" << endl;
				return false;
			}
		if (root->_bf != diff)
		{
			cout << root->_data<< "平衡因⼦异常" << endl;
			return false;
		}
		// pRoot的左和右如果都是AVL树，则该树⼀定是AVL树
		return _IsAVLTree(root->_left) && _IsAVLTree(root->_right);
	}
	
	size_t _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
	

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_data << endl;
		_InOrder(root->_right);
	}
private:
	Node* _root;
};

