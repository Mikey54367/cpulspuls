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

	// �ں�����в���ֵΪdata�Ľڵ㣬����ɹ�����true�����򷵻�false
	// ע�⣺Ϊ�˼����������ʵ�ֺ�������洢�ظ���Ԫ��
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
			//�����������������
			//���Ǻ�
			//��������
			//ÿ��·�����
			cur = newNode;
			while (parent!=_pHead&&parent != _pHead->_left&&parent->_col==Red)
			{
				Node* uncle = nullptr;
				if (parent == parent->_parent->_left)
					uncle = parent->_parent->_right;
				else
					uncle = parent->_parent->_left;
				//���������Ϊ��
				if (uncle && uncle->_col == Red)
				{
					parent->_parent->_col = Red;
					uncle->_col = parent->_col = Black;
					cur = parent->_parent;
					parent = cur->_parent;
				}
				//���岻���ڻ����������Ϊ��
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

	// ����������Ƿ����ֵΪdata�Ľڵ㣬���ڷ��ظýڵ�ĵ�ַ�����򷵻�nullptr
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
	// ��ȡ����������ڵ�
	Node* LeftMost();

	// ��ȡ��������Ҳ�ڵ�
	Node* RightMost();

	// ��������Ƿ�Ϊ��Ч�ĺ������ע�⣺���ڲ���Ҫ����_IsValidRBTRee�������
public:
	bool IsValidRBTRee()
	{
		if (_pHead->_left == nullptr)
			return true;

		if (_pHead->_left->_col == Red)
			return false;

		// �ο�ֵ
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
			// ǰ������ߵ���ʱ����ζ��һ��·��������
			//cout << blackNum << endl;
			if (pathBlack != blackCount)
			{
				cout << "���ں�ɫ������������ȵ�·��" << endl;
				return false;
			}
			return true;
		}

		// ��麢�Ӳ�̫���㣬��Ϊ�������������Ҳ�һ�����ڣ���������鸸�׾ͷ������
		if (root->_col == Red && root->_parent->_col == Red)
		{
			cout << root->_data << "���������ĺ�ɫ���" << endl;
			return false;
		}

		if (root->_col == Black)
		{
			blackCount++;
		}

		return _IsValidRBTRee(root->_left, blackCount, pathBlack)
			&& _IsValidRBTRee(root->_right, blackCount, pathBlack);
	}
	
	
	// Ϊ�˲��������������ȡ���ڵ�
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