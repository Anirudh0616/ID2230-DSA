#include<stdio.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *createNode(int dat){
    
    struct Node *newNode = (struct Node*)
    malloc(sizeof(struct Node));
    newNode-> data = dat;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

int main(){
   
    struct Node* head = NULL;
    int n;
    scanf("%d",&n);
    
    struct Node* linked[n];
    
    int x;
    for(int i = 0;i<n;i++){
        scanf("%d",&x);
        struct Node *new = createNode(x);
        
        
    }

    return 0;
}
