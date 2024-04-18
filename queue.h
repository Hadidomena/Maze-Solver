#ifndef _QUEUE_H
#define _QUEUE_H
#include "movement.h"
void writeToQueue(const char *data, const char *filename);
void readFromQueue(const char *filename, long *pos, char *buffer, size_t bufferSize);
#endif
