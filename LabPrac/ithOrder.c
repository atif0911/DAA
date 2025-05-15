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

int randomPartition(int arr[], int low, int high)
{
    int Randpivot = low + rand() % (high - low + 1);

    int temp = arr[Randpivot];
    arr[Randpivot] = arr[high];
    arr[high] = temp;

    int pivot = arr[high];

    int i = low - 1, j;

    for (j = low; j <= high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

int ithOrder(int arr[], int low, int high, int order)
{
    if (low == high)
        return arr[low];

    int piv = randomPartition(arr, low, high);
    int k = piv - low + 1;

    if (k == order)
        return arr[piv];
    else if (k < order)
        return ithOrder(arr, piv + 1, high, order - k);
    else
        return ithOrder(arr, low, piv - 1, order);
}

int main()
{
    srand(time(NULL));
    int arr[] = {5, 2, 1, 7, 3, 4, 9, 10, 6, 8};
    //  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int order;

    printArray(arr, size);
    printf("Enter the ith term \n");
    scanf("%d", &order);

    int ith = ithOrder(arr, 0, size - 1, order);
    printf("The %dth term of the array is: %d\n", order, ith);

    return 0;
}