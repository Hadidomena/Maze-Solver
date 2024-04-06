#ifndef _MOVEMENT_H
#define _MOVEMENT_H
#include <stdio.h>
typedef struct _position
{
    int current_character;
    int len_of_line;
    char value_of_field;
} position;

position * create(char * maze, int current_character, char value_of_field);

int * get_adjacent(position * current_position, char * maze, int came_from);

position * find_start(char * maze);

position * find_end(char * maze);
#endif
