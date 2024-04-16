#include <stdio.h>
#include <stdlib.h>
#include "movement.h"
#include "queue.h"
#include "bfs.h"

int main( int argc, char* argv[] ) {

    int len_of_line;
    char* file_name = argv[1];

    position * start = find_start(file_name);
    position * end = find_end(file_name);

    // Traverse the file using BFS
    len_of_line = bfs_traverse_file(file_name);

    printf("After traverse\n");

    backtrack(file_name, start->current_character, end->current_character, len_of_line);

    printf("output created\n");

    reverseLines();

    remove("output.txt");

    printf("End\n");

    return 0;
}
