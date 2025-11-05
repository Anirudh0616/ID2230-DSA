#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Entry {
    char *key;
    char *value;
    struct Entry *next;
};

void initializeEntry(struct Entry *entry, char *key, char *value) {
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
}

struct HashTable {
    int size;
    int capacity;
    struct Entry **buckets;
};

void initHashTable(struct HashTable *table) {
    table->capacity = 100;
    table->size = 0;
    table->buckets = (struct Entry **)malloc(sizeof(struct Entry *) * table->capacity);
    for (int i = 0; i < table->capacity; i++) {
        table->buckets[i] = NULL;
    }
}

int hashKey(struct HashTable *table, char *str) {
    int index;
    int sum = 0;
    int factor = 31;
    for (int i = 0; i < strlen(str); i++) {
        sum = ((sum % table->capacity) + (((int)str[i]) * factor) % table->capacity) % table->capacity;
        factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
    }
    index = sum;
    return index;
}

void insert(struct HashTable *table, char *key, char *value) {
    int index = hashKey(table, key);
    struct Entry *newEntry = (struct Entry *)malloc(sizeof(struct Entry));
    initializeEntry(newEntry, key, value);

    if (table->buckets[index] == NULL) {
        table->buckets[index] = newEntry;
    } else {
        newEntry->next = table->buckets[index];
        table->buckets[index] = newEntry;
    }
    table->size++;
}

void removeKey(struct HashTable *table, char *key) {
    int index = hashKey(table, key);
    struct Entry *prev = NULL;
    struct Entry *current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            if (current == table->buckets[index]) {
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            table->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

char *getValue(struct HashTable *table, char *key) {
    int index = hashKey(table, key);
    struct Entry *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void printTable(struct HashTable* table) {
  for (int i = 0; i < table->capacity; i++){
    struct Entry* current = table->buckets[i];
    while(current != NULL){
      printf("%s ", current->value);
      current = current->next;
    }
    printf("\n");
  }
}

int main() {
    struct HashTable *table = (struct HashTable *)malloc(sizeof(struct HashTable));
    initHashTable(table);

    insert(table, "user1", "Alice");
    insert(table, "user2", "Bob");
    insert(table, "user3", "Charlie");
    insert(table, "user4", "David");
    insert(table, "user5", "Eve");

  printTable(table);

    printf("%p\n", getValue(table, "unknown"));

    printf("\nAfter deletion:\n");
    removeKey(table, "user5");
    printf("%p\n", getValue(table, "user5"));

  printTable(table);

    for (int i = 0; i < table->capacity; i++) {
        struct Entry *current = table->buckets[i];
        while (current != NULL) {
            struct Entry *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);

    return 0;
}

