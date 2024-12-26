#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent22"

uint64_t prune_factor = 16777216;

uint64_t prune(uint64_t input)
{
    return input % prune_factor;
}

uint64_t mix(uint64_t input1, uint64_t input2)
{
    return input1 ^ input2;
}

//uint64_t calcsecret(uint64_t secret)
//{
//    uint64_t step1 = secret * 64;
//    step1 = mix(secret, step1);
//    step1 = prune(step1);
//
//    ylogd("start %llu", secret);
//    uint64_t step2 = floor((double) secret / 32);
//    ylogd("start %llu", step2);
//    step2 = mix(step2, secret);
//    step2 = prune(step2);
//
//    uint64_t step3 = secret * 2048;
//    step3 = mix(step3, secret);
//    step3 = prune(step3);
//
//    return step3;
//}

uint64_t calcsecret(uint64_t secret)
{
    secret = prune(mix( secret * 64, secret ));
    secret = prune(mix( floor((double) secret / 32), secret ));
    secret = prune(mix( secret * 2048, secret ));
    return secret;
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

    FILE* file = fopen("advent22.txt", "r"); /* should check the result */
    //FILE* file = fopen("advent22_sample.txt", "r"); /* should check the result */


    //char comps[computers][3];
    //char** returnstring1;
    //int px = 0;
    //int py = 0;
    //int memory = 0;
    char line[512];
    uint64_t sum = 0;
    while (fgets(line, sizeof(line), file))
    {
        uint64_t x = strtoull(line, NULL, 10);
        for(int i = 0; i < 2000; i++)
        {
            x = calcsecret(x);
        }
        //ylogd("found 2000th secret %llu", x);
        sum = sum + x;
    }
    fclose(file);



    free(p);
    ylogi("found 2000th secret number sum %llu", sum);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
