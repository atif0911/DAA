#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 100000000

int vertices;
int pred[MAX][MAX];
int dist[MAX][MAX];

void printPath(int u, int v)
{
    if (u == v)
    {
        printf("%d", u);
    }
    else if (pred[u][v] == -1)
    {
        printf("No path exist between %d and %d\n", u, v);
    }
    else
    {
        printPath(u, pred[u][v]);
        printf("->%d", v);
    }
}

void printPred()
{
    int i, j;
    printf("Predecessor Matrix\n");

    for (i = 0; i < vertices; i++)
    {
        for (j = 0; j < vertices; j++)
        {
            if (pred[i][j] == -1)
                printf("nill\t");
            else
                printf("%d\t", pred[i][j]);
        }
        printf("\n");
    }
}

void printDist()
{
    int i, j;
    printf("Distance Matrix\n");
    for (i = 0; i < vertices; i++)
    {
        for (j = 0; j < vertices; j++)
        {
            printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall()
{
    int i, j, k;
    for (k = 0; k < vertices; k++)
    {
        for (i = 0; i < vertices; i++)
        {
            for (j = 0; j < vertices; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }
}

int main()
{
    FILE *file = fopen("graph.txt", "r");
    if (!file)
    {
        printf("ERROR IN OPENING THE FILE\n");
        exit(0);
    }

    fscanf(file, "%d", &vertices);

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
            pred[i][j] = -1;
        }
    }

    int ver, numEdge;
    for (int i = 0; i < vertices; i++)
    {
        fscanf(file, "%d %d", &ver, &numEdge);
        for (int j = 0; j < numEdge; j++)
        {
            int to, weight;
            fscanf(file, "%d %d", &to, &weight);
            dist[ver][to] = weight;
            pred[ver][to] = ver;
        }
    }

    floydWarshall();
    printDist();
    printPred();

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            printf("Path from %d to %d\n", i, j);
            if (pred[i][j] == -1)
                printf("No Path Exist\n");
            else
            {
                printf("Cost for Travelling :%d\n", dist[i][j]);
                printPath(i, j);
                printf("\n");
            }
        }
    }

    return 0;
}