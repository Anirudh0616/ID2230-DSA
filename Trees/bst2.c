#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *right;
  struct Node *left;
} Node;

Node *insert(Node *root, int val) {
  Node *new = (Node *)malloc(sizeof(Node));
  new->val = val;
  new->left = NULL;
  new->right = NULL;
  if (!root) {
    return new;
  }
  if (root->val < val) {
    root->right = insert(root->right, val);
  }
  if (root->val > val) {
    root->left = insert(root->left, val);
  }
  return root;
}

Node *search(Node *root, int target) {
  if (!root)
    return NULL;
  if (root->val == target)
    return root;
  if (root->val < target)
    return search(root->right, target);
  if (root->val > target)
    return search(root->left, target);
  return root;
}

Node *findMin(Node *root) {
  if (!root)
    return NULL;
  while (root->left) {
    root = root->left;
  }
  return root;
}

Node *delete(Node *root, int target) {
  if (!root)
    return NULL;
  Node *temp = NULL;
  if (root->val < target) {
    root->right = delete(root->right, target);
    return root;
  } else if (root->val > target) {
    root->left = delete(root->left, target);
    return root;
  }
  if (root->right == NULL && root->left == NULL) {
    free(root);
    return NULL;
  }
  if (root->right == NULL) {
    temp = root->left;
    free(root);
    return temp;
  }
  if (root->left == NULL) {
    temp = root->right;
    free(root);
    return temp;
  }
  temp = findMin(root->right);
  root->val = temp->val;
  root->right = delete(root->right, temp->val);
  return root;
}

void inorder(Node *root) {
  if (!root)
    return;
  inorder(root->left);
  printf("%d ", root->val);
  inorder(root->right);
}

void postorder(Node *root) {
  if (!root)
    return;
  postorder(root->left);
  postorder(root->right);
  printf("%d ", root->val);
}

void preorder(Node *root) {
  if (!root)
    return;
  printf("%d ", root->val);
  preorder(root->left);
  preorder(root->right);
}

void levelOrder(Node *root) {
  if (!root)
    return;
  Node* curr = NULL;
  Node *q[1000];
  int head = 0, tail = 0;
  q[tail++] = root;
  while (head < tail) {
    curr = q[head++];
    printf("%d ", curr->val);
    if (curr->left) {
      q[tail++] = curr->left;
    }
    if (curr->right) {
      q[tail++] = curr->right;
    }
  }
}


int main() {
  int A[9] = {9, 10, 4, 3, 6, 7, 8, 12, 11};
  Node *root = NULL;
  for (int i = 0; i < 9; i++) {
    root = insert(root, A[i]);
  }


  inorder(root);
  printf("\n");
  postorder(root);
  printf("\n");
  preorder(root);
  printf("\n");
  levelOrder(root);
  printf("\n");

  Node *x = search(root, 6);
  if (x)
    printf("Found\n");
  else
    printf("Not found\n");

  root = delete(root, 9);

  inorder(root);
  printf("\n");
  postorder(root);
  printf("\n");
  preorder(root);
  printf("\n");
  levelOrder(root);
  printf("\n");

  x = search(root, 6);
  if (x)
    printf("Found\n");
  else
    printf("Not found\n");

  return 0;
}
