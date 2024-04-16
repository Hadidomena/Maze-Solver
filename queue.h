#ifndef _QUEUE_H
#define _QUEUE_H
#include "movement.h"
typedef struct Node {
    position value;
    struct Node* next;
} Node;

// Define the queue
typedef struct {
    Node* front;
    Node* rear;
} Queue;

Node* newNode(position value);
Queue* createQueue();
void enqueue(Queue* q, position value);
position dequeue(Queue* q);
int isEmpty(Queue* q);
void destroyQueue(Queue* q);
void writeToQueue(const char *data, const char *filename);
void readFromQueue(const char *filename, long *pos, char *buffer, size_t bufferSize);
#endif
