#pragma once
#include<iostream>
using namespace std;
enum Colour
{
	Red,
	Black
};
template<class T>
struct RBTreeNode
{
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Colour _col;
	RBTreeNode(const T& data=T(), Colour col=Red)
		:_data(data)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_col(col)
	{

	}
};
template<class T>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	RBTree()
	{
		_pHead = new Node();
		_pHead->_left = _pHead;
		_pHead->_right = _pHead;
	}

	// 在红黑树中插入值为data的节点，插入成功返回true，否则返回false
	// 注意：为了简单起见，本次实现红黑树不存储重复性元素
	bool Insert(const T& data)
	{
		if (_pHead->_left == _pHead)
		{
			Node* newNode = new Node(data,Black);
			_pHead->_left = _pHead->_right = newNode;
			newNode->_parent = _pHead;
			return true;
		}
		else
		{
			Node* newNode = new Node(data, Red);
			Node* cur = _pHead->_left;
			Node* parent = _pHead;
			while (cur)
			{
				if (newNode->_data > cur->_data)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (newNode->_data < cur->_data)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			if (newNode->_data > parent->_data)
			{
				parent->_right = newNode;
				newNode->_parent = parent;
			}
			else if (newNode->_data < parent->_data)
			{
				parent->_left = newNode;
				newNode->_parent = parent;
			}
			//处理不符合条件的情况
			//根是黑
			//不能连红
			//每条路黑相等
			cur = newNode;
			while (parent!=_pHead&&parent != _pHead->_left&&parent->_col==Red)
			{
				Node* uncle = nullptr;
				if (parent == parent->_parent->_left)
					uncle = parent->_parent->_right;
				else
					uncle = parent->_parent->_left;
				//叔叔存在且为红
				if (uncle && uncle->_col == Red)
				{
					parent->_parent->_col = Red;
					uncle->_col = parent->_col = Black;
					cur = parent->_parent;
					parent = cur->_parent;
				}
				//叔叔不存在或叔叔存在且为黑
				else
				{
					if (parent == parent->_parent->_left)
					{
						if (cur == parent->_left)
						{
							RotateR(parent);
							parent->_col = Black;
							parent->_left->_col = parent->_right->_col = Red;
						}
						else if (cur == parent->_right)
						{
							RotateL(cur);
							RotateR(cur);
							cur->_col = Black;
							cur->_left->_col = cur->_right->_col = Red;
						}
					}
					else
					{
						if (cur == parent->_right)
						{
							RotateL(parent);
							parent->_col = Black;
							parent->_left->_col = parent->_right->_col = Red;
						}
						else
						{
							RotateR(cur);
							RotateL(cur);
							cur->_col = Black;
							cur->_left->_col = cur->_right->_col = Red;
						}
					}
					break;
				}
			}
			_pHead->_left->_col = Black;
			return true;
		}
	}

	// 检测红黑树中是否存在值为data的节点，存在返回该节点的地址，否则返回nullptr
	Node* Find(const T& data);

	void InOrder()
	{
		return _InOrder(_pHead->_left);
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_data << endl;
		_InOrder(root->_right);
	}
	// 获取红黑树最左侧节点
	Node* LeftMost();

	// 获取红黑树最右侧节点
	Node* RightMost();

	// 检测红黑树是否为有效的红黑树，注意：其内部主要依靠_IsValidRBTRee函数检测
public:
	bool IsValidRBTRee()
	{
		if (_pHead->_left == nullptr)
			return true;

		if (_pHead->_left->_col == Red)
			return false;

		// 参考值
		int refNum = 0;
		Node* cur = _pHead->_left;
		while (cur)
		{
			if (cur->_col == Black)
			{
				++refNum;
			}
			cur = cur->_left;
		}
		return _IsValidRBTRee(_pHead->_left, 0, refNum);
	}
private:
	bool _IsValidRBTRee(Node* root, size_t blackCount, size_t pathBlack)
	{
		if (root == nullptr)
		{
			// 前序遍历走到空时，意味着一条路径走完了
			//cout << blackNum << endl;
			if (pathBlack != blackCount)
			{
				cout << "存在黑色结点的数量不相等的路径" << endl;
				return false;
			}
			return true;
		}

		// 检查孩子不太方便，因为孩子有两个，且不一定存在，反过来检查父亲就方便多了
		if (root->_col == Red && root->_parent->_col == Red)
		{
			cout << root->_data << "存在连续的红色结点" << endl;
			return false;
		}

		if (root->_col == Black)
		{
			blackCount++;
		}

		return _IsValidRBTRee(root->_left, blackCount, pathBlack)
			&& _IsValidRBTRee(root->_right, blackCount, pathBlack);
	}
	
	
	// 为了操作树简单起见：获取根节点
	Node*& GetRoot();
private:
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
		
	}
	void RotateL(Node* cur)
	{
		Node* parent = cur->_parent;
		parent->_right = cur->_left;
		if (cur->_left)
			cur->_left->_parent = parent;
		
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
	}
	Node* _pHead;
};