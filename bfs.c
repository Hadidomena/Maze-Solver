#include "bfs.h"
#include "movement.h"
#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>
void bfs_traverse_file(char* maze) {
    int x = 0; FILE* file; int new[4]; int len_of_line; char buffer[1];
    file = fopen(maze, "r+");
    position * start = find_start(maze);
    position * end = find_end(maze);
    Queue* que = createQueue();
    if ( que == NULL ) {
        fclose(file);
        return;
    }
    enqueue( que, *start );

    while ( buffer ) {
        fseek( file, x, SEEK_SET );
        fread( buffer, 1, 1, file );
        if ( buffer[0] == '\n' ) {
            break;
        }
        x++;
    }
    len_of_line = x + 1;

    while( !isEmpty( que ) )
    {
        position current = dequeue(que);

        if ( current.current_character != start->current_character ) {
            fseek( file, current.current_character, SEEK_SET);
            fwrite(&current.value_of_field, 1, sizeof(current.value_of_field), file );
        }

        fseek( file, current.current_character - 1, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[0] = current.current_character - 1;
        } else if ( buffer[0] == 'K' ) {
            return ;
        } else {
            new[0] = -1;
        }

        fseek( file, current.current_character + 1, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[1] = current.current_character + 1;
        } else if ( buffer[0] == 'K' ) {
            return ;
        } else {
            new[1] = -1;
        }

        fseek( file, current.current_character - len_of_line, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[2] = current.current_character - len_of_line;
        } else if ( buffer[0] == 'K' ) {
            return ;
        } else {
            new[2] = -1;
        }

        fseek( file, current.current_character + len_of_line, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[3] = current.current_character + len_of_line;
        } else if ( buffer[0] == 'K' ) {
            return ;
        } else {
            new[3] = -1;
        }

        if ( current.value_of_field < 'z' ) {
            buffer[0] = current.value_of_field + 1;
        } else {
            buffer[0] = 'a';
        }

        for ( x = 0; x < 4; x++ )
        {
            if ( new[x] >= 0 )
            {
                enqueue( que, *create( new[x], buffer[0] ));
            }
        }
        free_position(&current);
    }
    destroyQueue(que);
}
