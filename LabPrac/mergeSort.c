#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int low, int mid, int high, int *comp)
{
    int temp[high - low + 1];
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high)
    {
        (*comp)++;
        if (arr[i] < arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid)
    {
        (*comp)++;
        temp[k++] = arr[i++];
    }
    while (j <= high)
    {
        (*comp)++;
        temp[k++] = arr[j++];
    }
    k = 0;
    for (i = low; i <= high; i++)
    {
        arr[i] = temp[k++];
    }
}

void mergeSort(int arr[], int low, int high, int *comp)
{
    if (low < high)
    {
        int mid = ((high + low) / 2);
        mergeSort(arr, low, mid, comp);
        mergeSort(arr, mid + 1, high, comp);
        merge(arr, low, mid, high, comp);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d \t", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {3, 8, 0, 9, 6, 5, 1, 2, 4, 7};
    int size = 10;
    int comp = 0;
    printf("Array before sorting:\t");
    printArray(arr, size);
    mergeSort(arr, 0, size - 1, &comp);
    printf("Array after sorting:\t");
    printArray(arr, size);
    printf("%d \t", comp);
    return 0;
}