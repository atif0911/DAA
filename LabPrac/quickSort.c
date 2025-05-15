// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// int partition(int arr[], int low, int high, int *comp, int piv)
// {
//     int temp = arr[piv];
//     arr[piv] = arr[high];
//     arr[high] = temp;

//     piv = arr[high];
//     int i = low - 1;
//     int j;
//     for (j = low; j < high; j++)
//     {
//         (*comp)++;
//         if (arr[j] < piv)
//         {
//             i++;
//             temp = arr[i];
//             arr[i] = arr[j];
//             arr[j] = temp;
//         }
//     }
//     temp = arr[i + 1];
//     arr[i + 1] = arr[high];
//     arr[high] = temp;
//     return i + 1;
// }

// void quickSort(int arr[], int low, int high, int *comp, int pivCh)
// {
//     static int pivIdx;
//     if (low < high)
//     {
//         if (pivCh == 1)
//         {
//             pivIdx = low;
//         }
//         if (pivCh == 2)
//         {
//             pivIdx = high;
//         }
//         if (pivCh == 3)
//         {
//             pivIdx = (high + low) / 2;
//         }
//         if (pivCh == 4)
//         {
//             pivIdx = low + rand() % (high - low + 1);
//         }
//         pivIdx = partition(arr, low, high, comp, pivIdx);
//         quickSort(arr, low, pivIdx - 1, comp, pivIdx);
//         quickSort(arr, pivIdx + 1, high, comp, pivIdx);
//     }
// }

// void printArray(int arr[], int size)
// {
//     int i;
//     for (i = 0; i < size; i++)
//     {
//         printf("%d \t", arr[i]);
//     }
//     printf("\n");
// }
// int main()
// {
//     srand(time(NULL));
//     // int arr[] = {3, 8, 0, 9, 6, 5, 1, 2, 4, 7};
//     int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     int size = 10;
//     int comp = 0;
//     int pivCh = 2;
//     printf("Array before sorting:\t");
//     printArray(arr, size);
//     for (int i = 1; i <= 4; i++)
//     {
//         pivCh = i;
//         quickSort(arr, 0, size - 1, &comp, pivCh);
//         printf("Array after sorting:\t");
//         printArray(arr, size);
//         printf("%d \t", comp);
//         printf("\n");
//         comp = 0;
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int partition(int arr[], int low, int high, int pivIdx, int *comp)
{
    int temp = arr[high];
    arr[high] = arr[pivIdx];
    arr[pivIdx] = temp;

    int pivot = arr[high];
    int i = low - 1, j;

    for (j = low; j < high; j++)
    {
        (*comp)++;
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    temp = arr[high];
    arr[high] = arr[i + 1];
    arr[i + 1] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high, int pivot, int *comp)
{
    if (low < high)
    {
        int pivIdx;
        if (pivot == 1)
            pivIdx = low;
        if (pivot == 2)
            pivIdx = high;
        if (pivot == 3)
            pivIdx = (high + low) / 2;
        if (pivot == 4)
            pivIdx = low + rand() % (high - low + 1);
        pivIdx = partition(arr, low, high, pivIdx, comp);
        quickSort(arr, low, pivIdx - 1, pivot, comp);
        quickSort(arr, pivIdx + 1, high, pivot, comp);
    }
}

int main()
{
    srand(time(NULL));
    // int arr[] = {5, 2, 1, 7, 3, 4, 9, 10, 6, 8};
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    int pivot = 1;
    int comp = 0;

    printf("Before Sorting\n");
    printArray(arr, size);
    quickSort(arr, 0, size - 1, pivot, &comp);
    printf("After Sorting\n");
    printArray(arr, size);
    printf("\nNumber of Comparisons =%d\n", comp);
    return 0;
}