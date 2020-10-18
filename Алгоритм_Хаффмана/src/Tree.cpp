#include "Huffman_algorithm.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>

using pointer = std::shared_ptr<Node>;
using uchar = unsigned char;
using pQueue = std::priority_queue<Node::pointer, std::vector<Node::pointer>, changedPriority>;

bool Node::operator < (const Node& other) const
{
   return frequency < other.frequency;
}
int Node::getFrequency() const
{
   return frequency;
}
std::string Node::code() const
{
   return code_string;
}
void Node::code(std::string str)
{
   code_string = str;
}
void Node::setFrequency(int freq)
{
   frequency = freq;
}

std::string Node::getName() const
{
   if(ch == 0)
      return name;
   else
   {
         if(ch == 10)
            return "\\n";
   }

      return std::string(1, static_cast<char>(ch));

}

uchar Node::getByte() const
{
   return ch;
}

void buildTree(pQueue& myQueue)
{
   while(myQueue.size() > 1)
   {
      //Строим дерево
      //Удаляем два элемента (п. /n и k) и создаем новый элемент (1 - /nk)
      Node::pointer x = myQueue.top();
      myQueue.pop();
      Node::pointer y = myQueue.top();
      myQueue.pop();
      std::string name = x->getName() + y->getName();
      Node::pointer z = std::make_shared<Node>(name, x->getFrequency() + y->getFrequency());
      z->left = x;
      z->right = y;
      x->parent = z;
      y->parent = z;
      myQueue.push(z);
   }


}


void makeCode(Node::pointer& root, std::string str, std::vector<std::string>& codes)
{
     if(root->left != nullptr)
        makeCode(root->left, str + "0", codes);
     if(root->right != nullptr)
        makeCode(root->right, str + "1", codes);
      //Собираем код в строку
     if(root->left == nullptr && root->right == nullptr)
     {
        root->code(str);
        codes[root->getByte()] = str;
        //std::cout << "leaf: " << *root << " code: " << root->code() << std::endl;
     }

}



