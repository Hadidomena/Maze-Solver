#include "bfs.h"
#include "directions.h"
#include "movement.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int len_of_line;
    char *file_name = argv[1];

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
