#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int *computePrefix(char *pattern, int *pi)
{
    int n = strlen(pattern), k;
    printf("Enterned Compute\n");
    pi[0] = 0;
    for (int i = 1; i < n; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
        {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[i])
            k++;
        pi[i] = k;
    }
    return pi;
}

void KMP(char *text, char *pattern)
{
    int m = strlen(text), n = strlen(pattern);
    int *pi = (int *)malloc(n * sizeof(int));
    printf("Enterned KMP\n");
    pi = computePrefix(pattern, pi);
    int k = 0, flag = 0;
    for (int i = 0; i < m; i++)
    {
        while (k > 0 && pattern[k] != text[i])
        {
            k = pi[k - 1];
        }
        if (pattern[k] == text[i])
            k++;
        if (k == n)
        {
            flag++;
            printf("The pattern %s is found at index %d of the text\n", pattern, i - n + 1);
            k = pi[k - 1];
        }
    }
    if (flag == 0)
    {
        printf("Pattern not Found\n");
    }
}

int main()
{
    char text[MAX], pattern[MAX];
    printf("Enter Text\n");
    scanf("%s", &text);
    printf("Enter Pattern\n");
    scanf("%s", &pattern);

    KMP(text, pattern);
    return 0;
}