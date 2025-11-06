#include <iostream>

#define MAX_SIZE 1000 // Maximum size of the stack

// Class to represent a stack
class Stack {
private:
    int arr[MAX_SIZE];
    int top_p;

public:
    Stack() {
        top_p = -1; // Initialize top to -1 to indicate an empty stack
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        return top_p == -1;
    }

    // Function to check if the stack is full
    bool isFull() {
        return top_p == MAX_SIZE - 1;
    }

    // Function to add an element to the stack (push)
    void push(int x) {
        if (isFull()) {
            std::cout << "Error: Stack overflow" << std::endl;
            return;
        }
        arr[++top_p] = x;
        std::cout << x << " pushed to stack" << std::endl;
    }

    // Function to remove an element from the stack (pop)
    int pop() {
        if (isEmpty()) {
            std::cout << "Error: Stack underflow" << std::endl;
            return 0;
        }
        int x = arr[top_p--];
        return x;
    }

    // Function to get the top element of the stack
    int peek() {
        if (isEmpty()) {
            std::cout << "Error: Stack is empty" << std::endl;
            return 0;
        }
        int x = arr[top_p];
        return x;
    }

    // Function to print the stack
    void printStack() {
        if (isEmpty()) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        std::cout << "Elements in stack are: ";
        for (int i = top_p; i >= 0; i--) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    myStack.printStack();

    std::cout << myStack.pop() << " popped from stack" << std::endl;

    myStack.printStack();

    std::cout << "Top element is: " << myStack.peek() << std::endl;

    return 0;
}
