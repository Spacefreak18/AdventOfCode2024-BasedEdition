#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent01"

int comp (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main(int argc, char** argv) {

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

    //int sz = 6;
    int sz = 1000;
    int list1[sz];
    int list2[sz];

    FILE* file = fopen("advent01.txt", "r"); /* should check the result */
    //FILE* file = fopen("advent01sample.txt", "r"); /* should check the result */
    char line[256];

    int i = 0;
    int j = 0;

    char** returnstring;

    while (fgets(line, sizeof(line), file))
    {
	size_t sz = split_string(line, "   ", &returnstring);

	ylogd("split into size %i", sz);
	ylogd("%i", atoi(returnstring[0]));
	ylogd("%i", atoi(returnstring[1]));
	list1[i] = atoi(returnstring[0]);
	list2[i] = atoi(returnstring[1]);
	i++;
	free_string_array(returnstring);
    }
    fclose(file);

    qsort (list1, sizeof(list1)/sizeof(*list1), sizeof(*list1), comp);
    qsort (list2, sizeof(list2)/sizeof(*list2), sizeof(*list2), comp);

    int sum = 0;
    for (int i = 0 ; i < sz ; i++)
    {
        sum = sum + abs(list1[i] - list2[i]);
    }

    uint64_t a = 0;
    i = 0;
    j = 0;
    for(int i = 0; i < sz; i++)
    {
    	int b = 0;
    	for(int j = 0; j < sz; j++)
    	{
	    if(list1[i] == list2[j])
	    {
	    	b++;
		ylogd("matched %i %i times", list1[i], b);
	    }
    	}

    	a = a + (list1[i] * b);
    }


    ylogi("sum1 : %i", sum);
    ylogi("similarity score : %ld", (long) a);

    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);

    y_close_logs();
    return 0;
}
