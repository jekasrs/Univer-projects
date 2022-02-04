#include"StackArray.h"

#include <utility>
#include "StackOverflow.h"
#include "StackUnderflow.h"
#include "WrongStackSize.h"

// ����� swap - ��������
template<class T>
inline void StackArray<T>::swap(StackArray<T>& src) noexcept
{
  std::swap(array_, src.array_);
  std::swap(top_, src.top_);
  std::swap(size_, src.size_);
}

// ����������� 
template<class T>
StackArray<T>::StackArray(int size) :
	size_(size),
	top_(0)
{
	try { // ������ ����� ������� � 1, � [0] - ������ ��� 
		array_ = new T[size + 1]; // ����� ������ ��� stackarray
	}
	catch (...) { // ... - ���� ���-�� ��������� 
		throw WrongStackSize();
	}
}

// ����������� ����������� 
template<class T>
StackArray<T>::StackArray(const StackArray<T>& src) :
	size_(src.size_),
	top_(src.top_)
{
	try
	{
		array_ = new T[src.size_ + 1];
	}
	catch (...)
	{
		throw WrongStackSize();
	}

	// ����������� ������� 
	for (int i = 0; i <= src.top_; i++) {
		array_[i] = src.array_[i];
	}
}

// ����������� ����������� 
template<class T>
StackArray<T>::StackArray(StackArray<T>&& src) noexcept
	//size_(src.size_),
	//top_(src.top_),
	//array_(src.array_)
{
	swap(src);
	src.size_ = 0;
	src.top_ = 0;
	src.array_ = nullptr;
}

// �������� ����������� 
template<class T>
StackArray<T>& StackArray<T>::operator=(const StackArray<T>& src)
{
	// ������� ��� ����� 
	delete[] array_;
	array_ = nullptr;

	// �������� �� r-v � l-v
	size_ = src.size_;
	top_ = src.top_;
	
	try
	{
		array_ = new T[src.size_ + 1];
	}
	catch (...)
	{
		throw WrongStackSize();
	}
	for (int i = 0; i <= src.top_; i++) {
		array_[i] = src.array_[i];
	}
}

// �������� ����������� 
template<class T>
StackArray<T>& StackArray<T>::operator=(StackArray<T>&& src)
{
	// ������� ��� �����
	delete[] array_;
	array_ = nullptr;

	// ����������
	size_ = src.size_;
	top_ = src.top_;
	array_ = src.array_;

	// ������� r-v
	src.size_ = 0;
	src.top_ = 0;
	src.array_ = nullptr;
}

// ���������� 
template<class T>
StackArray<T>::~StackArray()
{
	delete[] array_;
	array_ = nullptr;
	size_ = 0;
	top_ = 0;
}

template<class T>
void StackArray<T>::push(const T& e)
{
	if (top_ == size_) {
		throw StackOverflow(); // ��� ����� ��� ������ �������� 
	}
	else {
		array_[++top_] = e; // ��������� �������� � ���� 
	}
}

template<class T>
const T& StackArray<T>::pop()
{
	// ���� - ���� 
	if (top_ == 0) {
		throw StackUnderFlow();
	}
	// ������� "���������" �������� 
	return *(array_+top_--); // �������� 
}

template<class T>
const size_t& StackArray<T>::getTop()
{
	return top_;
}

template<class T>
bool StackArray<T>::isEmpty() const noexcept
{
	if (top_==0)
		return true;
	else return false;
}
