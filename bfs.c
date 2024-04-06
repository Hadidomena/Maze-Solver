#include "bfs.h"
#include "movement.h"
#include "queue.h"
#include <stdbool.h>
void bfs_traverse_file(char* maze) {
    int x = 0; FILE* file;
    file = fopen(maze, "r+"); char buffer[1];
    position * start = find_start(maze);
    position * end = find_end(maze);
    Queue* que = createQueue();
    enqueue( que, *start );
    int y = 0;
    while( !isEmpty( que ) )
    {

        position current = dequeue(que);
        int new[4];
        fseek( file, current.current_character, SEEK_SET);
        fwrite(&current.value_of_field, 1, sizeof(current.value_of_field), file );
        fseek( file, current.current_character - 1, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[0] = current.current_character - 1;
        } else if ( buffer[0] == 'K' ) {
            new[0] = -2;
            return ;
        } else {
            new[0] = -1;
        }

        fseek( file, current.current_character + 1, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[1] = current.current_character + 1;
        } else if ( buffer[0] == 'K' ) {
            new[1] = -2;
            return ;
        } else {
            new[1] = -1;
        }

        fseek( file, current.current_character - current.len_of_line, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[2] = current.current_character - current.len_of_line;
        } else if ( buffer[0] == 'K' ) {
            new[2] = -2;
            return ;
        } else {
            new[2] = -1;
        }

        fseek( file, current.current_character + current.len_of_line, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[3] = current.current_character + current.len_of_line;
        } else if ( buffer[0] == 'K' ) {
            new[3] = -2;
            return ;
        } else {
            new[3] = -1;
        }

        if ( current.value_of_field < 'z' ) {
            buffer[0] = current.value_of_field + 1;
        } else {
            buffer[0] = 'a';
        }
        for ( int x = 0; x < 4; x++ )
        {
            if ( new[x] >= 0 )
            {
                enqueue( que, *create( maze, new[x], buffer[0] ));
            }
        }
        y++;
        if ( isEmpty(que) )
        {
            printf("jest puste\n");
        }
    }
}
