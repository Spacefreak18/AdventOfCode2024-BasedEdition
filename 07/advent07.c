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

#define PROGNAME "advent07"

int addormult(uint64_t* entries, int sized, int n, uint64_t a, int a1, int b)
{
    int total_permutations = 1 << (sized-1);
    if(b > 2)
    {
        total_permutations = pow(b, (sized-1));
    }

    ylogd("solving for %i %i permutations", sized-1, total_permutations);

    int* ops = malloc(total_permutations * sized * sizeof(int));
    for (int i = 0; i < total_permutations; i++)
    {
        int index = i;
        for (int j = 0; j < (sized-1); j++)
        {
            ops[i * (sized-1) + j] = index % b;
            index /= b;
        }
    }

    int i = 0;
    i = 0;
    while(i < (total_permutations*(sized)))
    {
        uint64_t sum = entries[0];
        for(int j = 0; j < (sized-1); j++)
        {
            if(ops[i] == 0)
            {
                sum = sum * entries[j+1];
            }
            if(ops[i]== 1)
            {
                sum = sum + entries[j+1];
            }
            if(ops[i] == 2)
            {
                char* temp;
                //ylogd("attempging to concat %llu %llu", sum, entries[j+1]);
                asprintf(&temp, "%lu%lu", sum, entries[j+1]);
                //ylogd("performed concat to get %s", temp);
                sum = strtoull(temp, NULL, 10);
                free(temp);
            }
            i++;
        }
        if(sum == a)
        {
            a1++;
        }
    }

    free(ops);
    return a1;
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


    //FILE* file = fopen("advent07sample.txt", "r"); /* should check the result */
    FILE* file = fopen("advent07.txt", "r"); /* should check the result */
    char line[512];

    int a1 = 0;
    uint64_t sum1 = 0;
    int a2 = 0;
    uint64_t sum2 = 0;

    char** returnstring;
    while (fgets(line, sizeof(line), file))
    {
        bool works = false;
        size_t sz = split_string(line, ":", &returnstring);
        char** entry;
        size_t sz1 = split_string(returnstring[1], " ", &entry);

        uint64_t answer = strtoull(returnstring[0], NULL, 10);

        sz1--;
        ylogd("testing %llu with %i numbers", answer, sz1);
        int b = 0;
        uint64_t* entries = malloc((sz1) * sizeof(uint64_t));
        while(b < sz1)
        {
            entries[b] = strtoull(entry[b+1], NULL, 10);
            b++;
        }

        int ans = addormult(entries, sz1, 1, answer, 0, 2);
        if(ans > 0)
        {
            ylogd("found way to get %llu", answer);
            a1++;
            sum1 = sum1 + answer;
        }

        ans = addormult(entries, sz1, 1, answer, 0, 3);
        if(ans > 0)
        {
            ylogd("found way to get %llu", answer);
            a2++;
            sum2 = sum2 + answer;
        }

        free(entries);
        free_string_array(entry);
        free_string_array(returnstring);
    }
    fclose(file);


    free(p);

    ylogi("Found %i possible operations using 2 possible operators", a1);
    ylogi("their answers add to %llu", sum1);
    ylogi("Found %i possible operations with 2 possible operators", a2);
    ylogi("their answers add to %llu", sum2);

    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();

    return 0;
}
