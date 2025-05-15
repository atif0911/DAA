#include <stdio.h>
#include <stdlib.h>
#define MAX 100
void printOptParen(int arr[MAX][MAX], int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        printOptParen(arr, i, arr[i][j]);
        printOptParen(arr, arr[i][j] + 1, j);
        printf(")");
    }
}

int matrixChainMul(int arr[], int size)
{
    int p[MAX][MAX], m[MAX][MAX];

    int i, j;
    for (i = 1; i < size; i++)
    {
        m[i][i] = 0;
    }
    int l, k, q;
    for (l = 2; l < size; l++)
    {
        for (i = 1; i < size - l + 1; i++)
        {
            j = i + l - 1;
            m[i][j] = INT_MAX;
            for (k = i; k < j; k++)
            {
                q = m[i][k] + m[k + 1][j] + (arr[i - 1] * arr[k] * arr[j]);
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    p[i][j] = k;
                }
            }
        }
    }
    printOptParen(p, 1, size - 1);
    return m[1][size - 1];
}

int main()
{
    int arr[] = {30, 35, 15, 5, 10, 20, 25};
    int size = sizeof(arr) / sizeof(arr[0]);

    int min = matrixChainMul(arr, size);
    printf("Minimun number of scalar multiplication required is : %d", min);
    return 0;
}