//Односвязный список
#include <iostream>
#include <string>
#include <fstream>

template <typename T> class List
   {
      public:
         List();
         ~List();
         void push_back(T data);
         //Реализация удаления первого элемента в списке
         void pop_front();
         //Геттер для сайз
         int GetSize(){return Size;}
         //Перегрузка оператора []
         T& operator[](const int index);
         //Очищение списка
         void clear();
         void print_List();
         void print_file();
         //Поместить элемент в начало списка
         void push_front(T data);
         //Поместить элемент по указанному индексу
         void insert(T value, int index);
         //Удаление по заданному индексу
         void removeAt(int index);
         //Удаление последнего элемента
         void pop_back();
         //Создание динамического списка из файла
         void read_List();
         void Caesar_code(int key);
         void Afin_code(int key_1, int key_2);
      private:
         template <typename T_Type>
         class Node
         {
            public:
               Node *pNext;
               T_Type data;
               Node(T_Type data=T(), Node *pNext=nullptr)
               {
                  this->data = data;
                  this->pNext = pNext;
               }
         };
      int Size; 
      Node<T> *head;

   };

template <typename T> List<T>:: List()
{
   Size = 0;
   head = nullptr;
}

template <typename T> List<T>::~List()
{
   clear();
}

template <typename T> void List<T>::push_back(T data)
{
   if (head == nullptr)
   {
      head = new Node<T>(data);
   }
   else 
   {
      Node<T> *current = this->head;
      while(current-> pNext != nullptr)
      {
         current = current->pNext;
      }
      current->pNext = new Node<T>(data);
   }
   Size++;
}

//Реализация получения элемента по индексу
template <typename T> T& List<T>::operator[](const int index)
{
      int counter = 0;
      Node<T> *current = this->head;
      while (current != nullptr)
      {
         if (counter == index)
         {
               return current->data;
         }
         current = current->pNext;
         counter++;
      }
}

//Печать элементов
template <typename T> void List<T>::print_List()
{
     Node<T> *current = this->head;
     while (current != nullptr)
     {
         std::cout << current->data << std::endl;
         current = current->pNext;
     }
     std::cout << "____________________" << std:: endl;
}

//Реализация удаления первого элемента
template <typename T> void List<T>::pop_front()
   {
      Node<T> *temp = head;
      head = head->pNext;
      delete temp;
      temp = nullptr;
      Size--;

   }

//Реализация удаления списка
template <typename T> void List<T>::clear()
   {
      while (Size)
      {
         pop_front();
         
      }
   }

//Поместить элемент в начало списка
template <typename T> void List<T>::push_front(T data)
   {
         head = new Node<T>(data, head);
         Size++;
   }

//Поместить элемент по указанному индексу
template <typename T> void List<T>::insert(T value, int index)
   {
         if (index == 0)
         {
            pop_front();
         }
         else
         {
         Node <T> *previous = this->head;
         for (int i = 0; i < index-1; i++)
         {
            //Находим предыдущий элемент, чтобы была возможность перекинуть ссылки
            previous = previous->pNext;
         }
         Node<T> *newNode = new Node<T>(value, previous->pNext);
         previous->pNext = newNode;
         }
   }
template <typename T> void List<T>::removeAt(int index)
   {
     if (index == 0)
     {
         pop_front();
     }
     else
     {
         Node<T> *previous = this->head;
         for(int i = 0; i < index - 1; i++)
         {
            previous = previous->pNext;

         }
         Node<T> *ToDelete = previous->pNext;
         previous->pNext = ToDelete->pNext;
         delete ToDelete;
         Size--;
     }
   }
template <typename T> void List<T>::pop_back()
   {
         removeAt(Size-1);
   }

template <typename T> void List<T>::print_file() //создание выходного файла
   {
      using namespace std;
     Node<T> *current = this->head;
      string output = "../bin/output.txt";
      //Очистка файла Вынести в отдельный метод
      ofstream fout;
      //fout.open(output);
      //fout.close();
     fout.open(output, ofstream::app);
     if (!fout.is_open())
     {
       cout << "Ошибка открытия файла!" << endl;
     }
      else
     {
       while (current != nullptr)
         {
         fout << current->data;
         current = current->pNext;
         }   
     }
      fout.close();
   }
template <typename T> void List<T>::read_List() //Чтение из файла

   {
      using namespace std;
      string input = "../data/input.txt";
      ifstream fin;
      fin.open(input);
      if (!fin.is_open())
         {
            cout << "Ошибка открытия файла" << endl;
         }
      else
         {
            char symbol;
            while (fin.get(symbol))      //Метод get считывает символы, пока их не станет совсем, метод eof пока не наста
                                         //конец файла;
            {                            //get также считает перевод каретки;
              push_back(symbol);         //метод getline считывает строки до знака перевода картеки,но принимает массив
                                         //char       
            }
         }
   }

template <typename T> void List<T>::Caesar_code(int key)
     {
        const int n = 26;
        int i = 0;
        char alphabet[n] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        char alphabet_big[n] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        Node<T> *current = this->head;
        while (current != nullptr)
        {
           while (i < n)
           { 
            if (current->data >= 97 and current->data <= 122)
             {
               if (current->data == alphabet[i])
               {
                  if (i + key < n)
                  {
                     current->data = alphabet[i + key];
                     i = n;
                  }
                  else
                  {
                     current->data = alphabet[i + key - n];
                     i = n;
                  }
            }
           }
            else
            {
               if (current->data == alphabet_big[i])
               {
                  if (i + key < n)
                  {
                     current->data = alphabet_big[i + key];
                     i = n;
                  }
                  else
                  {
                     current->data = alphabet_big[i + key - n];
                     i = n;
                  }
               }
            }
           i++;
           }
            current = current->pNext;
            i = 0;
        }
     }

template <typename T> void List<T>::Afin_code(int key_1, int key_2)
   {
        const int n = 26;
        int i = 0;
        char alphabet[n] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        char alphabet_big[n] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        Node<T> *current = this->head;

      while (current != nullptr)
        {
           while (i < n)
           { 
            if (current->data >= 97 and current->data <= 122)
             {
               if (current->data == alphabet[i])
               {
                  current->data = alphabet[(key_1 * i + key_2) % n];
                  i = n;
               }
            }
            else
            {
               if (current->data == alphabet_big[i])
               {
                  current->data = alphabet_big[(key_1 * i + key_2) % n];
                  i = n;
               }

            }
           i++;
           }
            current = current->pNext;
            i = 0;
        }
 
   }


 int main()
      {
         setlocale(LC_ALL, "ru");

         int k, m;
         //std:: cout << "Введите ключ для шифрования: " << std::endl;
         //std:: cin >> k;
         List<char> Symbol;
         Symbol.read_List();
         //Symbol.Caesar_code(k);
         Symbol.print_file();
         std::cout << "Введите ключи для широфания Афинный шифр: "<< std::endl;
         std:: cin >> k >> m;
         //Symbol.read_List();
         Symbol.Afin_code(k, m);
         Symbol.print_file();
         return 0;
   
      }
