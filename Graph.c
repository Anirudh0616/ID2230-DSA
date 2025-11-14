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
        Graph[i].capacity = 100;
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


int main(void){
    int n = 6; // Number of Nodes in Graph

    // Create Graph and edging :)
    Node* graph = initGraph(n);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 5);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);
    addEdge(graph, 4, 1);
    addEdge(graph, 4, 3);
    printf("Hello There :)\n");

    for(int i = 0;i<n;i++){
        for(int j =0;j<n;j++){
            printf("i = %d,j = %d ||| %d\n",i,j,graph[i].neighbours[j]);
        }
    }


    // Free some of that memory boy
    for (int i = 0; i < n; i++)
        free(graph[i].neighbours);
    free(graph);
    return 0;
}
