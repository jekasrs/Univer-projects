#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

#include "Stack.h"

template <class T>
class StackArray : public Stack<T> {

public:
  StackArray(int size = 30); // size ������ ������ ����� "�� ���������"

  StackArray(const StackArray<T>& src);
  StackArray(StackArray<T>&& src) noexcept;
  StackArray& operator=(const StackArray<T>& src);
  StackArray& operator=(StackArray<T>&& src);
  ~StackArray() override;

  void push(const T& e);
  const T& pop();
  const size_t& getTop();
  bool isEmpty() const noexcept;

private:
  T* array_; // ������ ��������� �����: !!! array_[0] � �� ������������, top_ �� 1 �� size_
  size_t top_; // ������� �����, ������� ���������� � ���� ���������
  size_t size_; // ������ �����
  void swap(StackArray<T>& src) noexcept;
};

#endif
