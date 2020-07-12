//#include "header.h"
#include <iostream>

template <typename T>
class Stack
{
   
  public:
      Stack();
      //Stack(int range):Stack();
      ~Stack();
      void Push(T top);
      void Pop();
      T Top();
      int Capacity();
      void AddMemory();
      bool empty();
      void Swap(Stack<T> &object);
  private:
      T* head;
      int Size;
      int Amount;
      T* array;
      bool StackOverFlow();
      bool StackEmpty();

};

template <typename T> Stack<T>:: Stack()
{
      Size = 100;
      array = new T [Size];
      head = array;
      Amount = 0;
   
}


template <typename T> Stack<T>::~Stack()
{
      Amount = 0;
      head = nullptr;
      delete [] array;
      Size = 0;
}

template <typename T> void Stack<T>::Push(T top)
{
   if(StackOverFlow())
   {
      array[Amount] = top;
      head = array + Amount;
      Amount++;
   }
   else
   {
      std::cout << "Overflow!!!" << std::endl;
   }

}

template <typename T> void Stack<T>::Pop()
{
   if(StackEmpty())
   {
      array[Amount] = 0;
      Amount--;
      head--;
   }
   else
      std::cout << "Underflow!!!" << std::endl;
}

template <typename T> bool Stack<T>::StackOverFlow()
{
   return Amount < Size;
}

template <typename T> bool Stack<T>::StackEmpty()
{
   return Amount != 0;
}

template <typename T> int Stack<T>::Capacity()
{
   return Size - Amount;
}

template <typename T> T Stack<T>::Top()
{
   return *head;
}

template <typename T> bool Stack<T>::empty()
{
   return Amount == 0;
}

template <typename T> void Stack<T>::Swap(Stack<T>& object)
{
   T* tmp = this->head;
   this->head = object.head;
   object.head = tmp;
   
   tmp = this->array;
   this->array = object.array;
   object.array = tmp;
   tmp = nullptr;

   int tmp_Amount = this->Amount;
   this->Amount = object.Amount;
   object.Amount = tmp_Amount;
}
