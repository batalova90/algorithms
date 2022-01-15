#include <iostream>
#include <ctime>


template<typename T>
void ChangeElements(T* array, int left, int right)
{
    T temp = array[left];
    array[left] = array[right];
    array[right] = temp;
}

template<typename T>
int Partition(T* array, int left, int right)
{
    T x = array[right];
    int i = left;
    for (int j = left; j <= right - 1; j++)
    {
        if (array[j] <= x)
        {
            ChangeElements(array, i, j);
            i++;
        }
    }
    ChangeElements(array, i, right);

    return i;
}


template<typename T>
void QuickSort(T* sourceArray, int left, int right)
{
    int q;
    
    if (left < right)
    {       
        q = Partition(sourceArray, left, right);
        QuickSort(sourceArray, left, q - 1);
        QuickSort(sourceArray, q + 1, right);
    }
}

int main()
{
    int sizeArray = 10;
    int* array = new int[sizeArray];

    for (int i = 0; i < sizeArray; i++)
        std::cin >> array[i];

    QuickSort(array, 0, sizeArray - 1);

    for (int i = 0; i < sizeArray; i++)
        std::cout << array[i] << ", ";

    return 0;
}
