// #include <stdio.h>
// #include <stdlib.h>
// #include <limits.h>

// #define MAX_VERTICES 100
// #define INF INT_MAX

// int numVertices; // Global variable to store the number of vertices

// typedef struct
// {
//     int vertex;
//     int weight;
// } Edge;

// typedef struct
// {
//     Edge **edges;
//     int *size;
//     int numVertices;
// } Graph;

// typedef struct
// {
//     int vertex;
//     int key;
// } HeapNode;

// typedef struct
// {
//     HeapNode **array;
//     int size;
//     int capacity;
// } MinHeap;

// Graph *createGraph(int numVertices);
// void addEdge(Graph *graph, int src, int dest, int weight);
// MinHeap *createMinHeap(int capacity);
// void swapHeapNodes(HeapNode **a, HeapNode **b);
// void minHeapify(MinHeap *minHeap, int idx);
// HeapNode *extractMin(MinHeap *minHeap);
// void decreaseKey(MinHeap *minHeap, int vertex, int key);
// int isInMinHeap(MinHeap *minHeap, int vertex);
// void printArr(int dist[], int n);
// void dijkstra(Graph *graph, int src);
// void primMST(Graph *graph, int src);
// void readGraphFromFile(Graph **graph, const char *filename); // Updated to pass Graph**
// void printGraph(Graph *graph);                               // Debug function
// void freeGraph(Graph *graph);
// void freeMinHeap(MinHeap *minHeap);

// Graph *createGraph(int numVertices)
// {
//     Graph *graph = (Graph *)malloc(sizeof(Graph));
//     graph->numVertices = numVertices;
//     graph->edges = (Edge **)malloc(numVertices * sizeof(Edge *));
//     graph->size = (int *)calloc(numVertices, sizeof(int));

//     for (int i = 0; i < numVertices; i++)
//     {
//         graph->edges[i] = NULL;
//     }
//     return graph;
// }
// void addEdge(Graph *graph, int src, int dest, int weight)
// {
//     graph->edges[src] = (Edge *)realloc(graph->edges[src], (graph->size[src] + 1) * sizeof(Edge));
//     graph->edges[src][graph->size[src]].vertex = dest;
//     graph->edges[src][graph->size[src]].weight = weight;
//     graph->size[src]++;
// }
// MinHeap *createMinHeap(int capacity)
// {
//     MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
//     minHeap->array = (HeapNode **)malloc(capacity * sizeof(HeapNode *));
//     minHeap->size = 0;
//     minHeap->capacity = capacity;
//     return minHeap;
// }
// void swapHeapNodes(HeapNode **a, HeapNode **b)
// {
//     HeapNode *t = *a;
//     *a = *b;
//     *b = t;
// }
// void minHeapify(MinHeap *minHeap, int idx)
// {
//     int smallest = idx;
//     int left = 2 * idx + 1;
//     int right = 2 * idx + 2;

//     if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
//         smallest = left;

//     if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
//         smallest = right;

//     if (smallest != idx)
//     {
//         swapHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
//         minHeapify(minHeap, smallest);
//     }
// }
// HeapNode *extractMin(MinHeap *minHeap)
// {
//     if (minHeap->size == 0)
//         return NULL;

//     HeapNode *root = minHeap->array[0];
//     HeapNode *lastNode = minHeap->array[minHeap->size - 1];
//     minHeap->array[0] = lastNode;
//     minHeap->size--;
//     minHeapify(minHeap, 0);

//     return root;
// }
// void decreaseKey(MinHeap *minHeap, int vertex, int key)
// {
//     int i;
//     for (i = 0; i < minHeap->size; i++)
//     {
//         if (minHeap->array[i]->vertex == vertex)
//         {
//             minHeap->array[i]->key = key;
//             break;
//         }
//     }

//     while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key)
//     {
//         swapHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
//         i = (i - 1) / 2;
//     }
// }
// int isInMinHeap(MinHeap *minHeap, int vertex)
// {
//     for (int i = 0; i < minHeap->size; i++)
//     {
//         if (minHeap->array[i]->vertex == vertex)
//             return 1;
//     }
//     return 0;
// }
// void printArr(int dist[], int n)
// {
//     printf("Vertex   Distance from Source\n");
//     for (int i = 0; i < n; ++i)
//         printf("%d \t\t %d\n", i, dist[i]);
// }
// void dijkstra(Graph *graph, int src)
// {
//     int V = graph->numVertices;
//     int dist[V];

