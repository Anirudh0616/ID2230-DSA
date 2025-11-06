#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Node{
	int val;
	struct Node* left;
	struct Node* right;
}Node;

Node* insert(Node*root,int val){
	if(!root){
		Node* new = (Node*)malloc(sizeof(Node));
		new->val = val;
		new->left = NULL;
		new->right = NULL;
		return new;
	} 
	if(root->val < val){ root->right = insert(root->right,val); }
	if(root->val > val){ root->left= insert(root->left,val); }
	return root;
}

Node* search(Node*root,int target){
	if(!root || root->val == target){
		return root;
	}
	if(root->val < target){
		return search(root->right,target);
	} else {
		return search(root->left,target);
	}
}
Node* findMin(Node*root){
	while(root->left){
		root = root->left;
	}
	return root;
}

Node* delete(Node*root, int target){
	if(!root) return NULL;
	Node*temp = NULL;
	if(root->val < target){
		root->right = delete(root->right,target);
		return root;
	} 
	else if(root->val > target){
		root->left = delete(root->left, target);
		return root;
	}
	// Found that bi
	if(root->right == NULL && root->left==NULL ){
		free(root);
		return NULL;
	}
	if(root->right==NULL){
		temp = root->left;
		free(root);
		return temp;
	}
	if(root->left==NULL){
		temp = root->right;
		free(root);
		return temp;
	}
	temp = findMin(root->right);
	root->val = temp->val;
	root->right = delete(root->right,temp->val);
	return root;
}
void inorder(Node* root) {
    if(!root) return;
    inorder(root->left);
    printf("%d ", root->val);
    printf("\n");
    inorder(root->right);
}

int main(){
	int A[9] = {1,8,10,12,11,15,6,3,4};
	Node* root = NULL;
	for(int i = 0;i<9;i++){
		root = insert(root,A[i]);
	}
	printf("  %d \n",root->val);
	// printf("%d\n",root->left==NULL?1:0);
	// printf("%d\n",root->right==NULL?1:0);
	printf(" / \\ \n");
	printf("%d  %d\n",0,root->right->val);

	Node* x = search(root,11);
	if(x){
		printf("Found %d\n",x->val);
	} else {
		printf("Not Found\n");
	}
	root= delete(root,12);
	x = search(root,15);
	if(x){
		printf("Found %d\n",x->val);
	} else {
		printf("Not Found\n");
	}

	inorder(root);


	return 0;
}
