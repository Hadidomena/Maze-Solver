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
    if (q->front == NULL) {
        exit(EXIT_FAILURE);
    }
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

void writeToQueue(const char *data, const char *filename) {
    FILE *file = fopen(filename, "a"); // Open file in append mode
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%s\n", data); // Write data to the file
    fclose(file); // Close the file
}

// Function to read data from the file
char *readFromQueue(const char *filename, long *pos) {
    FILE *file = fopen(filename, "r"); // Open file in read mode
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return NULL;
    }
    fseek(file, *pos, SEEK_SET); // Move the file pointer to the current position
    char *data = malloc(256 * sizeof(char)); // Allocate memory to store data
    if (data == NULL) {
        printf("Error allocating memory.\n");
        fclose(file);
        return NULL;
    }
    fgets(data, 256, file); // Read one line from the file
    *pos = ftell(file); // Update the current position
    fclose(file); // Close the file
    return data; // Return the read data
}
