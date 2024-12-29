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

#define PROGNAME "advent12"

//#define ROWS 15
//#define COLS 59
//#define ROWSIZE 59
//#define COLSIZE 15
//#define ROWS 6
//#define COLS 6
//#define ROWSIZE 6
//#define COLSIZE 6
//#define ROWS 10
//#define COLS 10
//#define ROWSIZE 10
//#define COLSIZE 10
//#define ROWS 4
//#define COLS 5
//#define ROWSIZE 5
//#define COLSIZE 4
#define ROWS 140
#define COLS 140
#define ROWSIZE 140
#define COLSIZE 140


int globalseen[ROWS*COLS];

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

int checksurroundingtiles(struct _pointer_list* peaks, char* puzzle, int pos, int row, int col, int rows, int cols, int rowsize, int n, int maxheight, char test)
{
    char tile1 = -1;
    char tile2 = -1;
    char tile3 = -1;
    char tile4 = -1;
    char* temp;

    if(row > 0)
    {
        tile1 = puzzle[pos-rowsize];
    }
    if(col > 0)
    {
        tile2 = puzzle[pos-1];
    }
    if(row < (rows-1))
    {
        tile3 = puzzle[pos+rowsize];
    }
    if(col < (cols-1))
    {
        tile4 = puzzle[pos+1];
    }

    char tile;
    if(pos > rows*cols || pos < 0)
    {
        tile = ']';
    }
    else
    {
        tile = puzzle[pos];
    }


    if(tile != test)
    {
        return n;
    }


    char* temp2;
    asprintf(&temp2, "%i", pos);

    if(pointer_list_contains(peaks, temp2) == 0)
    {
        pointer_list_append(peaks, o_strdup(temp2));
    }
    else
    {
        free(temp2);
        return 0;
    }

    globalseen[pos] = 1;
    free(temp2);






    if(tile1 == test)
    {
        ylogd("continuing up");
        n = n + checksurroundingtiles(peaks, puzzle, pos-rowsize, row-1, col, rows, cols, rowsize, n+1, maxheight, test);
    }
    if(tile2 == test)
    {
        ylogd("continuing left");
        n = n + checksurroundingtiles(peaks, puzzle, pos-1, row, col-1, rows, cols, rowsize, n+1, maxheight, test);
    }
    if(tile3 == test)
    {
        ylogd("continuing down");
        n = n + checksurroundingtiles(peaks, puzzle, pos+rowsize, row+1, col, rows, cols, rowsize, n+1, maxheight, test);
    }
    if(tile4 == test)
    {
        n = n + checksurroundingtiles(peaks, puzzle, pos+1, row, col+1, rows, cols, rowsize, n+1, maxheight, test);
    }

    return n;
}

int cellperimetercheck(int pos, char* puzzle)
{
    int row = pos / ROWSIZE;
    int col = pos % ROWSIZE;

    char val = puzzle[pos];
    //ylogd("checking row %i col %i pos %i val %c %i", row, col, pos, val, ROWSIZE);

    int lines = 0;

    if(row == 0)
    {
        lines = lines + 1;
    }
    else
    {
        if(puzzle[pos-ROWSIZE] != val)
        {
            lines = lines + 1;
        }
    }

    if(row == (ROWS-1))
    {
        lines = lines + 1;
    }
    else
    {
        if(puzzle[pos+ROWSIZE] != val)
        {
            lines = lines + 1;
        }
    }

    if(col == 0)
    {
        lines = lines + 1;
    }
    else
    {
        if(puzzle[pos-1] != val)
        {
            lines = lines + 1;
        }
    }

    if(col == (COLS-1))
    {
        lines = lines + 1;
    }
    else
    {
        if(puzzle[pos+1] != val)
        {
            lines = lines + 1;
        }
    }


    return lines;
}

uint64_t calcperimeter(struct _pointer_list* p, char* puzzle)
{
    uint64_t perimeter = 0;

    for(int e = 0; e < pointer_list_size(p); e++)
    {
        char* temp = pointer_list_get_at(p, e);
        ylogd("%s", temp);
        int pos = strtoul(temp, NULL, 10);

        perimeter = perimeter + cellperimetercheck(pos, puzzle);
    }


    return perimeter;
}

