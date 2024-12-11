#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent11"

#define MEMSIZE 4096*4096

uint64_t mem[MEMSIZE][100];

uint64_t rblink(uint64_t a1, int n, int blinks)
{

    n++;
    if(n == (blinks+1))
        return 1;

    //ylogd("processing stone %s size is %i", stone, strlen(stone));
    uint64_t istone = a1;

    if(a1 < MEMSIZE && mem[a1][n] != 0)
    {
        return mem[a1][n];
    }

    if(istone == 0)
    {
        return rblink(1, n, blinks);
    }

    if(istone < 10)
    {
        return rblink(istone*2024, n, blinks);
    }

    int numdigits = (int)log10(istone) + 1;
    if (numdigits % 2 == 0)
    {
        int splitPoint = numdigits / 2;
        int divisor = pow(10, numdigits - splitPoint);

        uint64_t st1 = istone / divisor;
        uint64_t st2 = istone % divisor;
        if(a1 < MEMSIZE)
        {
            return mem[a1][n] = rblink(st1, n, blinks) + rblink(st2, n, blinks);
        }
        else
        {
            return rblink(st1, n, blinks) + rblink(st2, n, blinks);
        }
    }

    return rblink(istone*2024, n, blinks);
}

int blink(struct _pointer_list* stones)
{
    for(int i = 0; i < pointer_list_size(stones); i++)
    {
        char* stone = pointer_list_get_at(stones, i);

        //ylogd("processing stone %s size is %i", stone, strlen(stone));
        bool processed = false;
        uint64_t istone = strtoull(stone, NULL, 10);

        if(processed == false)
        {
            if(istone == 0)
            {
                istone = 1;
                char* temp;
                asprintf(&temp, "%lu", istone);
                pointer_list_remove_at_free(stones, i, &o_free);
                pointer_list_insert_at(stones, o_strdup(temp), i);
                free(temp);
                processed = true;
            }
        }
        if(processed == false)
        {
            if(strlen(stone) % 2 == 0)
            {
                //ylogd("original stone is %s size is %i", stone, strlen(stone));
                int newsize = strlen(stone)/2;
                //ylogd("newsize is %i", newsize);
                char str1[newsize+1];
                char str2[newsize+1];
                str1[newsize] = '\0';
                str2[newsize] = '\0';

                for(int k = 0; k < (strlen(stone)/2); k++)
                {
                        str1[k] = stone[k];
                        str2[k] = stone[k+newsize];
                }
                uint64_t st1 = strtoull(str1, NULL, 10);
                uint64_t st2 = strtoull(str2, NULL, 10);

                char* f1;
                char* f2;
                asprintf(&f1, "%lu", st1);
                asprintf(&f2, "%lu", st2);
                //ylogd("duplicated stones %s %s", f1, f2);

                pointer_list_remove_at_free(stones, i, &o_free);
                pointer_list_insert_at(stones, o_strdup(f1), i);
                i++;
                pointer_list_insert_at(stones, o_strdup(f2), i);

                free(f1);
                free(f2);
                processed = true;
            }
        }
        if(processed == false)
        {
            istone = istone * 2024;
            char* temp;
            asprintf(&temp, "%lu", istone);
            pointer_list_remove_at_free(stones, i, &o_free);
            pointer_list_insert_at(stones, o_strdup(temp), i);
            free(temp);
        }
    }

    return 0;
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

    //struct _pointer_list* stones = o_malloc(sizeof(struct _pointer_list));
    //pointer_list_init(stones);

    ////pointer_list_append(stones, o_strdup("125"));
    ////pointer_list_append(stones, o_strdup("17"));

    ////112 1110 163902 0 7656027 83039 9 74
    //pointer_list_append(stones, o_strdup("112"));
    //pointer_list_append(stones, o_strdup("1110"));
    //pointer_list_append(stones, o_strdup("163902"));
    //pointer_list_append(stones, o_strdup("0"));
    //pointer_list_append(stones, o_strdup("7656027"));
    //pointer_list_append(stones, o_strdup("83039"));
    //pointer_list_append(stones, o_strdup("9"));
    //pointer_list_append(stones, o_strdup("74"));


    uint64_t a = 0;
    int blinks = 25;
    if(p->part2 > 0)
    {
        blinks = 75;
    }

    //for(int i = 0; i < blinks; i++)
    //{
    //    a += blink(stones);
    //}

    //a += rblink(125, 0, blinks);
    //a += rblink(17, 0, blinks);
    a = rblink(112, 0, blinks);
    ylogi("1 stone");
    a += rblink(1110, 0, blinks);
    a += rblink(163902, 0, blinks);
    a += rblink(0, 0, blinks);
    a += rblink(7656027, 0, blinks);
    a += rblink(83039, 0, blinks);
    a += rblink(9, 0, blinks);
    a += rblink(74, 0, blinks);

    //int a = pointer_list_size(stones);
    //for(int e = 0; e < pointer_list_size(stones); e++)
    //{
    //    ylogd("stone: %s", pointer_list_get_at(stones, e));
    //}



    //for(int e = 0; e < pointer_list_size(stones); e++)
    //{
    //    free(pointer_list_get_at(stones, e));
    //}
    //pointer_list_clean(stones);
    //o_free(stones);


    free(p);
    ylogi("Found %llu stones after %llu blinks", a, blinks);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();

    return 0;
}
