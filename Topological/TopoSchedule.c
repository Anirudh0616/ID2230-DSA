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

void Schedule(Node* Graph, int n){
    int* indegree = calloc(n, sizeof(int));
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

    // Start Scheduler
    int level = 0;
    while(head < tail){
        int level_size = tail - head;
        printf("Level %d: ", level);

        for (int i = 0; i < level_size; i++){
            int node = queue[head++];
            printf(" %d", node);
            for (int next = 0; next < Graph[node].size ; next++){
                int neighbour = Graph[node].neighbours[next];
                indegree[neighbour]--;
                if (indegree[neighbour] == 0){
                    queue[tail++] = neighbour;
                }
            }
        }
        printf("\n");
        level++;
    }

    free(indegree);
    free(queue);
}


int main(void){
    int n = 6;

    Node* graph = initGraph(n);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 1);
    addEdge(graph, 5, 2);

    Schedule(graph, n);

    // Free some of that memory boy
    for (int i = 0; i < n; i++)
        free(graph[i].neighbours);
    free(graph);
    return 0;
}
