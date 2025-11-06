#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int val;
	struct Node *next, *prev;
}Node;


Node* create(int*x, int n){
	Node* head = (Node*)malloc(sizeof(Node));
	head->val = x[0];
	head->prev = NULL;
	head->next = NULL;
	Node * t = head;
	for(int i = 1;i<n;i++){
		Node* node = (Node*)malloc(sizeof(Node));
		node->val = x[i];
		node->next = NULL;
		node->prev = t;
		t->next = node;
		t = node;
	}
	return head;
}

void insertionsort(Node*l){
	Node * t = l->next;
	Node * j = NULL;
	while(t){
		j = t->prev;
		int key = t->val;
		//printf("%d\n",j->val);
		while(j && (j->val > key)){
			j->next->val = j->val;
			//printf("Hello");
			j = j->prev;
		}
		if(j){
			j->next->val = key; 
		} else {
			l->val = key;
		}
		t = t->next;
	}
}

Node *insertionMoveNodes(Node*l){
	Node * t = l->next;
	Node * j = NULL;
	while(t){
		Node * next = t->next; // Store next since t will move
		j = t->prev;
		if(t->prev)t->prev->next = t->next;
		if(t->next)t->next->prev = t->prev;
		while(j && j->val > t->val){
			j = j->prev;
		}
		if(j){
			t->next = j->next;
			if(j->next)j->next->prev = t;
			j->next = t;
			t->prev = j;
		} else {
			t->next = l;
			l->prev = t;
			t->prev = NULL;
			l = t;
		}
		t = next;
	}
	return l;
}

int main(){
	int A[6] = {100,4,50,10,9,15};
	Node * dlist = create(A,sizeof(A)/sizeof(int));
	Node * t = dlist;
	while(t){
		printf("%d\n",t->val);
		t = t->next;
	}
	dlist = insertionMoveNodes(dlist);
	t  = dlist;
	printf("Sorted Code\n");
	while(t){
		printf("%d\n",t->val);
		t = t->next;
	}
		
	return 0;

}
