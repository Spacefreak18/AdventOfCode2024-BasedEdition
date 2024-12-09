#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent08"

#define ROWS 50
#define COLS 50
#define ROWSIZE 50
#define COLSIZE 50
//#define ROWS 12
//#define COLS 12
//#define ROWSIZE 12
//#define COLSIZE 12

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


int mapantennas(char* puzzle, struct _pointer_list* nodes_list, int rows, int cols, int rowsize, int colsize, int part2)
{
    int i =0;
    int nodes = 0;
    int row = 0;
    int col = 0;
    int start = 0;
    while(i < (rows * cols))
    {
        if(puzzle[i] != '.')
        {
            ylogd("found antenna %c at pos %i row %i col %i searching for matching antennas", puzzle[i], i, row, col);
            start = i;
            int k = i;
            int trow = row;
            int tcol = col;

            int antennas = 0;
            while(k < (rows * cols))
            {

                if(k > i)
                {
                    if(puzzle[i] == puzzle[k])
                    {
                        ylogd("found matching antenna %c at pos %i row %i col %i calculating antinode positions", puzzle[k], k, trow, tcol);
                        int a1_row = 0;
                        int a2_row = 0;
                        int a1_col = 0;
                        int a2_col = 0;

                        int inc = 2;
                        if(part2 > 0)
                        {
                            inc = rows;
                            if(antennas == 0)
                            {
                                char* temp;
                                asprintf(&temp, "%i|%i", row, col);
                                if( pointer_list_contains(nodes_list, temp) > 0 )
                                {
                                    ylogd("rejected %s antenna due to already being in the list", temp);
                                }
                                else
                                {
                                    ylogd("adding %s antenna to the list", temp);
                                    pointer_list_append(nodes_list, o_strdup(temp));
                                    nodes++;
                                }
                                free(temp);
                            }
                            if(antennas >= 0)
                            {
                                char* temp1;
                                asprintf(&temp1, "%i|%i", trow, tcol);
                                if( pointer_list_contains(nodes_list, temp1) > 0 )
                                {
                                    ylogd("rejected %s antenna due to already being in the list", temp1);
                                }
                                else
                                {
                                    ylogd("adding %s antenna to the list", temp1);
                                    pointer_list_append(nodes_list, o_strdup(temp1));
                                    nodes++;
                                }
                                free(temp1);
                            }
                        }

                        ylogd("searching for noes %i deep", inc);
                        for(int j = 1; j<inc; j++)
                        {
                            //a1 backwards node
                            a1_row = row - ((trow - row)*j);
                            a2_row = trow + ((trow - row)*j);
                            if(tcol >= col)
                            {
                                a1_col = col - ((tcol - col)*j);
                                a2_col = tcol + ((tcol - col)*j);
                            }
                            if(tcol < col)
                            {
                                a1_col = col + ((col - tcol)*j);
                                a2_col = tcol - ((col - tcol)*j);
                            }

                            ylogd("calculated node positions of %i,%i and %i,%i", a1_row, a1_col, a2_row, a2_col);

                            if((a1_row) < 0 || a1_col < 0 || (a1_col) > (cols-1) || a1_row > (rows-1))
                            {
                                ylogd("rejected first node due to being out of bounds");

                            }
                            else
                            {
                                char* temp;
                                asprintf(&temp, "%i|%i", a1_row, a1_col);
                                if( pointer_list_contains(nodes_list, temp) > 0 )
                                {
                                    ylogd("rejected first node due to already being in the list");
                                }
                                else
                                {
                                    pointer_list_append(nodes_list, o_strdup(temp));
                                    nodes++;
                                }
                                free(temp);
                            }

                            if((a2_row) < 0 || a2_col < 0 || (a2_col) > (cols-1) || a2_row > (rows-1))
                            {
                                ylogd("rejected second node due to being out of bounds");
                            }
                            else
                            {
                                char* temp;
                                asprintf(&temp, "%i|%i", a2_row, a2_col);
                                if( pointer_list_contains(nodes_list, temp) > 0 )
                                {
                                    ylogd("rejected second node due to already being in the list");
                                }
                                else
                                {
                                    pointer_list_append(nodes_list, o_strdup(temp));
                                    nodes++;
                                }
                                free(temp);
                            }
                            antennas++;
                        }
                    }
                }
                k++;
                tcol++;
                if((k % rowsize) == 0)
                {
                    trow++;
                }
                if(tcol == (cols))
                {
                    tcol = 0;
                }
            }
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

    return nodes;
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

    int a1 = 0;
    int a2 = 0;

    // to get this run
    // tr --delete '\n' < advent06.txt > advent06_nonewlines.txt
    //char* str = fileslurp("advent08_sample.txt");
    char* str = fileslurp("advent08_nonewlines.txt");

    struct _pointer_list * antennas_nodes_list1 = o_malloc(sizeof(struct _pointer_list));
    pointer_list_init(antennas_nodes_list1);

    struct _pointer_list * antennas_nodes_list2 = o_malloc(sizeof(struct _pointer_list));
    pointer_list_init(antennas_nodes_list2);

    a1 = mapantennas(str, antennas_nodes_list1, ROWS, COLS, ROWSIZE, COLSIZE, 0);
    a2 = mapantennas(str, antennas_nodes_list2, ROWS, COLS, ROWSIZE, COLSIZE, 1);

    ylogi("found %i antinodes", a1);
    ylogi("found %i antinodes taking into account resonant frequencies", a2);

    for(int e = 0; e < pointer_list_size(antennas_nodes_list1); e++)
    {
        free(pointer_list_get_at(antennas_nodes_list1, e));
    }
    for(int e = 0; e < pointer_list_size(antennas_nodes_list2); e++)
    {
        free(pointer_list_get_at(antennas_nodes_list2, e));
    }
    pointer_list_clean(antennas_nodes_list1);
    pointer_list_clean(antennas_nodes_list2);
    o_free(antennas_nodes_list1);
    o_free(antennas_nodes_list2);
    free(str);
    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
