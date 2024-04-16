#include "bfs.h"
#include "movement.h"
#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>

void reverseLines() {
    int ch; int i; int count;
    // Open the output file for reading
    FILE *outputFile = fopen("output.txt", "r+");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return;
    }

    // Open the instructions file for writing
    FILE *instructionsFile = fopen("instructions.txt", "w+");
    if (instructionsFile == NULL) {
        printf("Error opening instructions file.\n");
        fclose(outputFile);
        return;
    }

    // Buffer to store each line read from the output file
    char line[31]; // Assuming no line is longer than 30 characters

    fseek(outputFile, 0, SEEK_END);
    while (ftell(outputFile) > 1 ){
        fseek(outputFile, -2, SEEK_CUR);
        if (ftell(outputFile) <= 2) {break;}
        ch = fgetc(outputFile);
        count = 0;
        while(ch != '\n'){
            line[count++] = ch;
            if(ftell(outputFile) < 2) {break;}
            fseek(outputFile, -2, SEEK_CUR);
            ch =fgetc(outputFile);
        }
        for (i = count -1 ; i >= 0 && count > 0  ; i--) {
            fprintf(instructionsFile, "%c", line[i]);
        }
        fprintf(instructionsFile, "\n");
    }
    fclose(outputFile);

    // Delete the output file
    remove("output.txt");
}

void backtrack(char * maze, int end, int start, int len_of_line ) {
    FILE * file = fopen(maze, "r+"); char buffer[1]; int current = start;
    char current_char = 'a'; bool is_first = true;
    int direction; int previous_direction; int length = 0;

    FILE * output = fopen("output.txt", "w+");
    fprintf(output, "Stop\n");

    while ( true ) {

        if ( is_first == true ) {

            fseek( file, current - 1, SEEK_SET );
            fread( buffer, 1, 1, file );
            if ( buffer[0] >= 'a' && buffer[0] <= 'z' ) {
                current = current - 1;
                current_char = buffer[0];
                direction = 0;
                fprintf(output, "Forward 1\nTurn Left\n");
            }

            fseek( file, current + len_of_line, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] >= 'a' && buffer[0] <= 'z' ) {
                current = current + len_of_line;
                current_char = buffer[0];
                direction = 1;
            }

            fseek( file, current + 1, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] >= 'a' && buffer[0] <= 'z' ) {
                current = current + 1;
                current_char = buffer[0];
                direction = 2;
                fprintf(output, "Forward 1\nTurn Right\n");
            }

            fseek( file, current - len_of_line, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] >= 'a' && buffer[0] <= 'z' ) {
                current = current - len_of_line;
                current_char = buffer[0];
                direction = 3;
            }
            previous_direction = direction;
            is_first = false;

        } else {
            previous_direction = direction;

            if ( current_char > 'a' ) {
                current_char = current_char - 1;
            } else {
                current_char = 'z';
            }

            fseek( file, current - 1, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] == current_char ) {
                current = current - 1;
                direction = 0;
            } else if ( buffer[0] == 'P' ) {
                direction = 0;
                break ;
            }

            fseek( file, current + len_of_line, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] == current_char ) {
                current = current + len_of_line;
                direction = 1;
            } else if ( buffer[0] == 'P' ) {
                direction = 1;
                break ;
            }

            fseek( file, current + 1, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] == current_char ) {
                current = current + 1;
                direction = 2;
            } else if ( buffer[0] == 'P' ) {
                direction = 2;
                break ;
            }

            fseek( file, current - len_of_line, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] == current_char ) {
                current = current - len_of_line;
                direction = 3;
            } else if ( buffer[0] == 'P' ) {
                direction = 3;
                break ;
            }

        }
        if ( direction != previous_direction ) {
            fprintf(output, "Forward %i\n", length);
            if ( previous_direction == (direction + 1) % 4 ) {
                fprintf(output, "Turn Left\n");
            } else {
                fprintf(output, "Turn Right\n");
            }
            length = 1;
        } else {
                length++;
        }
    }
    if ( direction != previous_direction ) {
        fprintf(output, "Forward %i\n", length + 1);
        if ( previous_direction == (direction + 1) % 4 ) {
            fprintf(output, "Turn Left\nForward 1\n");
        } else {
            fprintf(output, "Turn Right\nForward 1\n");
        }
    } else {
        fprintf(output, "Forward %i\n", length + 1);
    }
    fprintf(output, "Start\n");
}
void bfs_traverse_file(char* maze) {
    int x = 0; FILE* file; int new[4]; int len_of_line; char buffer[1];
    file = fopen(maze, "r+");
    position * start = find_start(maze);
    position * end = find_end(maze);
    position current;
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
        current = dequeue(que);

        if ( current.current_character != start->current_character ) {
            fseek( file, current.current_character, SEEK_SET);
            fwrite(&current.value_of_field, 1, sizeof(current.value_of_field), file );
        }

        fseek( file, current.current_character - 1, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[0] = current.current_character - 1;
        } else if ( buffer[0] == 'K' ) {
            backtrack(maze, start->current_character, end->current_character, len_of_line);
            return ;
        } else {
            new[0] = -1;
        }

        fseek( file, current.current_character + 1, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[1] = current.current_character + 1;
        } else if ( buffer[0] == 'K' ) {
            backtrack(maze, start->current_character, end->current_character, len_of_line);
            return ;
        } else {
            new[1] = -1;
        }

        fseek( file, current.current_character - len_of_line, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[2] = current.current_character - len_of_line;
        } else if ( buffer[0] == 'K' ) {
            backtrack(maze, start->current_character, end->current_character, len_of_line);
            return ;
        } else {
            new[2] = -1;
        }

        fseek( file, current.current_character + len_of_line, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[3] = current.current_character + len_of_line;
        } else if ( buffer[0] == 'K' ) {
            backtrack(maze, start->current_character, end->current_character, len_of_line);
            return;
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
    }
    destroyQueue(que);
}
