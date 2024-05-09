#include "queue.h"
#include "movement.h"
#include <stdio.h>
#include <stdlib.h>


// Function to write data to the file
void writeToQueue(const char *data, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%s\n", data);
    fclose(file);
}

// Function to read data from the file
void readFromQueue(const char *filename, long *pos, char *buffer, size_t bufferSize) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    fseek(file, *pos, SEEK_SET);
    fgets(buffer, bufferSize, file);
    *pos = ftell(file);
    fclose(file);
}
