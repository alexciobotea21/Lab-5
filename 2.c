#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char* elements;
    int top;
    int capacity;
} Stack;

typedef struct {
    char* elements;
    int front;
    int rear;
    int capacity;
} Queue;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->elements = (char*)malloc(capacity * sizeof(char));
    return stack;
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

bool isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, char element) {
    if (isFull(stack)) {
        printf("Stiva este plina.\n");
        return;
    }
    stack->elements[++stack->top] = element;
}

char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stiva este goala.\n");
        return '\0';
    }
    return stack->elements[stack->top--];
}

char top(Stack* stack) {
    if (isEmpty(stack)) {
        return '\0';
    }
    return stack->elements[stack->top];
}

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->elements = (char*)malloc(capacity * sizeof(char));
    return queue;
}

bool isQueueEmpty(Queue* queue) {
    return queue->rear < queue->front;
}

bool isQueueFull(Queue* queue) {
    return queue->rear == queue->capacity - 1;
}

void enqueue(Queue* queue, char element) {
    if (isQueueFull(queue)) {
        printf("Coada este plina.\n");
        return;
    }
    queue->elements[++queue->rear] = element;
}

char dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Coada este goala.\n");
        return '\0';
    }
    return queue->elements[queue->front++];
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int getPrecedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Converteste expresia infix in postfix
char* infixToPostfix(char* expression) {
    int length = strlen(expression);

    char* postfix = (char*)malloc((length + 1) * sizeof(char));
    int postfixIndex = 0;

    Stack* stack = createStack(length);

    for (int i = 0; i < length; i++) {
        char ch = expression[i];

        if (ch == ' ')
            continue;

        if (!isOperator(ch)) {
            postfix[postfixIndex++] = ch;
        } else {
            // Daca este operator, scoate operatorii cu precedenta mai mare sau egala din stiva
            // si adauga-i la rezultatul final inaintea adaugarii operatorului curent in stiva
            while (!isEmpty(stack) && getPrecedence(ch) <= getPrecedence(top(stack))) {
                postfix[postfixIndex++] = pop(stack);
            }
            push(stack, ch);
        }
    }

    // Scoate toti operatorii ramasi din stiva si adauga-i la rezultatul final
    while (!isEmpty(stack)) {
        postfix[postfixIndex++] = pop(stack);
    }

    postfix[postfixIndex] = '\0';

    free(stack->elements);
    free(stack);

    return postfix;
}

int main() {
    char* expression = "2 + 3 * 4 - 5";

    char* postfix = infixToPostfix(expression);

    printf("Expresia in notatie postfix: %s\n", postfix);

    free(postfix);

    return 0;
}
