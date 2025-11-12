#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INIT_CAP 100 //This is the max-heap capacity assumed, set initially

// Structure holding the heap

typedef struct {
    int *data;   //pointer to the array
    unsigned int size; //unsigned int, should be non-negative integer
    unsigned int cap; //capacity
} MaxHeap;   

/* Heap API: implement the functions below main where mentioned */

void heap_init(MaxHeap *h);
void heap_free(MaxHeap *h);
void heap_push(MaxHeap *h, int x);
int heap_top(MaxHeap *h, int *out);     // returns 1 if present, 0 if empty. Stores result in out
int heap_pop(MaxHeap *h, int *out);     //  returns 1 if popped, 0 if empty. Stores result in out
void heap_clear(MaxHeap *h);

/* helper parsing */
void strtoupper(char *s);


/* DO NOT MODIFY MAIN */
int main(void) {
    MaxHeap heap;
    heap_init(&heap);

    char line[256];
    while (fgets(line, sizeof(line), stdin)) {
        // trim leading spaces
        char *p = line;
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0' || *p == '\n') continue; // blank line

        // parse command (tokenize)
        char cmd[32];
        if (sscanf(p, "%31s", cmd) != 1) continue;
        strtoupper(cmd);

        if (strcmp(cmd, "INSERT") == 0) {
            int x;
            if (sscanf(p + strlen(cmd), "%d", &x) == 1) {
                heap_push(&heap, x);
            } else {
                // malformed: skip
            }
        } else if (strcmp(cmd, "GET_MAX") == 0) {
            int v;
            if (heap_top(&heap, &v)) printf("%d\n", v);
            else printf("EMPTY\n");
        } else if (strcmp(cmd, "EXTRACT_MAX") == 0) {
            int v;
            if (heap_pop(&heap, &v)) printf("%d\n", v);
            else printf("EMPTY\n");
        } else if (strcmp(cmd, "SIZE") == 0) {
            printf("%u\n", heap.size);
        } else if (strcmp(cmd, "CLEAR") == 0) {
            heap_clear(&heap);
        } else if (strcmp(cmd, "END") == 0) {
            break;
        } else {
            // unknown command: skip
        }
    }

    heap_free(&heap);
    return 0;
}


void strtoupper(char *s) {
    for (; *s; ++s) *s = (char)toupper((unsigned char)*s);
}

void heap_init(MaxHeap *h) {
    h->cap = INIT_CAP;
    h->size = 0;
    h->data = malloc(h->cap * sizeof(int));
    if (!h->data) { perror("malloc"); exit(EXIT_FAILURE); }
}

void heap_free(MaxHeap *h) {
    free(h->data);
    h->data = NULL;
    h->size = h->cap = 0;
}

void heap_clear(MaxHeap *h) {
    h->size = 0; // keep capacity
}


/* ---------- ADD FUNCTIONS BELOW THIS LINE TO IMPLEMENT PUSH, POP, TOP---------- */

/* To implement:
   - heap_push: insert x, sift-up
   - heap_top: return top element (without removing)
   - heap_pop: remove top, sift-down, return value
   - BONUS: implement dynamic resizing in insert when size == cap (double the capacity). Set INIT CAP to a smaller number to start in this case.
*/


void heap_push(MaxHeap *h, int x){
	if(h->size < h->cap){
		h->data[h->size] = x;
		int index = h->size;
		while(index > 0){
			int parent = (index - 1)/2;
			if(h->data[parent] < h->data[index]){
				int temp = h->data[parent];
				h->data[parent] = h->data[index];
				h->data[index] = temp;
				index = parent;
			} else {
				break;
			}
		}
		h->size++;
	}	
}



int heap_top(MaxHeap *h, int *out){     // returns 1 if present, 0 if empty. Stores result in out
	if(h->size==0) return 0;	
	*out = h->data[0];
	return 1;
}
int heap_pop(MaxHeap *h, int *out){     //  returns 1 if popped, 0 if empty. Stores result in out
	if(h->size==0) return 0;
	*out = h->data[0];
	h->data[0] = h->data[h->size - 1];
	h->size--;
	
	int index = 0;
	while(1){
		int left = (index * 2) + 1;
		int right = (index * 2) + 2;
		int largest = index;

		if(left < h->size && h->data[left] > h->data[largest]){
			largest = left;
		}
		if(right < h->size && h->data[right] > h->data[largest]){
			largest = right;
		}
		if(largest == index){
			break;
		}
		int temp = h->data[largest];
		h->data[largest] = h->data[index];
		h->data[index] = temp;
		index = largest;
	}
		
	return 1;
}
