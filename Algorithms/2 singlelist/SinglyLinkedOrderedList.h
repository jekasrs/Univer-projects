#pragma once

#include <fstream>

template<typename T>
class SinglyLinkedOrderedList
{
public:
	SinglyLinkedOrderedList();   //����������� "�� ���������"
	~SinglyLinkedOrderedList(); //����������
	SinglyLinkedOrderedList(SinglyLinkedOrderedList<T>& src) noexcept;
	SinglyLinkedOrderedList(SinglyLinkedOrderedList<T>&& src) noexcept;
	SinglyLinkedOrderedList<T>& operator=(SinglyLinkedOrderedList<T>&& src);
	void addList(SinglyLinkedOrderedList& other); 
	// ����������� �������� ( � ������ ) ��� ����������
	// �� 2 ��������  - ������ ����������� ������ 
	void substractionList(SinglyLinkedOrderedList& other); 
	// �������� �� ������ ������, ���� ��� ���� � ������  
	void insertItem(T data);   // ���������� � ������ 
	bool deleteItem(T data);  // �������� ���� � �������� ���������
	bool searchItem(T data); // ����� ������ � �������� ���������
	void print() const;     // ����� ������ 
	int getSize() { return count_; };

	template<typename T>
	friend SinglyLinkedOrderedList<T> mergeList(SinglyLinkedOrderedList<T>& list1, SinglyLinkedOrderedList<T>& list2);
	// ����� ������� ������ �� ����� ���� ���� �������� 

private:
	template<typename T>
	struct Node
	{
		Node* next_;
		T item_;

		Node(T item = T(), Node* next = nullptr) 
			//����������� ��� �������� ������ ��������
		{
			this->item_ = item;
			this->next_ = next;
		}
	};
	Node<T>* head_; //��������� �� ������
	int count_; //���������� ���������
	void deleteNode(Node<T>* data);
	// �������� ��������� ���� 
	Node<T>* searchNode(T data);
	// ����� ���� (�����) � �������� ���������
};

