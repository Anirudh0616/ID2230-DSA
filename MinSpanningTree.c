#include <stdio.h>
#include <stdlib.h>

int comparator(const void* p1, const void* p2){
    return ((const int*)p1)[2] - ((const int*)p2)[2];
}

void makeSet(int parent[], int n){
    for (int i = 0; i < n; i++){
        parent[i] = i;
    }
}

int findParent(int parent[], int component){
    if (parent[component] == component){
        return component;
    }
    // This is just insane, it sends it directly to the root
    // After one iter it's parent array value is now set to the root
    // So the next time it's called it goes straight to root
    // and then the above if statement gets activated
    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int n){
    int uRoot = findParent(parent, u);
    int vRoot = findParent(parent, v);

    parent[uRoot] = vRoot;
}

int kruskalAlgo(int n, int edge[n][3]){
   qsort(edge, n, sizeof(edge[0]), comparator);

    int parent[n];
    makeSet(parent, n);

    int minCost = 0;
    for(int i = 0; i < n; i++){
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        if(v1 != v2){
            unionSet(v1, v2, parent, n);
            minCost += wt;
            printf("%d -- %d (weight %d)\n", 
                    edge[i][0], edge[i][1], edge[i][2]);
        }
    }
    return minCost;
}

int main(void){
    int edge[5][3] = { { 0, 1, 10 },
                       { 0, 2, 6 },
                       { 0, 3, 5 },
                       { 1, 3, 15 },
                       { 2, 3, 4 } };
    printf("MST Edges: \n");
    printf("Total Weight: %d\n",kruskalAlgo(5, edge));

    return 0;
}
