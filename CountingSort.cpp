//CountingSort задание максимального ("опорного") элемента через
//поиск в массиве, либо через максимальный рандомный эл-та


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int* CountingSort(int* sourceArray, int size, int max)
{
    int* buffer = new int [max - 1];
    int* array = new int [size];
    
    for(int j = 0; j < max - 1; j++)
        buffer[j] = 0;
        
    for(int i = 0; i < size; i++)
        buffer[sourceArray[i]]++;
        
    //Какое кол-во эл-тов не превышает max
    for(int i = 1; i < max; i++)
        buffer[i] = buffer[i] + buffer[i - 1];
    
    for(int i = (size - 1); i >= 0; i--)
    {
        array[buffer[sourceArray[i]] - 1] = sourceArray[i];
        buffer[sourceArray[i]]--;
    }
    
    return array;
}


int main()
{
    
    int n{0}, maxA{0};
    std::cin >> n;
    int * A = new int [n];
    int* B = new int [n];
    int index = 0;
    srand ( time(NULL) );
    for(int i = 0; i < n; i++)
        A[i] = rand() % 100; //maxA;
        
    //Поиск максимального элемента в массиве
    for(int i = 0; i < n; i++)
        {
            if(maxA < A[i])
            {
                maxA = A[i];
                index = i;
            }
        }
    //Устанавливаем максимальный эл-т в конец массива
        int tmp = A[index];
        A[index] = A[n - 1];
        A[n - 1] = tmp;
        
    for(int i = 0; i < n; i++)
        std::cout << A[i] << " ";
    std::cout << std::endl;
    //Вызов функции через поиск максимального эл-та в массиве
    B = CountingSort(A, n, maxA + 1);
    
    //Вызов функции через задания максимального рандомного элемента
    //B = CountingSort(A, n, maxA);
    
    for(int i = 0; i < n; i++)
        std::cout << B[i] << " ";
    std::cout << std::endl;
    
    
    return 0;
}
