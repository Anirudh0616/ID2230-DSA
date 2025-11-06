#include<stdio.h>
#include<stdlib.h>

int max(int a, int b){
	return a > b ? a : b;
}

typedef struct avlNode{
	int val;
	struct avlNode *left;
	struct avlNode *right;
	int height;
}avlNode;

avlNode* search(avlNode* root, int target){
	if(!root) return NULL;
	if(root->val == target) return root;
	if(root->val < target) return search(root->right,target);
	else return search(root->left,target);
}
int getHeight(avlNode *root){
	if(!root) return 0;
	return root->height;
}

avlNode* leftR(avlNode* root){
	avlNode* B = root->right;
	avlNode* y = B->left;

	B->left= root;
	root->right = y;

	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	B->height = 1 + max(getHeight(B->left), getHeight(B->right));

	return B;
}

avlNode* rightR(avlNode* root){
	avlNode* B = root->left;
	avlNode* y = B->right;

	B->right= root;
	root->left = y;

	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	B->height = 1 + max(getHeight(B->left), getHeight(B->right));

	return B;
}

int balanceFactor(avlNode*root){
	if(!root) return 0;
	return (getHeight(root->left)) - getHeight(root->right);
}


avlNode* insert(avlNode*root, int val){
	avlNode * node = (avlNode*)malloc(sizeof(avlNode));
	node->val = val;
	node->right = NULL;
	node->left= NULL;
	node->height = 1;
	if(!root) return node;
	if(root->val < val){
		root->right = insert(root->right, val);
	} else {
		root->left = insert(root->left,val);
	}
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));

	int bf = balanceFactor(root);

	if(bf>1 && val<root->left->val){
		root = rightR(root);
		return root;
	}
	if(bf < -1 && val>root->right->val){
		root = leftR(root);
		return root;
	}
	if(bf>1 && val>root->left->val){
		root->left = leftR(root->left);
		root = rightR(root);
		return root;
	}
	if(bf < -1 && val < root->right->val){
		root->right= rightR(root->right);
		root = leftR(root);
		return root;
	}
	return root;
}

avlNode* minval(avlNode*root){
	while(root->left){
		root = root->left;
	}
	return root;
}



avlNode* delete(avlNode*root, int target){
	avlNode* temp = NULL;
	if(!root) return root;
	if(target<root->val){
		root->left = delete(root->left,target);
	}
	else if(target>root->val){
		root->right = delete(root->right,target);
	} else {
		if(root->left==NULL && root->right == NULL){
			free(root);
			return NULL;
		}
		if(root->left==NULL){
			temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right==NULL){
			temp = root->left;
			free(root);
			return temp;
		} else {
			temp = minval(root->right);
			root->val = temp->val;
			root->right = delete(root->right,temp->val);
		}
	}
	if (!root) return NULL; // double guard
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	int bf = balanceFactor(root);
	
	if(bf>1 && (root->left)>=0){
		root = rightR(root);
		return root;
	}
	if(bf>1 && balanceFactor(root->left)<0){
		root->left = leftR(root->left);
		root = rightR(root);
		return root;
	}
	if(bf< -1 && balanceFactor(root->right)<=0){
		root = leftR(root);
		return root;
	}
	if(bf< -1 && balanceFactor(root->right)>0){
		root->right = rightR(root->right);
		root = leftR(root);
		return root;
	}
	return root;

}

void levelorder(avlNode*root){
	if(!root) return;
	avlNode* q[1000];
	int head = 0, tail =0;
	q[tail++] = root;
	while(head<tail && root){
		avlNode * curr = q[head++];
		printf("%d(%d,%d) ",curr->val,curr->height,balanceFactor(curr));
		if(curr->left){
			q[tail++] = curr->left;
		}	
		if(curr->right){
			q[tail++] = curr->right;
		}

	}
}


int main(){
	int A[9] = {5,9,14,13,11,12,3,1,4};
	avlNode *root = NULL;

	printf("inserted\n");
	for(int i = 0;i<9;i++){
		root = insert(root,A[i]);
		// if(A[i]==12){
		// 	levelorder(root);
		// }
	}
	
	// printf("\n");
	levelorder(root);
	printf("\n");
	root = delete(root,11);
	levelorder(root);
	printf("\n");
	
	return 0;
}
