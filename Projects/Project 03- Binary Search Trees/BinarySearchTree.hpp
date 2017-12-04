/* Modify this file! */

#ifndef _BINARY_SEARCH_TREE_HPP
#define _BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename TK, typename TD>
//! A template node class, to be used in the BinarySearchTree class.
class Node      // done
{
public:
	//! Initializes left and right pointers to nullptr.
	Node()
	{
		ptrLeft = nullptr;
		ptrRight = nullptr;
	}

	//! Destroys left and right children, if they are not pointing to nullptr.
	~Node()
	{
		// destroy children
		if (ptrLeft != nullptr) { delete ptrLeft; }
		if (ptrRight != nullptr) { delete ptrRight; }
	}

	//! Pointer to the left child of the node, which is lesser in value
	Node<TK, TD>* ptrLeft;

	//! Pointer to the right chlid of the node, which is greater in value
	Node<TK, TD>* ptrRight;

	//! The data stored by the node
	TD data;

	//! The key of this node
	TK key;
};

template <typename TK, typename TD>
//! A template binary search tree class
class BinarySearchTree
{
public:
	//! Initializes the node count to 0, and the root pointer to nullptr.
	BinarySearchTree()	// done
	{
		m_ptrRoot = nullptr;
		m_nodeCount = 0;
	}

	//! Destroys the root node
	~BinarySearchTree()		// done
	{
		if (m_ptrRoot != nullptr) { delete m_ptrRoot; }
	}

	//DONE
	void Insert(const TK& newKey, const TD& newData)
	{
		if (m_ptrRoot == nullptr)
		{
			Node<TK, TD>* newNode = new Node<TK, TD>;
			m_ptrRoot = newNode;
			newNode->key = newKey;
			newNode->data = newData;
			m_nodeCount++;
		}
		else
		{
			RecursiveInsert(newKey, newData, m_ptrRoot);
		}
	}

	//DONE
	void Delete(const TK& key)
	{
		Node<TK, TD>* node = FindNode(key);
		Node<TK, TD>* parentNode = FindParentOfNode(key);
		bool isLeftNode = (parentNode->ptrLeft == node);
		if (m_ptrRoot == nullptr)
		{
			return;
		}
		if (node == nullptr)
		{
			return;
		}
		if (node->ptrLeft == nullptr && node->ptrRight == nullptr)
		{
			if (node == m_ptrRoot)
			{
				m_ptrRoot = nullptr;
			}
			else if (isLeftNode)
			{
				parentNode->ptrLeft = nullptr;
			}
			else
			{
				parentNode->ptrRight = nullptr;
			}
		}
		else if (node->ptrLeft == nullptr)
		{
			if (node == m_ptrRoot)
			{
				m_ptrRoot = node->ptrRight;
			}
			else if (isLeftNode)
			{
				parentNode->ptrLeft = node->ptrRight;
			}
			else
			{
				parentNode->ptrRight = node->ptrRight;
			}
		}
		else if (node->ptrRight == nullptr)
		{
			if (node == m_ptrRoot)
			{
				m_ptrRoot = node->ptrLeft;
			}
			else if (isLeftNode)
			{
				parentNode->ptrLeft = node->ptrLeft;
			}
			else
			{
				parentNode->ptrRight = node->ptrLeft;
			}
		}
		else
		{
			Node<TK, TD>* tempNode = node->ptrRight;
			Node<TK, TD>* successor = node;
			Node<TK, TD>* successorParent = node;
			while (tempNode != nullptr)
			{
				successorParent = successor;
				successor = tempNode;
				tempNode = tempNode->ptrLeft;
			}

			if (successor != node->ptrRight)
			{
				successorParent->ptrLeft = successor->ptrRight;
				successor->ptrRight = node->ptrRight;
			}

			if (node == m_ptrRoot)
			{
				m_ptrRoot = successor;
			}
			else if (isLeftNode)
			{
				node = parentNode->ptrLeft;
				parentNode->ptrLeft = successor;
			}
			else
			{
				node = parentNode->ptrRight;
				parentNode->ptrRight = successor;
			}
			successor->ptrLeft = node->ptrLeft;
		}
		node->ptrLeft = nullptr;
		node->ptrRight = nullptr;
		delete node;
		m_nodeCount--;
	} 

	//DONE
	bool Contains(const TK& key)
	{
		Node <TK, TD>* currentRoot = m_ptrRoot;
		if (m_ptrRoot == nullptr)
		{
			return false;
		}
		while (currentRoot->key != key)
		{
			if (key < currentRoot->key)
			{
				currentRoot = currentRoot->ptrLeft;
			}
			else if (key > currentRoot->key)
			{
				currentRoot = currentRoot->ptrRight;
			}
			if (currentRoot == nullptr)
			{
				return false;
			}
		}
		return true;
	}

	string GetInOrder()     // done
	{
		stringstream stream;
		GetInOrder(m_ptrRoot, stream);
		return stream.str();
	}

	string GetPreOrder()     // done
	{
		stringstream stream;
		GetPreOrder(m_ptrRoot, stream);
		return stream.str();
	}

	string GetPostOrder()     // done
	{
		stringstream stream;
		GetPostOrder(m_ptrRoot, stream);
		return stream.str();
	}

	TK* GetMax()     // done
	{
		return GetMax(m_ptrRoot);
	}