//     MinHeap *minHeap = createMinHeap(V);

//     for (int v = 0; v < V; ++v)
//     {
//         dist[v] = INF;
//         minHeap->array[v] = (HeapNode *)malloc(sizeof(HeapNode));
//         if (!minHeap->array[v])
//         {
//             perror("Failed to allocate memory for heap node");
//             exit(EXIT_FAILURE);
//         }
//         minHeap->array[v]->vertex = v;
//         minHeap->array[v]->key = dist[v];
//         minHeap->size++;
//     }

//     dist[src] = 0;
//     decreaseKey(minHeap, src, dist[src]);

//     while (minHeap->size != 0)
//     {
//         HeapNode *minHeapNode = extractMin(minHeap);
//         int u = minHeapNode->vertex;

//         for (int i = 0; i < graph->size[u]; i++)
//         {
//             int v = graph->edges[u][i].vertex;
//             int weight = graph->edges[u][i].weight;

//             if (isInMinHeap(minHeap, v) && dist[u] != INF && dist[u] + weight < dist[v])
//             {
//                 dist[v] = dist[u] + weight;
//                 decreaseKey(minHeap, v, dist[v]);
//             }
//         }
//         free(minHeapNode); // Free the extracted node
//     }
//     printArr(dist, V);
//     freeMinHeap(minHeap);
// }
// void primMST(Graph *graph, int src)
// {
//     int V = graph->numVertices;
//     int parent[V];
//     int key[V];

//     MinHeap *minHeap = createMinHeap(V);

//     for (int v = 0; v < V; ++v)
//     {
//         parent[v] = -1;
//         key[v] = INF;
//         minHeap->array[v] = (HeapNode *)malloc(sizeof(HeapNode));
//         if (!minHeap->array[v])
//         {
//             perror("Failed to allocate memory for heap node");
//             exit(EXIT_FAILURE);
//         }
//         minHeap->array[v]->vertex = v;
//         minHeap->array[v]->key = key[v];
//         minHeap->size++;
//     }

//     key[src] = 0; // Start from the specified source vertex
//     decreaseKey(minHeap, src, key[src]);

//     while (minHeap->size != 0)
//     {
//         HeapNode *minHeapNode = extractMin(minHeap);
//         int u = minHeapNode->vertex;

//         for (int i = 0; i < graph->size[u]; i++)
//         {
//             int v = graph->edges[u][i].vertex;
//             int weight = graph->edges[u][i].weight;

//             if (isInMinHeap(minHeap, v) && weight < key[v])
//             {
//                 key[v] = weight;
//                 parent[v] = u;
//                 decreaseKey(minHeap, v, key[v]);
//             }
//         }
//         free(minHeapNode); // Free the extracted node
//     }

//     printf("Edge   Weight\n");
//     for (int i = 0; i < V; ++i)
//     {
//         if (parent[i] != -1)
//             printf("%d - %d    %d \n", parent[i], i, key[i]);
//     }

//     freeMinHeap(minHeap);
// }
// void readGraphFromFile(Graph **graph, const char *filename)
// {
//     FILE *file = fopen(filename, "r");
//     if (!file)
//     {
//         printf("Unable to open file");
//         exit(0);
//     }

//     fscanf(file, "%d", &numVertices);
//     *graph = createGraph(numVertices);

//     for (int i = 0; i < numVertices; i++)
//     {
//         int vertex, numEdges;
//         fscanf(file, "%d %d", &vertex, &numEdges);

//         for (int j = 0; j < numEdges; j++)
//         {
//             int dest, weight;
//             fscanf(file, "%d %d", &dest, &weight);
//             addEdge(*graph, vertex, dest, weight);
//         }
//     }
//     fclose(file);
//     printf("Finished reading graph.\n");
// }
// void printGraph(Graph *graph)
// {
//     printf("Graph adjacency list:\n");
//     for (int i = 0; i < graph->numVertices; i++)
//     {
//         printf("Vertex %d: ", i);
//         for (int j = 0; j < graph->size[i]; j++)
//         {
//             printf("(%d, %d) ", graph->edges[i][j].vertex, graph->edges[i][j].weight);
//         }
//         printf("\n");
//     }
// }
// void freeGraph(Graph *graph)
// {
//     for (int i = 0; i < graph->numVertices; i++)
//     {
//         free(graph->edges[i]);
//     }
//     free(graph->edges);
//     free(graph->size);
//     free(graph);
// }
// void freeMinHeap(MinHeap *minHeap)
// {
//     for (int i = 0; i < minHeap->size; i++)
//     {
//         free(minHeap->array[i]);
//     }
//     free(minHeap);
// }
// int main()
// {
//     Graph *graph = NULL;
//     readGraphFromFile(&graph, "graph.txt");
//     printGraph(graph);

