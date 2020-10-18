#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>

using uchar = unsigned char;
//Не забыть вынести в отдельный заголовочный файл
class Node
{
   private:
      uchar ch {0};
      int frequency {0};
      std::string name{""};
      
   public:
      Node() = default;
      Node(uchar symbol, int f) : ch(symbol), frequency(f) {};
      Node(std::string& n, int f) : frequency(f), name(n) {};
      friend std::ostream& operator<<(std::ostream& os, const Node& node);
      using pointer = std::shared_ptr<Node>;
      pointer left{nullptr};
      pointer right{nullptr};
      pointer parent{nullptr};
      std::string code_string{""};
      
      bool operator < (const Node& other) const;
      int getFrequency() const;
      std::string code() const;
      void code(std::string str);
      void setFrequency(int freq);
      std::string getName() const;
      uchar getByte() const;
};

std::ifstream::pos_type get_size(const std::string& file);
void read_file(const std::string& filename, std::vector<int>& frequency);
void console_output(std::vector<int>& frequency);

//функтор для того, чтобы изменить приоритет у очереди
class changedPriority
{
  public:
     bool operator() (const Node::pointer& left, const Node::pointer& right) const
     {
         return left->getFrequency() > right->getFrequency();
     }
};
using pQueue = std::priority_queue<Node::pointer, std::vector<Node::pointer>, changedPriority>;

void buildTree(pQueue& myQueue);

//задание кода при обходе дерева
void makeCode(Node::pointer& root, std::string str, std::vector<std::string>& codes);
void writeFile(const std::string& filename, std::vector<int>& frequency,const pQueue queue, const std::string mesage);
std::string message2code(const std::string& filename, const std::vector<std::string>& codes);
void readDecodingFile(std::string& filename, std::vector<int>& frequency, std::string& message);
void writeDecodingFile(const std::string& filename, const std::string& text);
 


   

