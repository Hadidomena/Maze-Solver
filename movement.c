#include "movement.h"
#include <stdlib.h>
#include <stdio.h>

position * create( char * maze, int current_character, char value_of_field ) {
    FILE * file;
    position * curr_position = (position *) malloc(sizeof(position));

    file = fopen(maze, "r+");
    char buffer[1]; int x = 0;
    while ( buffer ) {
        fseek( file, x, SEEK_SET );
        fread( buffer, 1, 1, file );
        if ( buffer[0] == '\n' ) {
            break;
        }
        x++;
    }

    curr_position->len_of_line = x + 1;
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
    return create(maze, x, 'a');
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
    return create(maze, x, 'K');

}

int * get_adjacent(position * current_position, char * maze, int came_from) {

    int* result; int len_of_result = 0; char buffer[1];
    FILE* file = fopen(maze, "r+");


}
