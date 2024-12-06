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

#define PROGNAME "advent02"

int passes(struct _pointer_list* p)
{
    int i = 0;
    while(i < pointer_list_size(p)-1)
    {
    	int temp1 = atoi(pointer_list_get_at(p, i));
    	int temp2 = atoi(pointer_list_get_at(p, i+1));
	if(temp1 == temp2)
    	{
    	    return i+1;
    	}
    	if(abs(temp2 - temp1) > 3)
    	{
	   return i+1;
    	}
    	i++;
    }
    return 0;
}

int issorted(struct _pointer_list* p)
{
    bool inc = false;
    int i = 0;
    while(i < pointer_list_size(p)-1)
    {
    	int temp1 = atoi(pointer_list_get_at(p, i));
    	int temp2 = atoi(pointer_list_get_at(p, i+1));
    	if(i == 0 && temp2 > temp1)
    	{
	   inc = true;
	}
	if(inc == true)
	{
	    if(temp2 < temp1)
	    {
	    	return i+1;
	    }
	}
	else
	{
	    if(temp2 > temp1)
	    {
	    	return i+1;
	    }
	}
	i++;
    }
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



    FILE* file = fopen("advent02.txt", "r"); /* should check the result */
    //FILE* file = fopen("advent02sample.txt", "r"); /* should check the result */
    char line[256];

    int i = 0;
    int j = 1;
    int passing = 0;
    // set maxfails to 0 for part 1 answer, to 1 for part 2 answer
    int maxfails = 1;

    char** returnstring;
    while (fgets(line, sizeof(line), file))
    {
	size_t sz = split_string(line, " ", &returnstring);

	struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
	pointer_list_init(pointer_list);
	int q = 0;
	while(q < sz)
	{
	    pointer_list_append(pointer_list, returnstring[q]);
	    q++;
	}

	bool fail = false;
	ylogd("testing list %i", j);
	if(issorted(pointer_list) == 0 && passes(pointer_list) == 0)
	{
	    ylogd("list %i passes", j);
	    fail = false;
	}
	else
	{
	    if(maxfails == 0)
		continue;

	    fail = true;
	    int a = issorted(pointer_list);
	    int b = passes(pointer_list);
	    ylogd("is sorted %i", a);
	    ylogd("is psses %i", b);

	    int use = 0;
	    if(a > 0)
	    {
	    	use = a;
	    }
	    else
	    {
	    	use = b;
	    }
	    if( b > 0 && b < use )
	    {
	    	use = b;
	    }
	    use--;

	    struct _pointer_list * pointer_list1 = pointer_list_clone(pointer_list);
	    struct _pointer_list * pointer_list2 = pointer_list_clone(pointer_list);
	    // remove current
	    if(fail == true)
	    {
	    	pointer_list_remove_at(pointer_list1, use);
		ylogd("removing position %i", use);
	    	if( issorted(pointer_list1) == 0 && passes(pointer_list1) == 0)
	    	{
	    	    ylogd("now %i passes", j);
	    		fail = false;
	    	}
	    	else
	    	{
	    		ylogd("still fails");
	    	}
	    }
	    pointer_list_clean(pointer_list1);
	    o_free(pointer_list1);

	    // remove 1 above
	    if(fail == true)
	    {
		pointer_list_remove_at(pointer_list2, use+1);
		ylogd("removing position %i", use+1);
		if(issorted(pointer_list2) == 0 && passes(pointer_list2) == 0)
	    	{
	    	    ylogd("now %i passes", j);
	    	    fail = false;
	    	}
		else
		{
		   ylogd("still fails");
		}
	    }
	    pointer_list_clean(pointer_list2);
	    o_free(pointer_list2);

	    // remove 1 below
	    if(fail == true && use > 0)
	    {
		pointer_list_remove_at(pointer_list, use-1);
		ylogd("removing position %i", use-1);
		if(issorted(pointer_list) == 0 && passes(pointer_list) == 0)
	    	{
		    ylogd("now %i passes", j);
		    fail = false;
	    	}
		else
		{
		   ylogd("still fails");
		}
	    }
	}

	if(fail == false)
	{
	    passing++;
	    ylogd("line %i passes", j);
	}
	j++;
	free_string_array(returnstring);
	pointer_list_clean(pointer_list);
	o_free(pointer_list);
    }
    fclose(file);


    ylogi("There are %i passing reports", passing);

    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();

    return 0;
}
