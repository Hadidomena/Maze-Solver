#ifndef _MOVEMENT_H
#define _MOVEMENT_H
#include <stdio.h>
typedef struct _position
{
    int current_character;
    char value_of_field;
} position;

position * create( int current_character, char value_of_field);
void free_position(position* pos);
position * find_start(char * maze);
position * find_end(char * maze);
#endif
