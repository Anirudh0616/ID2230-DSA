#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* neighbours;
    int size;
    int capacity;
} Node;

Node* initGraph(int num){
    Node* Graph = malloc(num * sizeof(Node));
    for (int i = 0; i < num; i++){
        Graph[i].size = 0;
        Graph[i].capacity = 2;
        Graph[i].neighbours = malloc(Graph[i].capacity * sizeof(int));
    }
    return Graph;
}

void addEdge(Node* Graph, int from, int to){
    // Reallocate Memory if Capacity gets exceeded
    if (Graph[from].size == Graph[from].capacity){
        Graph[from].capacity *= 2;
        Graph[from].neighbours = realloc(Graph[from].neighbours, Graph[from].capacity * sizeof(int));
    }
    Graph[from].neighbours[Graph[from].size++] = to;
}

void dfs(int v, Node* Graph, int* visited, int* stack, int* stackIndex){
    visited[v] = 1;
    for(int i = 0; i < Graph[v].size; i++){
        int neighbour = Graph[v].neighbours[i];
        if(!visited[neighbour]){
            dfs(neighbour, Graph, visited, stack, stackIndex);
        }
    }
    stack[(*stackIndex)++] = v;
    return;
}

// Topological Sorting yahhhh
int* topoSort(Node* Graph, int n){
    int* visited = calloc(n, sizeof(int));
    int* stack = malloc(n * sizeof(int));
    int stackIndex = 0;
    // Start DFS
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, Graph, visited, stack, &stackIndex);
    // Pop Elements from DFS
    int* order = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        order[i] = stack[n - i - 1];
    // Freedommmmmm
    free(stack);
    free(visited);
    return order;
}


int main(void){
    int n = 6; // Number of Nodes in Graph

    // Create Graph and edging :)
    Node* graph = initGraph(n);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    // Sorting
    int* order = topoSort(graph, n);
    printf("Topological Sort: ");
    for (int i = 0; i<n; i++){
        printf("%d ", order[i]);
    }printf("\n");

    // Free some of that memory boy
    free(order);
    for (int i = 0; i < n; i++)
        free(graph[i].neighbours);
    free(graph);
    return 0;
}
