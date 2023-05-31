#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* elements;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->elements = (int*)malloc(capacity * sizeof(int));
    return stack;
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

bool isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, int element) {
    if (isFull(stack)) {
        printf("Stiva este plina.\n");
        return;
    }
    stack->elements[++stack->top] = element;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stiva este goala.\n");
        return -1;
    }
    return stack->elements[stack->top--];
}

int longestIncreasingSubsequence(int arr[], int n) {
    Stack* stack = createStack(n);
    int maxLength = 0;
    int length = 0;
  
    for (int i = 0; i < n; i++) {
        if (isEmpty(stack) || arr[i] > stack->elements[stack->top]) {
            push(stack, arr[i]);
            length++;
        } else {
            if (length > maxLength) {
                maxLength = length;
            }
            length = 1;
            while (!isEmpty(stack)) {
                pop(stack);
            }
            push(stack, arr[i]);
        }
    }
  
    if (length > maxLength) {
        maxLength = length;
    }
  
    free(stack->elements);
    free(stack);
  
    return maxLength;
}

int main() {
    int arr[10],n;

    puts("Capacitatea sirului:");
    scanf("%d",&n);

    puts("Citeste numerele:");
    for (int i = 0; i < n; i++)
        scanf("%d",&arr[i]);
  
    int result = longestIncreasingSubsequence(arr, n);
    printf("Lungimea celui mai lung subsir crescator consecutiv: %d\n", result);
  
    return 0;
}
