#include "bfs.h"
#include "binary.h"
#include "movement.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void removeTempFiles() {

    if (remove("output.txt") != 0) {
        perror("Error removing output.txt");
    }
    if (remove("queue1.txt") != 0) {
        perror("Error removing queue1.txt");
    }
    if (remove("queue2.txt") != 0) {
        perror("Error removing queue2.txt");
    }
    if (remove("temp_maze.txt") != 0) {
        perror("Error removing temp_maze.txt");
    }
}


void replaceCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Error creating temporary file.\n");
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == 'X' || ch == 'K' || ch == 'P' || ch == ' ' || ch == '\n') {
            fputc(ch, tempFile);
        } else {
            fputc(' ', tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Rename temp file to original filename
    if (remove(filename) != 0) {
        printf("Error removing original file.\n");
        return;
    }
    if (rename("temp.txt", filename) != 0) {
        printf("Error renaming temp file.\n");
        return;
    }

    printf("Characters replaced successfully.\n");
}

int main(int argc, char *argv[])
{

    int len_of_line;
    char *file_name = argv[1];
    removeTempFiles();
    replaceCharacters(file_name);

    if (argc != 2)
    {
        printf("Invalid arguments, pass only one argument to function, filename of maze\n");
        return 1;
    }

    if (is_txt_file(file_name) == 0)
    {

        position *start = find_start(file_name);
        position *end = find_end(file_name);

        len_of_line = bfs_traverse_file(file_name);
        remove("queue1.txt");
        remove("queue2.txt");

        backtrack(file_name, start->current_character, end->current_character, len_of_line);

        reverseLines();
        remove("output.txt");
    }
    else if (is_txt_file(file_name) == 1)
    {

        bin_to_txt(file_name, "temp_maze.txt");

        position *start = find_start("temp_maze.txt");
        position *end = find_end("temp_maze.txt");

        len_of_line = bfs_traverse_file("temp_maze.txt");
        remove("queue1.txt");
        remove("queue2.txt");

        backtrack("temp_maze.txt", start->current_character, end->current_character, len_of_line);

        reverseLines();
        remove("output.txt");
        remove("temp_maze.txt");
    }
    else
    {
        printf("Not a proper filename.\n");
    }

    return 0;
}
