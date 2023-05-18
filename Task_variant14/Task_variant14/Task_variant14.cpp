#include <iostream>
#include <vector>
#include <omp.h>

// Функція для швидкого сортування
void quickSort(std::vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    // Розподіл елементів навколо опорного елемента
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    // Рекурсивний виклик для лівої та правої частин масиву
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            if (left < j)
                quickSort(arr, left, j);
        }

        #pragma omp section
        {
            if (i < right)
                quickSort(arr, i, right);
        }
    }
}

int main() {
    std::vector<int> arr = {9, 3, 2, 7, 1, 5, 6, 8, 0, 4};

    std::cout << "Original array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    // Виклик функції швидкого сортування
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            quickSort(arr, 0, arr.size() - 1);
        }
    }

    std::cout << "Sorted array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}