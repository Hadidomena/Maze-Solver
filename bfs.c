#include "bfs.h"
#include "movement.h"
#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>

// Function to create route from start to end
void reverseLines() {
    int ch, i, count;

    FILE *outputFile = fopen("output.txt", "r+");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return;
    }

    FILE *instructionsFile = fopen("instructions.txt", "w+");
    if (instructionsFile == NULL) {
        printf("Error opening instructions file.\n");
        fclose(outputFile);
        return;
    }

    char line[31];

    fseek(outputFile, 0, SEEK_END);

    while (ftell(outputFile) > 1 ) {

        fseek(outputFile, -2, SEEK_CUR);
        if (ftell(outputFile) <= 2) {
            break;
        }
        ch = fgetc(outputFile);
        count = 0;
        while (ch != '\n') {
            line[count++] = ch;
            if(ftell(outputFile) < 2) {
                break;
            }
            fseek(outputFile, -2, SEEK_CUR);
            ch = fgetc(outputFile);
        }
        for (i = count -1 ; i >= 0 && count > 0  ; i--) {
            fprintf(instructionsFile, "%c", line[i]);
        }
        fprintf(instructionsFile, "\n");
    }
    fclose(outputFile);
    fclose(instructionsFile);
}

// Function to create route from the end to start
void backtrack(char * maze, int end, int start, int len_of_line ) {
    FILE * file = fopen(maze, "r+");
    char buffer[1];
    int current = start;
    char current_char = 'a';
    bool is_first = true;
    int direction;
    int previous_direction;
    int length = 0;

    FILE * output = fopen("output.txt", "w+");
    fprintf(output, "STOP\n");

    if (start % len_of_line == len_of_line - 2) {
        previous_direction = 0;
    } else {
        previous_direction = 3;
    }

    while ( true ) {

        if ( is_first == true ) {

            fseek( file, current - 1, SEEK_SET );
            fread( buffer, 1, 1, file );
            if ( buffer[0] >= 'a' && buffer[0] <= 'z' ) {
                current = current - 1;
                current_char = buffer[0];
                direction = 0;
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
            }

            fseek( file, current - len_of_line, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] >= 'a' && buffer[0] <= 'z' ) {
                current = current - len_of_line;
                current_char = buffer[0];
                direction = 3;
            }

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
                length++;
                break ;
            }

            fseek( file, current + len_of_line, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] == current_char ) {
                current = current + len_of_line;
                direction = 1;
            } else if ( buffer[0] == 'P' ) {
                direction = 1;
                length++;
                break ;
            }

            fseek( file, current + 1, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] == current_char ) {
                current = current + 1;
                direction = 2;
            } else if ( buffer[0] == 'P' ) {
                direction = 2;
                length++;
                break ;
            }

            fseek( file, current - len_of_line, SEEK_SET );
            fread( buffer, 1, 1, file );

            if ( buffer[0] == current_char ) {
                current = current - len_of_line;
                direction = 3;
            } else if ( buffer[0] == 'P' ) {
                direction = 3;
                length++;
                break ;
            }

        }
        if ( direction != previous_direction ) {
            fprintf(output, "FORWARD %i\n", length > 0 ? length : 1);
            if ( previous_direction == (direction + 1) % 4 ) {
                fprintf(output, "TURN LEFT\n");
            } else {
                fprintf(output, "TURN RIGHT\n");
            }
            length = 1;
        } else {
                length++;
        }
    }
    if ( direction != previous_direction ) {
        fprintf(output, "FORWARD %i\n", length - 1);
        if ( previous_direction == (direction + 1) % 4 ) {
            fprintf(output, "TURN LEFT\nFORWARD 2\n");
        } else {
            fprintf(output, "TURN RIGHT\nFORWARD 2\n");
        }
    } else {
        fprintf(output, "FORWARD %i\n", length + 1);
    }
    fprintf(output, "START\n");
    fclose(output);
}

// Function to seed maze with values
int bfs_traverse_file(char* maze) {
    int x = 0;
    FILE* file;
    int new[4];
    int len_of_line;
    char buffer[1];

    file = fopen(maze, "r+");
    position * start = find_start(maze);
    position * end = find_end(maze);

    position current;
    int curr_int;
    char curr_char;

    const char *filename1 = "queue1.txt";
    const char *filename2 = "queue2.txt";
    char data[10];
    long pos1 = 0;
    long pos2 = 0;

    sprintf(data, "%d", start->current_character);
    writeToQueue(data, filename1);
    sprintf(data, "%c", start->value_of_field);
    writeToQueue(data, filename2);

    while ( buffer ) {
        fseek( file, x, SEEK_SET );
        fread( buffer, 1, 1, file );
        if ( buffer[0] == '\n' ) {
            break;
        }
        x++;
    }
    len_of_line = x + 1;

    while( true )
    {
        readFromQueue(filename1, &pos1, data, sizeof(data));
        curr_int = atoi(data);
        readFromQueue(filename2, &pos2, data, sizeof(data));
        curr_char = data[0];

        if ( curr_int != start->current_character ) {
            fseek( file, curr_int, SEEK_SET);
            fwrite(&curr_char, 1, sizeof(curr_char), file );
        }

        fseek( file, curr_int - 1, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[0] = curr_int - 1;
        } else if ( buffer[0] == 'K' ) {
            return len_of_line;
        } else {
            new[0] = -1;
        }

        fseek( file, curr_int + 1, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[1] = curr_int + 1;
        } else if ( buffer[0] == 'K' ) {
            return len_of_line;
        } else {
            new[1] = -1;
        }

        fseek( file, curr_int - len_of_line, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[2] = curr_int - len_of_line;
        } else if ( buffer[0] == 'K' ) {
            return len_of_line;
        } else {
            new[2] = -1;
        }

        fseek( file, curr_int + len_of_line, SEEK_SET );
        fread( buffer, 1, 1, file );

        if ( buffer[0] == ' ' ) {
            new[3] = curr_int + len_of_line;
        } else if ( buffer[0] == 'K' ) {
            return len_of_line;
        } else {
            new[3] = -1;
        }

        if ( curr_char < 'z' ) {
            buffer[0] = curr_char + 1;
        } else {
            buffer[0] = 'a';
        }

        for ( x = 0; x < 4; x++ )
        {
            if ( new[x] >= 0 )
            {
                sprintf(data, "%d", new[x]);
                writeToQueue(data, filename1);
                sprintf(data, "%c", buffer[0]);
                writeToQueue(data, filename2);
            }
        }
    }
}
