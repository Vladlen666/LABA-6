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
  TStack(const TStack&) = delete; // Запрет на копирование стека
  void operator=(const TStack&) = delete; // Запрет на присваивание стека

public:
  TStack(int _size = MaxStackSize) {// Конструктор по умолчанию
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw - 1;
    pMem = new TType[size];
  }

  ~TStack() {// Деструктор
    delete[] pMem;
  }

  bool empty() { return top == -1; } // Проверка пустой ли стек

  bool full() { return top == size - 1; } // Проверка заполнен ли стек

  void push(const TType obj) {// Вставка элемента в вершину стека
    if (full())
      throw - 1;
    pMem[++top] = obj;
  }

  TType pop() {// Получение значения верхнего элемента с удалением
    if (empty())
      throw - 1;
    return pMem[top--];
  }

  TType tos() {// Получение значения верхнего элемента без удаления // Top Of Stack
    if (empty())
      throw - 1;
    return pMem[top];
  }

};

#endif