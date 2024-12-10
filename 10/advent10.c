#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent10"

//#define ROWS 8
//#define COLS 8
//#define ROWSIZE 8
//#define COLSIZE 8
#define ROWS 43
#define COLS 43
#define ROWSIZE 43
#define COLSIZE 43

int pointer_list_contains(struct _pointer_list* p, char* str)
{
    int ret = 0;
    for(int i = 0; i < pointer_list_size(p); i++)
    {
        if(strcmp(str, pointer_list_get_at(p, i)) == 0)
        {
            ret++;
        }
    }
    return ret;
}

int checksurroundingtiles(struct _pointer_list* peaks, char* puzzle, int pos, int row, int col, int rows, int cols, int rowsize, int n, int maxheight)
{
    int tile1 = -1;
    int tile2 = -1;
    int tile3 = -1;
    int tile4 = -1;
    char temp[2];
    temp[1] = '\0';

    ylogd("searching for spot of height %i from pos %i row %i col %i", n, pos, row, col);

    if(row > 0)
    {
        temp[0] = puzzle[pos-rowsize];
        tile1 = atoi(temp);
        ylogd("tile up is %i", tile1);
    }
    if(col > 0)
    {
        temp[0] = puzzle[pos-1];
        tile2 = atoi(temp);
        ylogd("tile left is %i", tile2);
    }
    if(row < (rows-1))
    {
        temp[0] = puzzle[pos+rowsize];
        tile3 = atoi(temp);
        ylogd("tile down is %i", tile3);
    }
    if(col < (cols-1))
    {
        temp[0] = puzzle[pos+1];
        tile4 = atoi(temp);
        ylogd("tile right is %i", tile4);
    }

    int c = 0;
    if(tile1 == maxheight && n == maxheight)
    {
        char* temp2;
        asprintf(&temp2, "%i|%i", row-1, col);
        if(pointer_list_contains(peaks, temp2) == 0)
        {
            pointer_list_append(peaks, o_strdup(temp2));
        }
        free(temp2);
        c++;
    }
    if(tile2 == maxheight && n == maxheight)
    {
        char* temp2;
        asprintf(&temp2, "%i|%i", row, col-1);
        if(pointer_list_contains(peaks, temp2) == 0)
        {
            pointer_list_append(peaks, o_strdup(temp2));
        }
        free(temp2);
        c++;
    }
    if(tile3 == maxheight && n == maxheight)
    {
        char* temp2;
        asprintf(&temp2, "%i|%i", row+1, col);
        if(pointer_list_contains(peaks, temp2) == 0)
        {
            pointer_list_append(peaks, o_strdup(temp2));
        }
        free(temp2);
        c++;
    }
    if(tile4 == maxheight && n == maxheight)
    {
        char* temp2;
        asprintf(&temp2, "%i|%i", row, col+1);
        if(pointer_list_contains(peaks, temp2) == 0)
        {
            pointer_list_append(peaks, o_strdup(temp2));
        }
        free(temp2);
        c++;
    }
    if(n == maxheight)
    {
        return c;
    }

    int b = 0;
    if(tile1 == n)
    {
        ylogd("continuing up");
        b = b + checksurroundingtiles(peaks, puzzle, pos-rowsize, row-1, col, rows, cols, rowsize, n+1, maxheight);
    }
    if(tile2 == n)
    {
        ylogd("continuing left");
        b = b + checksurroundingtiles(peaks, puzzle, pos-1, row, col-1, rows, cols, rowsize, n+1, maxheight);
    }
    if(tile3 == n)
    {
        ylogd("continuing down");
        b = b + checksurroundingtiles(peaks, puzzle, pos+rowsize, row+1, col, rows, cols, rowsize, n+1, maxheight);
    }
    if(tile4 == n)
    {
        ylogd("continuing right");
        b = b + checksurroundingtiles(peaks, puzzle, pos+1, row, col+1, rows, cols, rowsize, n+1, maxheight);
    }

    return b;
}

int examinetrails(char* puzzle, int rows, int cols, int rowsize, int colsize, int part2)
{
    int i =0;
    int summits = 0;
    int paths = 0;
    int row = 0;
    int col = 0;
    int start = 0;
    while(i < (rows * cols))
    //while(i < 3)
    {
        if(puzzle[i] == '0')
        {
            ylogd("found trail head at position %i row %i col %i", i, row, col);

            struct _pointer_list* peaks = o_malloc(sizeof(struct _pointer_list));
            pointer_list_init(peaks);

            int res = checksurroundingtiles(peaks, puzzle, i, row, col, rows, cols, rowsize, 1, 9);
            ylogi("results in %i finishing heads pointer list %i", res, pointer_list_size(peaks));

            paths += res;
            summits += pointer_list_size(peaks);

            for(int e = 0; e < pointer_list_size(peaks); e++)
            {
                free(pointer_list_get_at(peaks, e));
            }
            pointer_list_clean(peaks);
            o_free(peaks);

        }
        i++;
        col++;
        if((i % rowsize) == 0)
        {
            row++;
        }
        if(col == (cols))
        {
            col = 0;
        }
    }

    if(part2 > 0)
    {
        return paths;
    }
    return summits;
}

int main(int argc, char** argv)
{

    clock_t start_time = clock();

    Parameters* p = malloc(sizeof(Parameters));

    ConfigError ppe = getParameters(argc, argv, p);

    if(p->verbosity_count>0)
    {
        y_init_logs(PROGNAME, Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_DEBUG, NULL, "Initializing logs mode: file, logs level: debug");
    }
    else
    {
        y_init_logs(PROGNAME, Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_INFO, NULL, "Initializing logs mode: file, logs level: info");
    }




    //char* str = fileslurp("advent10sample.txt");
    char* str = fileslurp("advent10nonewlines.txt");


    int i = 0;
    int file_id = 0;

    int len = strlen(str);
    ylogd("string length is %i", len);



    int a1 = 0;
    int a2 = 0;
    a1 = examinetrails(str, ROWS, COLS, ROWSIZE, COLSIZE, 0);
    a2 = examinetrails(str, ROWS, COLS, ROWSIZE, COLSIZE, 1);

    free(str);
    free(p);
    ylogi("Found a total score of %i for entire map", a1);
    ylogi("Found a total rating of %i for entire map", a2);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();

    return 0;
}
