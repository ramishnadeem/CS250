#include "project1_LinkedList.hpp"

Node::Node()
{
	m_ptrNext = nullptr;
	m_ptrPrev = nullptr;

}

LinkedList::LinkedList()
{
	m_ptrFirst = nullptr;
	m_ptrLast = nullptr;

}

LinkedList::~LinkedList()
{
	Clear();
}

void LinkedList::Clear()
{
	while (!IsEmpty())
	{
		PopFront();
		PopBack();
	}

}

void LinkedList::PushFront(CustomerData newData)
{
	Node* newNode = new Node;
	newNode->m_data = newData;
	m_itemCount++;
	if (m_ptrFirst == nullptr)
	{
		m_ptrFirst = newNode;
		m_ptrLast = newNode;
	}
	else
	{
		m_ptrFirst->m_ptrPrev = newNode;
		newNode->m_ptrNext = m_ptrFirst;
		m_ptrFirst = newNode;
	}
}

void LinkedList::PushBack(CustomerData newData)
{
	Node* newNode = new Node;
	newNode->m_data = newData;
	m_itemCount++;
	if (m_ptrLast == nullptr)
	{
		m_ptrFirst = newNode;
		m_ptrLast = newNode;
	}
	else
	{
		m_ptrLast->m_ptrNext = newNode;
		newNode->m_ptrPrev = m_ptrLast;
		m_ptrLast = newNode;
	}

}

void LinkedList::PopFront() noexcept
{
	if (IsEmpty())
	{
		return;
	}

	if (m_ptrFirst == m_ptrLast)
	{
		delete m_ptrFirst;
		m_ptrFirst = nullptr;
		m_ptrLast = nullptr;
		m_itemCount--;
	}
	else
	{ 
		Node* ptrSecond = m_ptrFirst->m_ptrNext;
		ptrSecond->m_ptrPrev = nullptr;
		delete m_ptrFirst;
		m_ptrFirst = ptrSecond;
		m_itemCount--;
	}
	
}

void LinkedList::PopBack() noexcept
{
	if (IsEmpty())
	{
		return;
	}

	if (m_ptrFirst == m_ptrLast)
	{
		delete m_ptrFirst;
		m_ptrFirst = nullptr;
		m_ptrLast = nullptr;
		m_itemCount--;
	}
	else
	{
		Node* ptrSecondToLast = m_ptrLast->m_ptrPrev;
		ptrSecondToLast->m_ptrNext = nullptr;
		delete m_ptrLast;
		m_ptrLast = ptrSecondToLast;
		m_itemCount--;
	}
	
} 

CustomerData LinkedList::GetFront()
{
	if (m_ptrFirst == nullptr)
	{
		throw out_of_range("ptrFirst is null");
	}
	return m_ptrFirst->m_data;
}

CustomerData LinkedList::GetBack()
{
	if (m_ptrLast == nullptr)
	{
		throw out_of_range("ptrLast is null");
	}
	return m_ptrLast->m_data;
}

CustomerData& LinkedList::operator[](const int index)
{
	if (m_ptrFirst == nullptr)
	{
		throw out_of_range("Empty List");
	}
	else if (index < 0 || index >= Size())
	{
		throw out_of_range("Invalid Index");
	}
	int counter = 0;
	Node* ptrCurrent = m_ptrFirst;
	while (ptrCurrent != nullptr && counter < index)
	{
		ptrCurrent = ptrCurrent->m_ptrNext;
		counter++;
	}
	return ptrCurrent->m_data;
}

bool LinkedList::IsEmpty()
{
	if (m_itemCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int LinkedList::Size()
{
	return m_itemCount;
}