	int GetCount()     // done
	{
		return m_nodeCount;
	}

	int GetHeight()     // done
	{
		if (m_ptrRoot == nullptr)
		{
			return 0;
		}

		return GetHeight(m_ptrRoot);
	}

	TD* GetData(const TK& key)	// done
	{
		Node<TK, TD>* node = FindNode(key);

		if (node == nullptr)
		{
			return nullptr;
		}

		return &(node->data);
	}

private:
	//DONE
	Node<TK, TD>* FindNode(const TK& key)
	{
		Node<TK, TD>* currentPtr = m_ptrRoot;
		if (m_ptrRoot == nullptr)
		{
			return nullptr;
		}
		while (currentPtr->key != key)
		{
			if (key < currentPtr->key)
			{
				currentPtr = currentPtr->ptrLeft;
			}
			else if (key > currentPtr->key)
			{
				currentPtr = currentPtr->ptrRight;
			}

			if (currentPtr == nullptr)
			{
				return nullptr;
			}
		}
		return currentPtr;
	}

	//DONE
	Node<TK, TD>* FindParentOfNode(const TK& key)
	{
		Node <TK, TD>* nodeCurrent = m_ptrRoot;
		Node <TK, TD>* previous = nullptr;
		if (m_ptrRoot == nullptr)
		{
			return nullptr;
		}
		while (nodeCurrent->key != key)
		{
			previous = nodeCurrent;
			if (key < nodeCurrent->key)
			{
				nodeCurrent = nodeCurrent->ptrLeft;
			}
			else
			{
				nodeCurrent = nodeCurrent->ptrRight;
			}
			if (nodeCurrent == nullptr)
			{
				return nullptr;
			}
		}
		return previous;
	}

	void RecursiveInsert(const TK& newKey, const TD& newData, Node<TK, TD>* ptrCurrent)
	{
		if (ptrCurrent == nullptr)
		{
			Node<TK, TD>* newNode = new Node<TK, TD>;
			ptrCurrent = newNode;
			newNode->key = newKey;
			newNode->data = newData;
			m_nodeCount++;
		}
		else if (newKey < ptrCurrent->key)
		{
			if (ptrCurrent->ptrLeft == nullptr)
			{
				Node<TK, TD>* newNode = new Node<TK, TD>;
				ptrCurrent->ptrLeft = newNode;
				newNode->key = newKey;
				newNode->data = newData;
				m_nodeCount++;
			}
			else
			{
				RecursiveInsert(newKey, newData, ptrCurrent->ptrLeft);
			}
		}
		else if (newKey > ptrCurrent->key)
		{
			if (ptrCurrent->ptrRight == nullptr)
			{
				Node<TK, TD>* newNode = new Node<TK, TD>;
				ptrCurrent->ptrRight = newNode;
				newNode->key = newKey;
				newNode->data = newData;
				m_nodeCount++;
			}
			else
			{
				RecursiveInsert(newKey, newData, ptrCurrent->ptrRight);

			}
		}
	}

	void GetInOrder(Node<TK, TD>* ptrCurrent, stringstream& stream)
	{
		if (ptrCurrent != nullptr)
		{
			GetInOrder(ptrCurrent->ptrLeft, stream);
			stream << ptrCurrent->key << " ";
			GetInOrder(ptrCurrent->ptrRight, stream);
		}
	}

	void GetPreOrder(Node<TK, TD>* ptrCurrent, stringstream& stream)
	{
		if (ptrCurrent != nullptr)
		{
			stream << ptrCurrent->key << " ";
			GetPreOrder(ptrCurrent->ptrLeft, stream);
			GetPreOrder(ptrCurrent->ptrRight, stream);
		}
	}

	void GetPostOrder(Node<TK, TD>* ptrCurrent, stringstream& stream)
	{
		if (ptrCurrent != nullptr)
		{
			GetPostOrder(ptrCurrent->ptrLeft, stream);
			GetPostOrder(ptrCurrent->ptrRight, stream);
			stream << ptrCurrent->key << " ";
		}
	}

	//DONE
	TK* GetMax(Node<TK, TD>* ptrCurrent)
	{
		if (ptrCurrent == nullptr)
		{
			return nullptr;
		}
		if (ptrCurrent->ptrRight == nullptr)
		{
			return &ptrCurrent->key;
		}
		return GetMax(ptrCurrent->ptrRight);
	}

	//DONE
	int GetHeight(Node<TK, TD>* ptrCurrent)
	{
		int leftHeight = 0;
		int rightHeight = 0;
		if (ptrCurrent == nullptr)
		{
			return -1;
		}
		if (ptrCurrent->ptrLeft != nullptr)
		{
			leftHeight = GetHeight(ptrCurrent->ptrLeft);
		}
		if (ptrCurrent->ptrRight != nullptr)
		{
			rightHeight = GetHeight(ptrCurrent->ptrRight);
		}
		if (rightHeight < leftHeight)
		{
			return leftHeight + 1;
		}
		else
			return rightHeight + 1;
	}

private:
	//! A pointer to the root node of the tree; TK = data type of the key, TD = data type of the data.
	Node<TK, TD>* m_ptrRoot;

	//! The amount of nodes in the tree
	int m_nodeCount;

	friend class Tester;
};

#endif
