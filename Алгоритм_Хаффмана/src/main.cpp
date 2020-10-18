#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "Huffman_algorithm.h"
#include <cstring>
#include <algorithm>
#include <bitset> //после переноса в decoding file все библиотеки ненужные удалить!!
#include <limits.h>

//#include <chrono>
using uchar = unsigned char; //не забыть убрать через оператора области видимости!!!А так он во всех трех файлах
using pointer = std::shared_ptr<Node>;



void make_char(const Node::pointer& root, const std::string& message, std::string& text)
{
   Node::pointer node = root;

   for(size_t i = 0; i < message.size(); ++i)
   {
      char ch = message[i];
      if(ch == '0')
      {
         if(node->left != nullptr)
         {
            node = node->left;
            if(node->left == nullptr && node->right == nullptr)
            {
               text += node->getByte();
               node = root;
            }
         }
      }
      else if(ch == '1')
      {
         if(node->right != nullptr)
         {
            node = node->right;
            if(node->left == nullptr && node->right == nullptr)
            {
               text += node->getByte();
               node = root;
            }
         }

      }
   }
   std::cout << "Text: " << text << std::endl;
}

int main()
{
   std::string fileForRead = "../data/text.txt";
   std::vector<int> frequency(0x100, 0);
   read_file(fileForRead, frequency);
   console_output(frequency);

  //Алгоритм Хаффмана(сжатие информации)
  //Заведем очередь с приоритетом и поместим туда символы в зависимости от частоты
   using pQueue = std::priority_queue<Node::pointer, std::vector<Node::pointer>, changedPriority>;  
   pQueue myQueue;
   
   for(int i = 0; i < frequency.size(); i++)
   {
      if(frequency[i] != 0)
      {
         Node::pointer node = std::make_shared<Node>(i, frequency[i]);
         myQueue.push(node);
      }
   }
   buildTree(myQueue); 
   //Функция для создания кода при обходе дерева
   std::vector<std::string> codes(0x100, "");
   Node::pointer root = myQueue.top();
   makeCode(root, "", codes);
   
   std::string message = message2code(fileForRead, codes);
   std::cout << "Message" << std::endl;
   std::cout << message << std::endl;

   writeFile(fileForRead, frequency, myQueue, message);
   //decoder файла с расширением .hff
   std::vector<int> frequency2(0x100, 0);
   std::string message2 = "";
   readDecodingFile(fileForRead, frequency2, message2);

   pQueue queue2;

   //fill_queue(frequency2, queue2);
   for(int i = 0; i < frequency.size(); i++)
   {
      if(frequency[i] != 0)
      {
         Node::pointer node = std::make_shared<Node>(i, frequency[i]);
         queue2.push(node);
      }
   }

   buildTree(queue2);
   
   Node::pointer root2 = queue2.top();
   std::string text = "";
   make_char(root2, message2, text);
   
   writeDecodingFile(fileForRead, text);

   //из-за отсутствия итераторов, печатать приходится, вынимая поэлементно из очереди
  // while(!myQueue.empty())
  // {
  //    std::cout << *(myQueue.top()) << std::endl;
  //    myQueue.pop();
  // }

   
   return 0;
}

