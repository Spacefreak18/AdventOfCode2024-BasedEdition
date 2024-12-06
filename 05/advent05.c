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

#define PROGNAME "advent05"

int getmiddle(struct _pointer_list* pages)
{
    int listsize = pointer_list_size(pages);
    int a = listsize/2;
    y_log_message(Y_LOG_LEVEL_DEBUG, "list size is %i middle is %i", listsize, a);
    return atoi(pointer_list_get_at(pages, a));
}

int checkorder(struct _pointer_list* pages, struct _pointer_list* rules)
{
    int found2 = 0;
    int rulessize = pointer_list_size(rules);

    int i = 0;
    char** returnstring;
    bool fail = false;
    while(i < rulessize)
    {
	size_t sz = split_string(pointer_list_get_at(rules, i), "|", &returnstring);
        int rule1 = atoi(returnstring[0]);
        int rule2 = atoi(returnstring[1]);

        y_log_message(Y_LOG_LEVEL_DEBUG, "checking rule %i|%i found at %i", rule1, rule2, i);
        int pagesize = pointer_list_size(pages);
        int j = pagesize-1;
        while(j > 0)
        {
            int found1 = 0;

            // found number with associated ordering
            void* test1 = pointer_list_get_at(pages, j);
            if(atoi(test1) == rule1)
            {
                y_log_message(Y_LOG_LEVEL_DEBUG, "found hit for rule with pos %i", j);
                found1++;
                int k = j-1;
                while(k >= 0)
                {
                    void* test2 = pointer_list_get_at(pages, k);
                    if(rule2 == atoi(test2))
                    {
                        y_log_message(Y_LOG_LEVEL_DEBUG, "found fail for rule with pos %i", k);

                        pointer_list_insert_at(pages, test2, j+1);
                        pointer_list_remove_at(pages, k);

                        found2++;

                        // force recheck of everything
                        j=pagesize-1;
                        i=0;
                    }
                    k--;
                }
            }
            j--;
            if(found1>0 && found2 == 0)
            {
                fail = true;
            }
        }

        i++;
        free_string_array(returnstring);
    }

    return found2;
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

    int a = 0;
    int aa = 0;
    int aaa = 0;

    //FILE* file = fopen("advent05sample_rules.txt", "r"); /* should check the result */
    //FILE* file2 = fopen("advent05sample_orders.txt", "r"); /* should check the result */
    FILE* file = fopen("advent05_rules.txt", "r"); /* should check the result */
    FILE* file2 = fopen("advent05_orders.txt", "r"); /* should check the result */

    char line[256];
    char line2[256];

    struct _pointer_list * rules_list = o_malloc(sizeof(struct _pointer_list));
    pointer_list_init(rules_list);


    while (fgets(line, sizeof(line), file))
    {
        pointer_list_append(rules_list, o_strdup(line));
    }
    fclose(file);


    int c = 1;
    char** returnstring;
    while (fgets(line2, sizeof(line2), file2))
    {
	    size_t sz = split_string(line2, ",", &returnstring);
	    int i =0;

            struct _pointer_list * pages_list = o_malloc(sizeof(struct _pointer_list));
            pointer_list_init(pages_list);
	    while(i < sz)
	    {
	        pointer_list_append(pages_list, returnstring[i]);
                i++;
	    }
	    i = 0;

            y_log_message(Y_LOG_LEVEL_DEBUG, "checking order of list %i", c);
            int b = checkorder(pages_list, rules_list);
            if(b == 0)
            {
                y_log_message(Y_LOG_LEVEL_DEBUG, "list %i is good", c);
                int h = getmiddle(pages_list);
                aa = aa + h;
                a++;
            }
            else
            {
                y_log_message(Y_LOG_LEVEL_DEBUG, "list %i is bad", c);

                int z = 0;
                while(z < pointer_list_size(pages_list))
                {
                    y_log_message(Y_LOG_LEVEL_DEBUG, "%i", atoi(pointer_list_get_at(pages_list, z)));
                    z++;
                }
                int h = getmiddle(pages_list);
                aaa = aaa + h;
                a++;
            }
	    free_string_array(returnstring);

	    pointer_list_clean(pages_list);
	    o_free(pages_list);
	    c++;
    }
    fclose(file2);

    int e = 0;
    while(e < pointer_list_size(rules_list))
    {
        free(pointer_list_get_at(rules_list, e));
        e++;
    }
    pointer_list_clean(rules_list);
    o_free(rules_list);

    y_log_message(Y_LOG_LEVEL_INFO, "found xmas %i times", a);
    y_log_message(Y_LOG_LEVEL_INFO, "sum of middles is %i", aa);
    y_log_message(Y_LOG_LEVEL_INFO, "sum of bad middles is %i", aaa);


    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    y_log_message(Y_LOG_LEVEL_INFO, "time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
