#include "movement.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
// Function to create a new node
Node* newNode(position value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->value = value;
    temp->next = NULL;
    return temp;
}

// Function to create an empty queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to add an element to the queue
void enqueue(Queue* q, position value) {
    Node* temp = newNode(value);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// Function to remove an element from the queue
position dequeue(Queue* q) {
    if (q->front == NULL)
        exit(EXIT_FAILURE);

    Node* temp = q->front;
    position value = temp->value;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return value;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return (q->front == NULL);
}
void destroyQueue(Queue* q) {
    if (q != NULL) {
        Node* current = q->front;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp); // Free memory allocated for node
        }
        free(q); // Free memory allocated for queue
    }
}
