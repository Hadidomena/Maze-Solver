#include <stdio.h>
#include <stdlib.h>
#include "movement.h"
#include "queue.h"
#include "bfs.h"

int main( int argc, char* argv[] ) {

    char* file_name = argv[1];

    FILE* file = fopen(file_name, "r+");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Traverse the file using BFS
    bfs_traverse_file(file_name);

    // Close the file
    fclose(file);
}
