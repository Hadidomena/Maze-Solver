#include "movement.h"
#include <stdlib.h>
#include <stdio.h>

position * create( int current_character, char value_of_field ) {
    position * curr_position = (position *) malloc(sizeof(position));
    curr_position->current_character = current_character;
    curr_position->value_of_field = value_of_field;
    return curr_position;
}

position * find_start(char * maze) {
    FILE * file;
    file = fopen(maze, "r+");
    char buffer[1]; int x = 0;
    while ( buffer ) {
        fseek( file, x, SEEK_SET );
        fread( buffer, 1, 1, file );
        if ( buffer[0] == 'P' ) {
            break;
        }
        x++;
    }
    return create( x, 'a');
}

position * find_end(char * maze) {
    FILE * file;
    file = fopen(maze, "r+");
    char buffer[1]; int x = 0;
    while ( buffer[0] ) {
        fseek( file, x, SEEK_SET );
        fread(buffer, 1, 1, file);
        if ( buffer[0] == 'K' ) {
            break;
        }
        x++;
    }
    return create( x, 'K');
}
void free_position(position* pos) {
    if (pos != NULL) {
        free(pos); // Free memory allocated for position struct
    }
}
