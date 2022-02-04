#include "DoubleLinkedList.h"
//  DoubleLinkedList.cpp - ������ ������� ������ ����� ����� - ���������� ������� ������  
//
#include <iostream>
#include <fstream>

// ����������� "�����������" � �������� ����� ���������� ������
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& src) {

	// std::cout << "�������� ����������� " << std::endl;
	head_ = nullptr;
	tail_ = nullptr;
	count_ = 0;

	// ������ ������, �� �������� ��������:
	Node* temp = src.head_;

	// ���� �� ����� ������:
	while (temp != nullptr)
	{   // ���������� ������:
		this->insertTail(temp->item_);
		temp = temp->next_;
	}
}

// ����������� "�����������" ��������� � �������� ��������� ������ rvalue reference
DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& src) noexcept :
	count_(src.count_)
	, head_(src.head_)
	, tail_(src.tail_)
{
	// std::cout << "�������� �����������" << std::endl;
	src.count_ = 0;
	src.head_ = nullptr;
	src.tail_ = nullptr;
}

void DoubleLinkedList::swap(DoubleLinkedList& list) {
	std::swap(head_, list.head_);
	std::swap(tail_, list.tail_);
	std::swap(count_, list.count_);
}
// ����� �����������
DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList& list)
{
	// std::cout << "�������� ����������� =" << std::endl;
	DoubleLinkedList tmp(list);
	this->swap(tmp);
	return *this;
}
// ������ ���������� 
DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& list) noexcept
{
	// std::cout << "�������� ���������� = " << std::endl;
	this->swap(list);
	list.head_ = nullptr;
	list.tail_ = nullptr;
	list.count_ = 0;
	return *this;
}

// �������� �������������� ���� � ����� ������
void DoubleLinkedList::insertTail(Node* x)
{
	// task 5 
	x->prev_ = tail_;
	if (tail_ == nullptr) {
		// ������ ��� ���� � ����� ������� ����� � ������, � ���������
		head_ = x;
	}
	else {
		tail_->next_ = x;
	}
	tail_ = x;
	count_++;  // ����� ��������� ������ �����������
}

// �������� �������������� ���� � ������ ������
void DoubleLinkedList::insertHead(Node* x)
{
	x->next_ = head_;
	if (head_ != nullptr) {
		// ������ ��� �� ���� � ����� ������� ����� � ������, � ���������
		head_->prev_ = x;
	}
	else {
		// ������ ��� ���� � ����� ������� ����� � ������, � ���������
		tail_ = x;
	}
	head_ = x;
	count_++;  // ����� ��������� ������ �����������
}

// �������� ��������� ���� 
void DoubleLinkedList::deleteNode(Node* x)
{
	if (x == nullptr) {
		throw ("DoubleLinkedList::deleteNode  - ������� ����� ����� ���������� ����");
	}
	if (x->prev_ != nullptr) {
		// ��������� �� ������ ������
		(x->prev_)->next_ = x->next_;
	}
	else {
		// ��������� ������ ������,  ������ ������� ���������� ������
		head_ = x->next_;
	}
	if (x->next_ != nullptr) {
		// ��������� �� �����
		(x->next_)->prev_ = x->prev_;
	}
	else {
		// ��������� �����
		tail_ = x->prev_;
	}
	delete x;      // 
	count_--;     // ����� ��������� ������ �����������
}

// ����� ���� (�����) � �������� ���������  
DoubleLinkedList::Node* DoubleLinkedList::searchNode(int item)
{
	Node* x = head_;
	while (x != nullptr && x->item_ != item) {
		x = x->next_;
	}
	return x;
}

// ������ ���������� ���� �� ����� 
DoubleLinkedList::Node* DoubleLinkedList::replaceNode(DoubleLinkedList::Node* x, int item)
{
	// task 6
	x->item_ = item;
	return x;
}

// ������ � ���������� ��������� ���� ������
int DoubleLinkedList::headItem() const
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - ������ ����!");
}
int& DoubleLinkedList::headItem()
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - ������ ����!");
}

// ������ � ���������� ���������� ���� ������
int DoubleLinkedList::tailItem() const
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - ������ ����!");
}
int& DoubleLinkedList::tailItem()
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - ������ ����!");
}

