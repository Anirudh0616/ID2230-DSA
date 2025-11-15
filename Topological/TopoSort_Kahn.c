#include <stdio.h>
#include <stdlib.h>

typedef struct{
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
    if (Graph[from].size == Graph[from].capacity){
        Graph[from].capacity *= 2;
        Graph[from].neighbours = realloc(Graph[from].neighbours, Graph[from].capacity * sizeof(int));
    }
    Graph[from].neighbours[Graph[from].size++] = to;
}

int* topoSortKahn(Node* Graph, int n){
    int* indegree = calloc(n, sizeof(int));
    // result index
    int* res = malloc(n * sizeof(int));
    int res_idx = 0;
    // Initialize Queue
    int* queue = malloc(n * sizeof(int));
    int head = 0;
    int tail = 0;

    // Compute Indegrees
    for (int node = 0; node < n; node++){
        for(int next = 0; next < Graph[node].size ; next++){
            indegree[Graph[node].neighbours[next]]++;
        }
    }
    // Add indegree 0 queue
    for (int node = 0; node < n; node++){
        if (indegree[node] == 0){
            queue[tail++] = node;
        }
    }

    // Kahn's Algo
    while(head != tail){
        int node = queue[head++];
        res[res_idx++] = node;
        for (int next = 0; next < Graph[node].size ; next++){
            int neighbour = Graph[node].neighbours[next];
            indegree[neighbour]--;
            if (indegree[neighbour] == 0){
                queue[tail++] = neighbour;
            }
        }
    }

    return res;
}


int main(void){
    int n = 9;

    Node* graph = initGraph(n);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 6);
    addEdge(graph, 0, 7);
    addEdge(graph, 0, 8);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 1);
    addEdge(graph, 5, 2);

    int* order = topoSortKahn(graph, n);
    printf("Topological Sort: ");
    for (int i = 0; i<n; i++){
        printf("%d ", order[i]);
    }printf("\n");

    // Free some of that memory boy
    for (int i = 0; i < n; i++)
        free(graph[i].neighbours);
    free(graph);
    return 0;
}
