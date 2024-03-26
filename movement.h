#ifndef _MOVEMENT_H
#define _MOVEMENT_H
#include <stdio.h>
typedef struct _position
{
    int current_character;
    int len_of_line;
} position;

position * create(FILE maze, int current_character);

int move_up(position * current_position);

int move_right(position * current_position);

int move_down(position * current_position);

int move_left(position * current_position);
#endif
