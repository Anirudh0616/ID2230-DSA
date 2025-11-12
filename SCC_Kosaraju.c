#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void dfs(Node* Graph, int start, int* visited, int* stack, int* top){
    visited[start] = 1;
    for(int i = 0; i < Graph[start].size; i++){
        int neigh = Graph[start].neighbours[i];
        if(!visited[neigh]){
            dfs(Graph, neigh, visited, stack, top);
        }
    }
    stack[(*top)++] = start;
}

void rev_dfs(Node* RevGraph, int start, int* visited){
    visited[start] = 1;
    printf(" %d", start);

    for(int i = 0; i < RevGraph[start].size; i++){
        int neigh = RevGraph[start].neighbours[i];
        if(!visited[neigh]){
            rev_dfs(RevGraph, neigh, visited);
        }
    }
}

// Kosaraju's Algorithm for findgin Strongly Connected Comp.
void printSCC(Node* Graph, int n){
    int* visited = calloc(n, sizeof(int));
    int* stack = malloc(n * sizeof(int));
    int stack_top = 0;

    // Fill Stack
    for (int i = 0; i < n; i++){
        if(!visited[i]){
            dfs(Graph, i, visited, stack, &stack_top);
        }
    }

    // Reverse Graph
    Node* rev_graph = initGraph(n);
    for(int i = 0; i < n; i++){
        for(int neigh = 0; neigh < Graph[i].size; neigh++){
            int rev_node = Graph[i].neighbours[neigh];
            addEdge(rev_graph, rev_node, i);
        }
    }

    // DFS in reverse
    memset(visited, 0, n * sizeof(int));

    while(stack[0] != -1){
        int rev_node = stack[stack_top];
        stack[stack_top--] = -1;
        if(!visited[rev_node]){
            printf("SCC: ");
            rev_dfs(rev_graph, rev_node, visited);
            printf("\n");
        }
    }
}


int main(void){
    int n = 6; // Number of Nodes in Graph

    // Create Graph and edging :)
    Node* graph = initGraph(n);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 3);

    printSCC(graph, n);
    // Free some of that memory boy
    for (int i = 0; i < n; i++)
        free(graph[i].neighbours);
    free(graph);
    return 0;
}
