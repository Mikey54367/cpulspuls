#pragma once
#include<iostream>
using namespace std;
enum Color
{
	BLACK,
	RED
};
template <class T>
struct RBTreeNode
{
	T _data;
	RBTreeNode<T>* _left=nullptr;
	RBTreeNode<T>* _right=nullptr;
	RBTreeNode<T>* _parent=nullptr;
	Color _col=RED;
	RBTreeNode(const T& data)
		:_data(data)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_col(RED)
	{

	}
};
template <class T>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;

	Node* _node;

	RBTreeIterator(Node* node)
		:_node(node)
	{}

	// 请完善迭代器的++操作，让迭代器可以移动
	Self& operator++()
	{
		if (_node->_right)
		{
			Node* cur = _node->_right;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			_node = cur;
		}
		else
		{
			Node* parent = _node->_parent;
			while (parent && parent->_right == _node)
			{
				_node = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	// 请完善下面两个操作，让迭代器可以像指针一样操作
	T& operator*()
	{
		return _node->_data;
	}
	T* operator->()
	{
		return &(_node->_data);
	}

	// 请完善下面两个操作，让迭代器能够支持比较
	bool operator!=(const Self& s)const
	{
		return _node != s._node;
	}
	bool operator==(const Self& s)const
	{
		return _node == s._node;
	}
};



// 注意：红黑树完整操作参考课堂代码
// 此处给红黑树添加迭代器，其他用不到的操作暂被拿掉，只留下红黑树构建的核心操作
template<class T>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	// 请给红黑树的迭代器取别名，方便后序使用
	// ________________________
	typedef RBTreeIterator<T> iterator;
	// 请完善Begin() 和 End()方法

	iterator begin()
	{
		if (_root == nullptr)
		{
			return _root;
		}
		Node* cur = _root;
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}
	iterator end()
	{
		return nullptr;
	}


	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}


	bool Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return true;
		}


		//KeyOfT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_data < data)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_data > data)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}


		cur = new Node(data);
		// 新增节点。颜色红色给红色
		cur->_col = RED;
		if (parent->_data < data)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//    g
			//  p   u
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					// u存在且为红 -》变色再继续往上处理
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;


					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					// u存在且为黑或不存在 -》旋转+变色
					if (cur == parent->_left)
					{
						//    g
						//  p   u
						//c
						//单旋
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//    g
						//  p   u
						//    c
						//双旋
						RotateL(parent);
						RotateR(grandfather);


						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else
			{
				//    g
				//  u   p
				Node* uncle = grandfather->_left;
				// 叔叔存在且为红，-》变色即可
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 叔叔不存在，或者存在且为黑
				{
					// 情况二：叔叔不存在或者存在且为黑
					// 旋转+变色
					//      g
					//   u     p
					//            c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//		g
						//   u     p
						//      c
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}

		_root->_col = BLACK;
		return true;
	}
private:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* parentParent = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;


		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}

			subR->_parent = parentParent;
		}
	}


	void  RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* parentParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parentParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
	}

	void Destroy(Node* root)
	{
		if (root == nullptr)
			return;

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}

private:
	Node* _root = nullptr;
};