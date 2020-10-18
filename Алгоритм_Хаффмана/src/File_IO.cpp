#include "Huffman_algorithm.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <bitset>


using uchar = unsigned char;

//функция, которая говорит от размере файла

std::ifstream::pos_type get_size(const std::string& file)
{
      //сразу переносимся в конец файла и спрашиваем где находимся
   std::ifstream ifs(file, std::ifstream::ate);
   return ifs.tellg();
}

void read_file(const std::string& filename, std::vector<int>& frequency)
{
   std::ifstream input(filename, std::ifstream::binary);
   int filesize = get_size(filename);
   int j = 0;
   while(true)
   {
      char ch; //читаем из файла по байтам
      input.read(&ch, 1); //функция принимает указатель на char, который от -128 до 127
      if(input.eof())
      {
         break;
      }

      frequency[static_cast<uchar>(ch)]++; //static_cast, чтобы все charы были положительными
      //std::cout << static_cast<unsigned int>(ch) <<", ";
     //последний символ перевода картеки читается два раза!!!Убрать!
       
      if(j % 20 == 0)
      {
         int value = (j + filesize%20) * 100 / filesize; //сколько в процентах считали файл
         std::cout << "\r" << value << " % " << std::flush; //перезаписываем проценты, без перевода каретки
      }
      j++;
   }

   std::cout << std::endl;

}

void console_output(std::vector<int>& frequency)
{
   for(int i = 0; i < frequency.size(); i++)
      {  
         if (frequency[i] != 0)
            std::cout << "[ " << char(i) << " ] = " << frequency[i] << ",\n";
      }
   std::cout << std::endl;
}


std::ostream& operator << (std::ostream& os, const Node& node)
{
   return os << "[ " << node.getName() << " ] = " << node.frequency;
}

using pQueue = std::priority_queue<Node::pointer, std::vector<Node::pointer>, changedPriority>;

void writeFile(const std::string& filename, std::vector<int>& frequency,const pQueue queue, const std::string mesage)
{
      std::string new_file = filename + ".hff";
      std::ofstream ofs(new_file, std::ofstream::binary);
      if(!ofs)
      {
         std::cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno);
         return;
      }
      
      uchar count = std::count_if(frequency.begin(), frequency.end(), [] (const int& value){return (value != 0);});
      std::cout << "Count: " << int(count) << std::endl;

      ofs.write(reinterpret_cast<char*>(&count), sizeof count);
      
      for_each(frequency.begin(), frequency.end(), [index = uchar(0), &ofs](int& value)mutable 
            {
               if(value != 0)
               {
                  std::cout << "[ " << index << " ] = " << value << "\n";
                  ofs.write(reinterpret_cast<char*>(&index), sizeof index);
                  ofs.write(reinterpret_cast<char*>(&value), sizeof value);
               }
               ++index;
            });
      int byte_count = mesage.size() / CHAR_BIT; //1 byte = 8 bits
      uchar modulo = mesage.size() % CHAR_BIT;
      std::cout << "byte count: " << byte_count << " of size " << mesage.size() << std::endl;
      std::cout << "modulo: " << (int)modulo << " of size " << mesage.size() << std::endl;
      
      ofs.write(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
      ofs.write(reinterpret_cast<char*>(&modulo), sizeof modulo);
      
      int i = 0;
      for(; i < byte_count; ++i)
      {
         std::cerr << "Here " << std::endl;
         std::bitset<CHAR_BIT> b(mesage.substr(i * CHAR_BIT, CHAR_BIT));
         std::cerr << "Here!!" << std::endl;
         uchar value = static_cast<uchar>(b.to_ulong());
         ofs.write(reinterpret_cast<char*>(&value), sizeof value);
      }

      if(modulo > 0)
      {
         std::bitset<CHAR_BIT> b(mesage.substr(i * CHAR_BIT, modulo));
         uchar value = static_cast<uchar>(b.to_ulong());
         ofs.write(reinterpret_cast<char *>(&value), sizeof value);
      }

}

std::string message2code(const std::string& filename, const std::vector<std::string>& codes)
{
   std::string msg{""};
   std::ifstream ifs(filename, std::ifstream::binary);
   
   while(true)
   {
      char ch;
      ifs.read(&ch, 1);

      if(ifs.eof())
         break;
      msg+= codes[static_cast<uchar>(ch)] + "|";
   }
   return msg;
}

void readDecodingFile(std::string& filename, std::vector<int>& frequency, std::string& message)
{
   std::string new_filename = filename + ".hff";
   std::ifstream ifs(new_filename, std::ifstream::binary);
   if(!ifs)
   {
      std::cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno);
      return;
   }

   uchar count = 0;
   ifs.read(reinterpret_cast<char*>(&count), sizeof count);
   std::cout << "New count: " << (int)count << std::endl;

   int i = 0;
   while(i < count)
   {
      uchar ch;
      ifs.read(reinterpret_cast<char*>(&count), sizeof ch);

      int f = 0;
      ifs.read(reinterpret_cast<char*>(&f), sizeof f);
      frequency[ch] = f;

      ++i;
   }
   
   std::cout << "Decoding file: " << "\n";
   for_each(frequency.begin(), frequency.end(), [index = uchar(0)] (const int & value)mutable 
         {
            if(value != 0)
            {
               std::cout << "[" << static_cast<char>(index) << "] = " << value << "\n";
            }
            ++index;
         });
   int byte_count = 0;
   uchar modulo = 0;

   ifs.read(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
   ifs.read(reinterpret_cast<char*>(&modulo), sizeof modulo);

   std::cout << "New byte count: " << byte_count << "\n";
   std::cout << "New modulo: " << (int)modulo << "\n";

   i = 0;
   for(; i < byte_count; i++)
   {
       uchar byte;
       ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);

       std::bitset<CHAR_BIT> b(byte);
       message += b.to_string();
   }

   if(modulo > 0)
   {
      uchar byte;
      ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);
      std::bitset<CHAR_BIT> b(byte);
      message += b.to_string().substr(CHAR_BIT - modulo, CHAR_BIT);
      //0000 0110 <-- this is b
      //необходимо брать последние три бита,которые мы забираем
   }
}



void writeDecodingFile(const std::string& filename, const std::string& text)
{
   std::string new_filename = filename + ".s";
      std::ofstream ofs(new_filename, std::ofstream::binary);
   if(!ofs)
   {
      std::cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno);
      return;
   }
   ofs << text;

}

