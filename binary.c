#include "binary.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Function to check type of passed filename
int is_txt_file(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (dot != NULL) {
        if (strcasecmp(dot, ".txt") == 0) {
            return 0;
        }
        else if (strcasecmp(dot, ".bin") == 0) {
            return 1;
        }
    }
    return 2;
}

// Function to change binary file into txt file
void bin_to_txt(const char* binary_filename, const char* text_filename) {

    uint8_t Value; int x; uint8_t Count;
    int curr_row = 1; int curr_col = 1;

    FILE *binary = fopen(binary_filename, "rb+");
    if ( binary == NULL ) {
        printf("Error opening binary file.\n");
        return ;
    }

    FILE *text = fopen(text_filename, "w+");
    if ( text == NULL ) {
        printf("Error opening text file.\n");
        return ;
    }

    uint32_t File_Id;    fread(&File_Id, sizeof(File_Id), 1, binary);
    uint8_t Escape;    fread(&Escape, sizeof(Escape), 1, binary);
    uint16_t Columns;    fread(&Columns, sizeof(Columns), 1, binary);
    uint16_t Lines;    fread(&Lines, sizeof(Lines), 1, binary);
    uint16_t Entry_X;    fread(&Entry_X, sizeof(Entry_X), 1, binary);
    uint16_t Entry_Y;    fread(&Entry_Y, sizeof(Entry_Y), 1, binary);
    uint16_t Exit_X;    fread(&Exit_X, sizeof(Exit_X), 1, binary);
    uint16_t Exit_Y;   fread(&Exit_Y, sizeof(Exit_Y), 1, binary);
    fseek(binary, 12, SEEK_CUR);
    uint32_t Counter;    fread(&Counter, sizeof(Counter), 1, binary);
    uint32_t Solution_Offset;   fread(&Solution_Offset, sizeof(Solution_Offset), 1, binary);
    uint8_t Separator;    fread(&Separator, sizeof(Separator), 1, binary);
    uint8_t Wall;    fread(&Wall, sizeof(Wall), 1, binary);
    uint8_t Path;    fread(&Path, sizeof(Path), 1, binary);

    while ( Counter-- )
    {
        fseek(binary, 1, SEEK_CUR);
        fread(&Value, sizeof(Value), 1, binary);
        fread(&Count, sizeof(Count), 1, binary);

        for ( x = 0; x < Count + 1; x++ )
        {
            if ( curr_row == Entry_Y && curr_col == Entry_X ) {
                fprintf( text, "P" );
            } else if ( curr_row == Exit_Y && curr_col == Exit_X ) {
                fprintf( text, "K" );
            } else if ( Value == Wall ) {
                fprintf( text, "X" );
            } else if ( Value == Path ) {
                fprintf( text, " " );
            }

            curr_col++;
            if (curr_col > Columns) {
                fprintf(text, "\n");
                curr_col = 1;
                curr_row++;
            }
        }
    }

    fclose(binary);
    fclose(text);
}
