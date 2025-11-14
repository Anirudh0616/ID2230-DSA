#include <stdio.h>
#include <stdlib.h>

typedef struct Heap{
  int* arr;
  int size;
  int cap;
}heap;

heap* createHeap(int cap, int* nums);
void insertRec(heap* hp, int index);
void maxHeapify(heap* hp, int index);
int popMax(heap* hp);
void insert(heap* h, int data);

// Heap Initializatiion
heap* createHeap(int cap, int* nums){
  heap* new_heap = (heap*)malloc(sizeof(heap));

  new_heap->size = 0;
  new_heap->cap = cap;
  new_heap->arr = (int*)malloc(cap * sizeof(int));

  int i;
  for (i = 0; i < cap; i++){
    new_heap->arr[i] = nums[i];
  }
  new_heap->size = i;

  i = (new_heap->size - 2)/2;
  while(i >= 0){
    maxHeapify(new_heap, i--);
  }

  return new_heap;
}

// Recursion for Swapping Parent and Child
void insertRec(heap* hp, int index){
  int parent = (index - 1)/2;

  if ( hp->arr[parent] < hp->arr[index]){
    int temp = hp->arr[parent];
    hp->arr[parent] = hp->arr[index];
    hp->arr[index] = temp;

    insertRec(hp, parent);
  }
}

// void maxHeapify(heap* hp, int index){
//   int left = index * 2 + 1;
//   int right = index * 2 + 2;
//   int max = index;
//
//   if (left >= hp->size || left < 0){
//     left = -1;
//   }
//   if (right >= hp->size || right < 0){
//     right = -1;
//   }
//
//   if (left != -1 && hp->arr[left] > hp->arr[max]){
//     max = left;
//   }
//   if (right != -1 && hp->arr[right] > hp->arr[max]){
//     max = right;
//   }
//
//   if (max != index){
//     int temp = hp->arr[max];
//     hp->arr[max] = hp->arr[index];
//     hp->arr[index] = temp;
//
//     maxHeapify(hp, max);
//   }
// }
//
void maxHeapify(heap*heap,int index){
    int largest = index;
    int left = index* 2 + 1;
    int right = index*2 + 2;
    
    if(left < 0 || left >= heap->size){
        left = -1;
    }
    if(right < 0 || right >= heap->size){
        right = -1;
    }
    if(left != -1 && heap->arr[left] > heap->arr[largest]){
        largest = left;
    }
    if(right != -1 && heap->arr[right] > heap->arr[largest]){
        largest = right;
    }
    if(largest != index){
        int temp = heap->arr[largest];
        heap->arr[largest] = heap->arr[index];
        heap->arr[index] = temp;
        
        maxHeapify(heap, largest);
    }
}



int popMax(heap* hp){
  int delete;

  if (hp->size == 0){
    printf("Heap is Empty.\n");
    return -1;
  }

  delete = hp->arr[0];

  hp->arr[0] = hp->arr[hp->size - 1];
  hp->size--;
  maxHeapify(hp, 0);

  return delete;
}

void insert(heap* hp, int data){
  if (hp->size < hp->cap){
    hp->arr[hp->size] = data;
    insertRec(hp, hp->size);
    hp->size++;
  }
}

void printHeap(heap* hp) {
    int level = 0;
    int nextBreak = 1;
    if(hp->size <= 0){
      printf("Heap Empty \n");
      return;
    }
    printf("Printing Heap: \n");

    for (int i = 0; i < hp->size; i++) {
        printf("%d ", hp->arr[i]);

        if (i + 1 == nextBreak) {
            printf("\n");
            level++;
            nextBreak += (1 << level);
        }
    }
    printf("\n");
}

int main(void){
  int arr[9] = {1,2,3,4,5,6,7,8,9};
  heap* hp = createHeap(9, arr);

  for(int i = 0; i<=9; i++){
    printHeap(hp);
    printf("Popped: %d\n", popMax(hp));
  }

  return 0;
}
