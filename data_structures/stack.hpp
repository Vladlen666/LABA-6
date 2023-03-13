#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class TType>
class TStack
{
private:
  TType* pMem;
  int size;
  int top;
  TStack(const TStack&) = delete; // ������ �� ����������� �����
  void operator=(const TStack&) = delete; // ������ �� ������������ �����

public:
  TStack(int _size = MaxStackSize) {// ����������� �� ���������
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw - 1;
    pMem = new TType[size];
  }

  ~TStack() {// ����������
    delete[] pMem;
  }

  bool empty() { return top == -1; } // �������� ������ �� ����

  bool full() { return top == size - 1; } // �������� �������� �� ����

  void push(const TType obj) {// ������� �������� � ������� �����
    if (full())
      throw - 1;
    pMem[++top] = obj;
  }

  TType pop() {// ��������� �������� �������� �������� � ���������
    if (empty())
      throw - 1;
    return pMem[top--];
  }

  TType tos() {// ��������� �������� �������� �������� ��� �������� // Top Of Stack
    if (empty())
      throw - 1;
    return pMem[top];
  }

};

#endif