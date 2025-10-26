#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node* left;
  struct Node* right;
};



int getHeight(struct Node* root, int h)
{
  if (root == NULL){
    return h-1;
  }
  int leftHeight = getHeight(root->left, h+1);
  int rightHeight = getHeight(root->right, h+1);
  return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

int getBalance(struct Node* root)
{
  return getHeight(root->left, 0) - getHeight(root->right, 0);
}

struct Node* leftRotate(struct Node* x){
  struct Node* y = x->right;
  struct Node* T2 = y->left;

  // Perform Rotation ( Right side was heavy )
  x->right = T2;
  y->left = x;

  return y;
}

struct Node* rightRotate(struct Node* y){
  struct Node* x = y->left;
  struct Node* T2 = x->right;

  // Perform Rotation
  x->right = y;
  y->left = T2;

  return x;
}

struct Node* Balance(struct Node* node)
{
  if (node == NULL) return NULL;
  int b_factor = getBalance(node);

  if (b_factor > 1) // Left side is heavier gotta right rotate
  {
    if (getBalance(node->left) < 0) // Left node is right heavy also kinda
      node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (b_factor < -1) // Right side is heavier gotta left rotate
  {
    if (getBalance(node->right) > 0) // Right node is left heavy also kinda
      node->left = rightRotate(node->left);
    return leftRotate(node);
  }
  return node;
}

struct Node* insert_bst(struct Node* root, int x){
  if (root == NULL){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = x;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
  }

  if (root->data > x){
    root->left = insert_bst(root->left, x);
  }
  else if (root->data < x){
    root->right = insert_bst(root->right, x);
  }
  return Balance(root);
}

// Helper: Print nodes at a specific level
void printLevel(struct Node* root, int level) {
    if (root == NULL) return;
    if (level == 0) {
        printf("%d ", root->data);
    } else if (level > 0) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Level order traversal without external queues
void levelOrder(struct Node* root) {
    if (root == NULL) {
        printf("Empty tree\n");
        return;
    }
    int h = getHeight(root, 0);
    for (int i = 0; i <= h; i++) {
        printLevel(root, i);
        printf("\n");  // New line after each level
    }
}

// Find successor in right subtree ( NOT OVERALL Successor )
struct Node* successor(struct Node* curr)
{
  curr = curr->right;
  while(curr != NULL && curr->left != NULL){
    curr = curr->left;
  }
  return curr;
}

struct Node* delete_BST(struct Node* root, int x)
{
  if (root == NULL) return root;
  // Traverse till if you find the data
  if (root->data > x){
    root->left = delete_BST(root->left, x);
  }
  else if(root->data < x){
    root->right = delete_BST(root->right,x);
  }
  else{
    // Now 2 different things can happen, node has empty child or not
    // if one child is gone, we can do direct shifting
    if (root->left == NULL){
      struct Node* temp = root->right;
      free(root);
      return Balance(temp);
    }
    if (root->right == NULL){
      struct Node* temp = root->left;
      free(root);
      return Balance(temp);
    }
    // Kill the key by replacing it with the succ, and then go kill the lonely ahh succ
    struct Node* succ = successor(root);
    root->data = succ->data;
    root->right = delete_BST(root->right, succ->data);
  }
  return Balance(root);
}

// Preorder Traversal
void preorder(struct Node* root)
{
  if (root == NULL) return;
  printf("%d ", root->data);
  preorder(root->left);
  preorder(root->right);
  return;
}

int main()
{
  printf("------------\n AVL \n--------------\n");
  struct Node* root = NULL;
  int values[8] = {3, 4, 7, 0, 5, 2, 9, 8};
  for(int i = 0; i<8; i++){
    root = insert_bst(root, values[i]);
    printf("Printing Preorder: ");
    preorder(root);
    printf("\n");
  }
  printf("Level Order: \n");
  levelOrder(root);
  printf("\n");
  printf("Deleteing 7. \nPrinting Preorder: ");
  root = delete_BST(root, 7);
  preorder(root);
  printf("\n");
  printf("Deleteing 3. \nPrinting Preorder: ");
  root = delete_BST(root, 3);
  preorder(root);
  printf("\n");
  printf("Level Order: \n");
  levelOrder(root);
  printf("\n");
  return 0;
}
