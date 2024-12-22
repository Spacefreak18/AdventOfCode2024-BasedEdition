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

#define PROGNAME "advent18"

#define ROWS 71
#define COLS 71
#define ROWSIZE 71
#define COLSIZE 71
//#define ROWS 7
//#define COLS 7
//#define ROWSIZE 7
//#define COLSIZE 7

//#define SIMBYTES 12
#define SIMBYTES 1024

int rowDirs[] = {-1, 1, 0, 0};
int colDirs[] = {0, 0, -1, 1};
int maze[ROWS][COLS];
int dist[ROWS][COLS];
int points[4096][2];

typedef struct
{
    int x;
    int y;
    int dir;
    int dist;
} Point;

typedef struct
{
    Point* arr;
    int size;
} MinHeap;

// Function to create a min-heap
MinHeap* createMinHeap(int size)
{
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (Point*)malloc(size * sizeof(Point));
    heap->size = 0;
    return heap;
}

// Swap two points in the min-heap
void swap(Point* a, Point* b)
{
    Point temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left].dist < heap->arr[smallest].dist)
    {
        smallest = left;
    }
    if (right < heap->size && heap->arr[right].dist < heap->arr[smallest].dist)
    {
        smallest = right;
    }

    if (smallest != idx)
    {
        swap(&heap->arr[idx], &heap->arr[smallest]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap* heap, Point p)
{
    ylogd("heap size is %i", heap->size);
    heap->arr[heap->size] = p;
    int idx = heap->size++;

    while (idx > 0 && heap->arr[(idx - 1) / 2].dist > heap->arr[idx].dist)
    {
        swap(&heap->arr[(idx - 1) / 2], &heap->arr[idx]);
        idx = (idx - 1) / 2;
    }
    minHeapify(heap, 0);
}

Point extractMin(MinHeap* heap)
{
    if (heap->size == 0)
    {
        return (Point){-1, -1, -1, -1};
    }

    Point min = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    minHeapify(heap, 0);
    return min;
}

bool isValidMove(int x, int y, int visited[ROWS][COLS])
{
    if(maze[x][y] == 0 && x > -1 && y > -1)
    {
        return true;
    }
    return false;
}

// Dijkstra's Algorithm to find the shortest path
int dijkstra(int startX, int startY, int endX, int endY)
{


    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            dist[i][j] = INT_MAX;
        }
    }

    MinHeap* heap = createMinHeap(ROWS * COLS);

    dist[startX][startY] = 0;
    insertMinHeap(heap, (Point){startX, startY, 0, 0});

    // While the heap is not empty
    while (heap->size > 0)
    {

        Point current = extractMin(heap);
        int x = current.x, y = current.y, dir = current.dir;
        ylogd("at point %i %i", x, y);

        // If we reach the destination, stop
        if (x == endX && y == endY)
        {
            ylogd("maze end found %i %i", x, y);
            free(heap->arr);
            free(heap);
            return dist[x][y];
        }


        for (int i = 0; i < 4; i++)
        {
            int newDir = i;
            int newX = x + rowDirs[i];
            int newY = y + colDirs[i];

            int newDist = dist[x][y] + 1;


            if (isValidMove(newX, newY, dist) == true)
            {
                if (newDist < dist[newX][newY])
                {
                    dist[newX][newY] = newDist;
                    insertMinHeap(heap, (Point) {newX, newY, newDir, newDist});
                }
            }
        }

    }

    ylogd("heap exhausted");
    free(heap->arr);
    free(heap);
    return -1;
}





int findend(char* puzzle, int rows, int cols, int rowsize, int colsize)
{
    int i =0;
    int end = 0;
    while(i < (rows * cols))
    {
        if(puzzle[i] == 'E')
        {
            end = i;
            ylogd("found ending position %i", i);
        }
        i++;
    }

    return end;
}

int findstart(char* puzzle, int rows, int cols, int rowsize, int colsize)
{
    int i =0;
    int start = 0;
    while(i < (rows * cols))
    {
        if(puzzle[i] == 'S')
        {
            start = i;
            ylogd("found starting position %i", i);
        }
        i++;
    }

    return start;
}

void mazify(char* puzzle, int rows, int cols, int rowsize)
{
    for(int i = 0; i < (rows*cols); i++)
    {
        int row = i / rowsize;
        int col = i % rowsize;
        if(puzzle[i] == '#')
        {
            maze[row][col] = 1;
        }
        if(puzzle[i] == '.')
        {
            maze[row][col] = 0;
        }
        if(puzzle[i] == 'E')
        {
            maze[row][col] = 0;
        }
        if(puzzle[i] == 'S')
        {
            maze[row][col] = 0;
        }
    }
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

    // to get this run
    // tr --delete '\n' < advent06.txt > advent06_nonewlines.txt
    FILE* file = fopen("advent18.txt", "r"); /* should check the result */
    //FILE* file = fopen("advent18_sample.txt", "r"); /* should check the result */


    char** returnstring1;
    int px = 0;
    int py = 0;
    int memory = 0;
    char line[512];
    while (fgets(line, sizeof(line), file))
    {
        size_t sz1 = split_string(line, ",", &returnstring1);

        px = atoi(returnstring1[0]);
        py = atoi(returnstring1[1]);
        ylogd("setting point at %i,%i", px, py);
        points[memory][0] = py;
        points[memory][1] = px;

        free_string_array(returnstring1);
        memory++;
    }
    fclose(file);

    int i = 0;
    while(i < SIMBYTES)
    {
        py = points[i][0];
        px = points[i][1];
        maze[py][px] = 1;
        i++;
    }
    ylogd("finished setting up maze");


    ylogi("starting at %i,%i and ending at %i,%i", 0, 0, ROWS-1, COLS-1);
    int shortestPath = dijkstra(0, 0, ROWS-1, COLS-1);

    int ret = shortestPath;
    while(ret != -1)
    {
        py = points[i][0];
        px = points[i][1];
        maze[py][px] = 1;
        ylogd("retrying maze");
        ret = dijkstra(0, 0, ROWS-1, COLS-1);
        ylogd("path still solvable with %i steps %i", ret, i);
        i++;
    }


    //for(int i = 0; i < ROWS; i++)
    //{
    //    for(int j = 0; j < COLS; j++)
    //        printf("%i", maze[i][j]);
    //    printf("\n");
    //}



    ylogi("found minimum steps of %i in shortest path", shortestPath);
    ylogi("coordinates which first block the exit are %i,%i", px, py);

    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