//     int choice, src;
//     printf("1. Prim's Algorithm\n2. Dijkstra's Algorithm\nEnter your choice: ");
//     scanf("%d", &choice);

//     printf("Enter the source vertex: ");
//     scanf("%d", &src);

//     if (src < 0 || src >= numVertices)
//     {
//         printf("Invalid source vertex.\n");
//     }
//     else
//     {
//         if (choice == 1)
//         {
//             primMST(graph, src);
//         }
//         else if (choice == 2)
//         {
//             dijkstra(graph, src);
//         }
//         else
//         {
//             printf("Invalid choice\n");
//         }
//     }
//     freeGraph(graph);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

int numVertices; // Global variable to store the number of vertices

typedef struct
{
    int vertex;
    int weight;
} Edge;
typedef struct
{
    Edge **edges;
    int *size;
    int numVertices;
} Graph;
typedef struct
{
    int vertex;
    int key;
} HeapNode;
typedef struct
{
    HeapNode **array;
    int size;
    int capacity;
} MinHeap;
Graph *createGraph(int numVertices);
void addEdge(Graph *graph, int src, int dest, int weight);
MinHeap *createMinHeap(int capacity);
void swapHeapNodes(HeapNode **a, HeapNode **b);
void minHeapify(MinHeap *minHeap, int idx);
HeapNode *extractMin(MinHeap *minHeap);
void decreaseKey(MinHeap *minHeap, int vertex, int key);
int isInMinHeap(MinHeap *minHeap, int vertex);
void printArr(int dist[], int n);
void dijkstra(Graph *graph, int src);
void primMST(Graph *graph, int src);
void readGraphFromFile(Graph **graph, const char *filename); // Updated to pass Graph**
void printGraph(Graph *graph);                               // Debug function
void freeGraph(Graph *graph);
void freeMinHeap(MinHeap *minHeap);

Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->edges = (Edge **)malloc(numVertices * sizeof(Edge *));
    graph->size = (int *)calloc(numVertices, sizeof(int));

    for (int i = 0; i < numVertices; i++)
    {
        graph->edges[i] = NULL;
    }
    return graph;
}
void addEdge(Graph *graph, int src, int dest, int weight)
{
    if (src < 0 || src >= graph->numVertices ||
        dest < 0 || dest >= graph->numVertices ||
        weight < 0)
    {
        printf("Invalid edge: %d %d %d\n", src, dest, weight);
        return; // or exit()
    }
    graph->edges[src] = (Edge *)realloc(graph->edges[src], (graph->size[src] + 1) * sizeof(Edge));
    graph->edges[src][graph->size[src]].vertex = dest;
    graph->edges[src][graph->size[src]].weight = weight;
    graph->size[src]++;
}
MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->array = (HeapNode **)malloc(capacity * sizeof(HeapNode *));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}
void swapHeapNodes(HeapNode **a, HeapNode **b)
{
    HeapNode *t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;
    if (smallest != idx)
    {
        swapHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
HeapNode *extractMin(MinHeap *minHeap)
{
    if (minHeap->size == 0)
        return NULL;
    HeapNode *root = minHeap->array[0];
    HeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->size--;
    minHeapify(minHeap, 0);
    return root;
}
void decreaseKey(MinHeap *minHeap, int vertex, int key)
{
    int i;
    for (i = 0; i < minHeap->size; i++)
    {
        if (minHeap->array[i]->vertex == vertex)
        {
            minHeap->array[i]->key = key;
            break;
        }
    }
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key)
    {
        swapHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int isInMinHeap(MinHeap *minHeap, int vertex)
{
    for (int i = 0; i < minHeap->size; i++)
    {
        if (minHeap->array[i]->vertex == vertex)
            return 1;
    }
    return 0;
}
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
void dijkstra(Graph *graph, int src)
{
    int V = graph->numVertices;
    int *dist = malloc(V * sizeof(int));
    if (!dist)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    MinHeap *minHeap = createMinHeap(V);
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INF;
        minHeap->array[v] = (HeapNode *)malloc(sizeof(HeapNode));
        if (!minHeap->array[v])
        {
            perror("Failed to allocate memory for heap node");
            exit(EXIT_FAILURE);
        }
        minHeap->array[v]->vertex = v;
        minHeap->array[v]->key = dist[v];
        minHeap->size++;
    }
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    while (minHeap->size != 0)
    {
        HeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        for (int i = 0; i < graph->size[u]; i++)
        {
            int v = graph->edges[u][i].vertex;
            int weight = graph->edges[u][i].weight;

            if (isInMinHeap(minHeap, v) && dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                decreaseKey(minHeap, v, dist[v]);
            }
        }
        free(minHeapNode); // Free the extracted node
    }
    printArr(dist, V);
    freeMinHeap(minHeap);
    free(dist);
}
void primMST(Graph *graph, int src)
{
    int V = graph->numVertices;
    int *parent = malloc(V * sizeof(int));
    int *key = malloc(V * sizeof(int));
    if (!parent || !key)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    MinHeap *minHeap = createMinHeap(V);
    for (int v = 0; v < V; ++v)
    {
        parent[v] = -1;
        key[v] = INF;
        minHeap->array[v] = (HeapNode *)malloc(sizeof(HeapNode));
        if (!minHeap->array[v])
        {
            perror("Failed to allocate memory for heap node");
            exit(EXIT_FAILURE);
        }
        minHeap->array[v]->vertex = v;
        minHeap->array[v]->key = key[v];
        minHeap->size++;
    }
    key[src] = 0; // Start from the specified source vertex
    decreaseKey(minHeap, src, key[src]);
    while (minHeap->size != 0)
    {
        HeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        for (int i = 0; i < graph->size[u]; i++)
        {
            int v = graph->edges[u][i].vertex;
            int weight = graph->edges[u][i].weight;
            if (isInMinHeap(minHeap, v) && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
        }
        free(minHeapNode); // Free the extracted node
    }
    printf("Edge   Weight\n");
    for (int i = 0; i < V; ++i)
    {
        if (parent[i] != -1)
            printf("%d - %d    %d \n", parent[i], i, key[i]);
    }
    freeMinHeap(minHeap);
    free(parent);
    free(key);
}
void readGraphFromFile(Graph **graph, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Unable to open file");
        exit(0);
    }
    fscanf(file, "%d", &numVertices);
    if (numVertices <= 0 || numVertices > MAX_VERTICES)
    {
        printf("Invalid number of vertices: %d\n", numVertices);
        exit(EXIT_FAILURE);
    }
    *graph = createGraph(numVertices);
    for (int i = 0; i < numVertices; i++)
    {
        int vertex, numEdges;
        fscanf(file, "%d %d", &vertex, &numEdges);

        for (int j = 0; j < numEdges; j++)
        {
            int dest, weight;
            fscanf(file, "%d %d", &dest, &weight);
            addEdge(*graph, vertex, dest, weight);
        }
    }
    fclose(file);
    printf("Finished reading graph.\n");
}
void printGraph(Graph *graph)
{
    printf("Graph adjacency list:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("Vertex %d: ", i);
        for (int j = 0; j < graph->size[i]; j++)
        {
            printf("(%d, %d) ", graph->edges[i][j].vertex, graph->edges[i][j].weight);
        }
        printf("\n");
    }
}
void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        free(graph->edges[i]);
    }
    free(graph->edges);
    free(graph->size);
    free(graph);
}
void freeMinHeap(MinHeap *minHeap)
{
    for (int i = 0; i < minHeap->size; i++)
    {
        free(minHeap->array[i]);
    }
    free(minHeap);
}
int main()
{
    Graph *graph = NULL;
    readGraphFromFile(&graph, "graph.txt");
    printGraph(graph);
    int choice, src;
    printf("1. Prim's Algorithm\n2. Dijkstra's Algorithm\nEnter your choice: ");
    scanf("%d", &choice);
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    if (src < 0 || src >= numVertices)
    {
        printf("Invalid source vertex.\n");
    }
    else
    {
        if (choice == 1)
        {
            primMST(graph, src);
        }
        else if (choice == 2)
        {
            dijkstra(graph, src);
        }
        else
        {
            printf("Invalid choice\n");
        }
    }
    freeGraph(graph);
    return 0;
}
