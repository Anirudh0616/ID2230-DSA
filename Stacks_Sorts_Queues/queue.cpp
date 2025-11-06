#include <iostream>

#define MAX_SIZE 1000 // Maximum size of the queue

// Class to represent a queue
class Queue {
private:
    int arr[MAX_SIZE];
    int front_p;
    int rear_p;

public:
    Queue() {
        front_p = -1;
        rear_p = -1;
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return front_p == -1;
    }

    // Function to check if the queue is full
    bool isFull() {
        return (rear_p + 1) % MAX_SIZE == front_p;
    }

    // Function to add an element to the queue
    void enqueue(int x) {
        if (isFull()) {
            std::cout << "Error: Queue is full" << std::endl;
            return;
        }
        if (isEmpty()) {
            front_p = 0;
        }
        rear_p = (rear_p + 1) % MAX_SIZE;
        arr[rear_p] = x;
    }

    // Function to remove an element from the queue
    void dequeue() {
        if (isEmpty()) {
            std::cout << "Error: Queue is empty" << std::endl;
            return;
        }
        if (front_p == rear_p) {
            front_p = -1;
            rear_p = -1;
        } else {
            front_p = (front_p + 1) % MAX_SIZE;
        }
    }

    // Function to get the front element of the queue
    int front() {
        if (isEmpty()) {
            std::cout << "Error: Queue is empty" << std::endl;
            return -1; // Return a sentinel value
        }
        return arr[front_p];
    }

    // Function to print the queue
    void printQueue() {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        int i = front_p;
        while (i != rear_p) {
            std::cout << arr[i] << " ";
            i = (i + 1) % MAX_SIZE;
        }
        std::cout << arr[rear_p] << std::endl;
    }
};

int main() {
    Queue myQueue;

    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);

    std::cout << "Queue after enqueuing 10, 20, 30:" << std::endl;
    myQueue.printQueue();

    myQueue.dequeue();

    std::cout << "Queue after dequeuing one element:" << std::endl;
    myQueue.printQueue();

    std::cout << "Front element is: " << myQueue.front() << std::endl;

    return 0;
}
