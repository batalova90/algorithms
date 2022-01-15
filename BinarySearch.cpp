//The file contains the Binary search algorithm and basic sorting algorithms

#include <iostream>
#include <limits>

template <typename T> void Merge(T* array, int p, int q, int r);
template <typename T> void CopyArray(T* sourceArray, T* arrayToCopy, int size, int offset);

template <typename T>
int BinarySearch(T* sortedArray, int size, T key)
{
    int p, q;
    int n = size;
    p = 0;
    while (p <= n)
    {
        q = (n + p) / 2;
        if (sortedArray[q] == key)
            return q;
        else if (sortedArray[q] > key)
        {
            n = q - 1;
        }
        else
        {
            p = q + 1;
        }
    }
    return -1;
}

template <typename T>
void SelectionSort(T* array, int size)
{
    int small = 0;
    T tmp = 0;
    for (int i = 0; i < size; i++)
    {
        small = i;
        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[small])
            {
                small = j;
            }
        }
        tmp = array[i];
        array[i] = array[small];
        array[small] = tmp;
    }
}

template <typename T>
void InsertionSort(T* array, int size)
{
    T key;
    int j = 0;
    for (int i = 1; i < size; i++)
    {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

template <typename T>
void MergeSort(T* array, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        MergeSort(array, p, q);
        MergeSort(array, q + 1, r);
        Merge(array, p, q, r);
    }
}

template <typename T>
void Merge(T* array, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    T* copyArray1 = new T[n1 + 1];
    T* copyArray2 = new T[n2 + 1];
    for (int i = 0; i < n1; i++)
    {
        copyArray1[i] = array[i + p];
    }
    for (int j = 0; j < n2; j++)
    {
        copyArray2[j] = array[q + j + 1];
    }
    //Устанавливаем ограничитель
    copyArray1[n1] = std::numeric_limits <T> ::max();
    copyArray2[n2] = std::numeric_limits <T> ::max();
    int i = 0, j = 0;
    for (int k = p; k <= r; k++)
    {
        if (copyArray1[i] <= copyArray2[j]) //если эл-т одного массива меньше другого, то ставим его обратно в исходный массив
        {
            array[k] = copyArray1[i];
            i++;
        }
        else
        {
            array[k] = copyArray2[j];
            j++;
        }
    }
}

template <typename T>
void CopyArray(T* sourceArray, T* arrayToCopy, int size, int offset)
{
    for (int i = 0; i < size; i++)
    {
        arrayToCopy[i] = sourceArray[i + offset];
        std::cout << i << " " << arrayToCopy[i] << std::endl;
    }
}

int main()
{
    int sizeArray = 4;
    int* array = new int[sizeArray];
    for (int i = 0; i < sizeArray; i++)
    {
        std::cin >> array[i];
    }

    //std::cout << BinarySearch<int>(array, sizeArray, 2) << std::endl;
    MergeSort<int>(array, 0, sizeArray);
    for (int i = 0; i < sizeArray; i++)
        std::cout << array[i] << std::endl;

    return 0;
}

