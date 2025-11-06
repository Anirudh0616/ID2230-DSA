#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 1000

typedef struct Node{
	int val;
	struct Node* right;
	struct Node* left;
}Node;
	


Node* insert(Node*root, int val){
	Node* new = (Node*)malloc(sizeof(Node));
	new->val = val;
	new->right = NULL;
	new->left = NULL;
	if(!root) return new;
	if(root->val < val){
		root->right = insert(root->right,val);
	} else {
		root->left = insert(root->left,val);
	}
	return root;
}

Node* search(Node*root, int target){
	if(!root) return NULL;
	if(root->val == target) return root;
	if(root->val<target){
		return search(root->right,target);
	} else {
		return search(root->left,target);
	}
	return root;
}
Node* findMin(Node*root){
	while(root->left){
		root = root->left;
	}
	return root;
}

Node* delete(Node*root, int target){
	if(!root) return NULL;
	Node* temp = NULL;
	if(root->val < target){
		root->right = delete(root->right,target);
		return root;
	} else if(root->val > target){
		root->left = delete(root->left, target);
		return root;
	}
	else { 
		if(root->left == NULL && root->right == NULL){
			free(root);
			return NULL;
		}
		else if(root->left==NULL){
			temp = root->right;
			free(root);
			return temp;

		}
		else if(root->right==NULL){
			temp = root->left;
			free(root);
			return temp;
		}
		temp = findMin(root->right);
		root->val = temp->val;
		root->right = delete(root->right,target);
	}
	return root;
}

int height(Node*root){
	if(!root){
		return -1;
	}
	int leftH = height(root->left);
	int rightH = height(root->right);
	return 1 + (leftH>rightH ? leftH:rightH);
}

void inorder(Node*root){
	if(root){
		inorder(root->left);
		printf("%d ",root->val);
		inorder(root->right);
	}
}

void postorder(Node*root){
	if(root){
		postorder(root->left);
		postorder(root->right);
		printf("%d ",root->val);
	}
}
void preorder(Node*root){
	if(root){
		printf("%d ",root->val);
		preorder(root->left);
		preorder(root->right);
	}
}
void levelorder(Node*root){
	Node* q[MAX_SIZE];
	int head = 0, tail = 0;
	q[tail++] = root;
	while(head<tail){
		Node* curr = q[head++];
		printf("%d ",curr->val);
		if(curr->left){
			q[tail++] = curr->left;
		}
		if(curr->right){
			q[tail++] = curr->right;
		}
	}
}

int main(){
	int A[6] = {8,6,9,2,10,4};
	Node* root = NULL;
	for(int i = 0;i<6;i++){
		root = insert(root,A[i]);
	}
	
	printf("  %d\n",root->val);
	printf("%d   %d\n",root->left->val,root->right->val);

	for(int i = 0;i<6;i++){
		Node*x = search(root,A[i]);
		if(x){
			printf("%d is there in the tree\n",x->val);
		}else {
			printf("%d is not there in the tree\n",A[i]);
		}
	}
	inorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	levelorder(root);
	
	printf("\n");
	Node* garb = delete(root,6);

	for(int i = 0;i<6;i++){
		Node*x = search(root,A[i]);
		if(x){
			printf("%d is there in the tree!\n",x->val);
		}else {
			printf("%d is NOT there in the tree\n",A[i]);
		}
	}
	printf("Height is %d\n",height(root));

	inorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	levelorder(root);

	return 0;
}
