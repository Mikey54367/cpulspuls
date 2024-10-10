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
	int _bf;   // �ڵ��ƽ������
};


// AVL: ���������� + ƽ�����ӵ�����
template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		: _root(nullptr)
	{}

	// ��AVL���в���ֵΪdata�Ľڵ�
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
			//����
			if (parent->_data > newNode->_data)
			{
				newNode = parent->_left;
				newNode->_parent = parent;
			}
			else if(parent->_data < newNode->_data)
			{ 
				newNode = parent->_right;
				newNode->_parent = parent;
			}
			else
			{
				assert(false);
			}
			//����_bf
			Node* cur = newNode;
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
					//��ת

					break;
				}
			}
		}
	}

	// AVL������֤
	bool IsAVLTree()
	{
		return _IsAVLTree(_root);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
private:
	// ����AVL���ĸ�����֤pRoot�Ƿ�Ϊ��Ч��AVL��
	bool _IsAVLTree(Node* pRoot);
	size_t _Height(Node* pRoot);
	// �ҵ���
	void RotateR(Node* pParent);
	// ����
	void RotateL(Node* pParent);
	// ����˫��
	void RotateRL(Node* pParent);
	// ����˫��
	void RotateLR(Node* pParent);

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