int celledgecheck(int pos, char* puzzle)
{
    int row = pos / ROWSIZE;
    int col = pos % ROWSIZE;

    char val = puzzle[pos];
    ylogi("checking row %i col %i pos %i val %c %i", row, col, pos, val, ROWSIZE);

    int edges = 0;

    // bottom left outer edge
    if((row == 0 && col == 0))
    {
        edges = edges + 1;
    }

    if(row > 0)
    {
        if((puzzle[pos-1] != val || col == 0) && puzzle[pos-ROWSIZE] != val)
        {
            edges = edges + 1;
        }
    }
    else
    {
        if(col > 0 && puzzle[pos-1] != val)
        {
            edges = edges + 1;
        }
    }
    ylogi("edges is %i", edges);

    // bottom right outer edge
    if(row == 0 && col == COLS-1)
    {
        edges = edges + 1;
    }

    if(row > 0)
    {
        if((puzzle[pos+1] != val || col == COLS-1) && puzzle[pos-ROWSIZE] != val)
        {
            edges = edges + 1;
        }
    }
    else
    {
        if(col < COLS-1 && puzzle[pos+1] != val)
        {
            edges = edges + 1;
        }
    }
    ylogi("edges is %i", edges);

    // top right outer edge
    if(row == ROWS-1 && col == COLS-1)
    {
        edges = edges + 1;
        //if(puzzle[pos-1] == val && puzzle[pos-ROWSIZE] == val && puzzle[pos-ROWSIZE-1] != val)
        //{
        //    ylogi("hit");
        //    edges = edges + 1;
        //}
    }

    if(row < ROWS-1)
    {
        if((puzzle[pos+1] != val || col == COLS-1) && puzzle[pos+ROWSIZE] != val)
        {
            edges = edges + 1;
        }
    }
    else
    {
        if(col < COLS-1 && puzzle[pos+1] != val)
        {
            edges = edges + 1;
        }
    }
    ylogi("edges is %i", edges);

    // top left outer edge
    if(row == ROWS-1 && col == 0)
    {
        edges = edges + 1;
    }

    if(row < ROWS-1)
    {
        if((puzzle[pos-1] != val || col == 0) && puzzle[pos+ROWSIZE] != val)
        {
            edges = edges + 1;
        }
    }
    else
    {
        if(col > 0 && puzzle[pos-1] != val)
        {
            edges = edges + 1;
        }
    }
    ylogi("edges is %i", edges);



    // bottom right inner edge

    if(col > 0)
    {
    // bottom right inner edge
    if(row < ROWS-1 && puzzle[pos+ROWSIZE-1] != val && puzzle[pos+ROWSIZE] == val && puzzle[pos-1] == val)
    {
        edges = edges + 1;
    }
    // top right inner edge
    if(row > 0 && puzzle[pos-(ROWSIZE+1)] != val && puzzle[pos-ROWSIZE] == val && puzzle[pos-1] == val)
    {
        edges = edges + 1;
    }



    }



    if(col < COLS-1)
    {
    // top left inner edge
    if(row > 0 && puzzle[pos-(ROWSIZE-1)] != val && puzzle[pos-ROWSIZE] == val && puzzle[pos+1] == val)
    {
        ylogi("top left inner edge %i diagonal %c", pos, puzzle[pos-(ROWSIZE-1)]);
        edges = edges + 1;
    }

    // bottom left inner edge
    if(row < ROWS-1 && puzzle[pos+ROWSIZE+1] != val && puzzle[pos+ROWSIZE] == val && puzzle[pos+1] == val)
    {
        edges = edges + 1;
    }
    }


    ylogi("edges is %i", edges);

    return edges;
}

uint64_t calcsides(struct _pointer_list* p, char* puzzle)
{
    uint64_t edges = 0;

    for(int e = 0; e < pointer_list_size(p); e++)
    {
        char* temp = pointer_list_get_at(p, e);
        ylogi("pos %s", temp);
        int pos = strtoul(temp, NULL, 10);

        edges = edges + celledgecheck(pos, puzzle);
    }


    return edges;
}


uint64_t examineplants(char* puzzle, int rows, int cols, int rowsize, int colsize, int part2)
{
    int i =0;
    uint64_t price = 0;
    int row = 0;
    int col = 0;
    char start = puzzle[0];
    char currchar = start;


    uint64_t totarea = 0;

    for(int j = 0; j < (rows*cols); j++)
    {
        globalseen[j] = 0;
    }

    while(i < (rows * cols))
    {
        if(globalseen[i] == 0)
        {
            //ylogd("found trail head at position %i row %i col %i", i, row, col);

            struct _pointer_list* peaks = o_malloc(sizeof(struct _pointer_list));
            pointer_list_init(peaks);


            char test = puzzle[i];
            int res = checksurroundingtiles(peaks, puzzle, i, row, col, rows, cols, rowsize, 0, 9, test);

            uint64_t area = pointer_list_size(peaks);
            totarea = totarea + area;

            uint64_t subprice = 0;
            if(part2 > 0)
            {
                uint64_t sides = calcsides(peaks, puzzle);
                subprice = sides * area;
                ylogi("found %c list of area %llu and sides %llu price %llu", puzzle[i], area, sides, subprice);
            }
            else
            {
                uint64_t peri = calcperimeter(peaks, puzzle);
                subprice = peri * area;
            }

            price = price + subprice;

            //ylogi("found %c list of area %llu and perimeter %llu price %llu", puzzle[i], pointer_list_size(peaks), peri, subprice);

            for(int e = 0; e < pointer_list_size(peaks); e++)
            {
                o_free(pointer_list_get_at(peaks, e));
            }
            pointer_list_clean(peaks);
            o_free(peaks);
        }
        //else
        //{
        //    ylogd("pos %i already seen", i);
        //}
        i = i+1;
        if((i % rowsize) == 0)
        {
            row++;
        }
        col++;
        if(col == (cols))
        {
            col = 0;
        }
    }
    ylogd("tot area: %llu", totarea);

    return price;
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

    //char* str = fileslurp("tempsimple4.txt");
    //char* str = fileslurp("tempsimple3.txt");
    //char* str = fileslurp("advent12sample.txt");
    char* str = fileslurp("advent12.txt");

    uint64_t a1 = 0;
    a1 = examineplants(str, ROWS, COLS, ROWSIZE, COLSIZE, p->part2);

    ylogi("total cost is %llu", a1);

    free(str);
    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();

    return 0;
}
