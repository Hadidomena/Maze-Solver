#ifndef _BFS_H
#define _BFS_H
#include "movement.h"
#include "queue.h"
int bfs_traverse_file(char* maze);
void backtrack(char * maze, int end, int start, int len_of_line );
void reverseLines();
#endif
