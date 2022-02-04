#ifndef STACK_HPP
#define STACK_HPP

template <class T>
class Stack
{
public:
  virtual ~Stack() = default;
  virtual void push(const T& e) = 0; // ���������� �������� � ����
  virtual const T& pop() = 0; // �������� � ����������� �������� ��������. // ���� ��������� ���, ����� ���������� StackUnderflow	  
  virtual bool isEmpty() const = 0; // �������� ����� �� �������
};

#endif 