// �������� ������� � ������ ������
void DoubleLinkedList::insertHead(int item)
{   // ������� ����� ������� ������ � ��������� � ������ 
	insertHead(new Node(item));
}

// �������� ������� � ����� ������
void DoubleLinkedList::insertTail(int item)
{   // ������� ����� ������� ������ � ��������� � ����� 
	insertTail(new Node(item));
}

// ������� ������� � ������ ������
bool DoubleLinkedList::deleteHead()
{
	if (head_ == nullptr) {
		return 0;  // ������ ����, �������� ���
	}
	deleteNode(head_);
	return 1;      // ������ ��� �� ����, �������� ������
}

// ������� ������� �� ������ ������
bool DoubleLinkedList::deleteTail()
{
	// task 7
	if (tail_ == nullptr) {
		return 0;  // ������ ����, �������� ���
	}
	deleteNode(tail_);
	return 1;
}

// �������� ���� � �������� ���������  
bool DoubleLinkedList::deleteItem(const int item)
{
	// task 8
	if (searchItem(item) == false) {
		return false;
	}
	else {
		Node* prevDdel = this->head_;
		while (prevDdel->item_ != item) {
			prevDdel = prevDdel->next_;
		}
		deleteNode(prevDdel);
	}
	return true;
}

// ����� ������ � �������� ���������  
bool DoubleLinkedList::searchItem(int item)
{   // ���������� TRUE, ���� ���� ������ 
	return (searchNode(item) != nullptr);
}

// ������ ���������� ���� �� ����� 
bool DoubleLinkedList::replaceItem(int itemOld, int itemNew, bool all)
{
	// ���� ����� �������� �� ���� �������� 
	if (!all) {
		if (itemOld == itemNew) {
			return true;
		}
		else if (searchItem(itemOld) == false) {
			return false;
		}
		else {
			Node* prevDdel = this->head_;
			while (prevDdel->item_ != itemOld) {
				prevDdel = prevDdel->next_;
			}
			replaceNode(prevDdel, itemNew);
		}
		
	}
	else{
		Node* prevDdel = this->head_;
		while (prevDdel->next_!= nullptr) {
			replaceNode(prevDdel, itemNew);
			prevDdel = prevDdel->next_;
		}
		replaceNode(prevDdel, itemNew);
	}
	return true;
}

// ����� ��������� ������ � ��������� ���� � ����������� �������� ����� 
void DoubleLinkedList::outAll()
{
	Node* current = head_;       // ��������� �� �������
	while (current != nullptr) {
		std::cout << current->item_ << ' ';
		current = current->next_;  // ������� � ���������� ��������
	}
	std::cout << std::endl;
}

bool DoubleLinkedList::operator==(const DoubleLinkedList& list)
{
	Node* l = this->head_;
	Node* r = list.head_;
	if (this->count_ != list.count_) {
		return false;
	}
	else {
		if (l->item_ != r->item_) return false;
		while (l->item_ == r->item_ && l->next_ != nullptr) {
			if (l->item_ != r->item_) {
				return false;
			}
			l = l->next_; r = r->next_;
		}
	}
	return true;
}

// ���������� ������	
DoubleLinkedList::~DoubleLinkedList()
{
	// std::cout << "�������� ����������" << std::endl;
	Node* current = nullptr;   // ��������� �� �������, ���������� ��������
	Node* next = head_;        // ��������� �� ��������� �������
	while (next != nullptr) {  // ���� ���� ��� �������� � ������
		current = next;
		next = next->next_;    // ������� � ���������� ��������
		delete current;        // ������������ ������
	}
}

std::ostream& operator<<(std::ostream& out, DoubleLinkedList list)
{
	DoubleLinkedList::Node* current = list.head_;       // ��������� �� �������
	while (current != nullptr) {
		out << current->item_ << ' ';
		current = current->next_;  // ������� � ���������� ��������
	}
	out << std::endl;
	return out;
}

// task  12 
void DoubleLinkedList::AddList(DoubleLinkedList& src) {
	if (src == *this) {

	}
	else {
		Node* noder = src.head_;
		while (noder != nullptr) {
			this->insertTail(noder);
			noder = noder->next_;

		}
		src.count_ = 0;
		src.head_ = nullptr;
		src.tail_ = nullptr;
	}
}