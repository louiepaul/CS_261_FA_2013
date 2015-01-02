#include "dynamicArray.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*  VISUAL STUDIO (VS) USERS: COMMENT OUT THE LINE BELOW
    TO EXCLUDE THE MEMORY TEST CODE.
*/
#define MEMORY_TEST_INCLUDED

#ifdef MEMORY_TEST_INCLUDED
/* This header is needed for memory usage calculation. */
#include <sys/resource.h>

/* Function to get current memory usage in KB (Max Resident Set Size) */
long getMemoryUsage() {
    int who = RUSAGE_SELF;
    struct rusage usage;
    int ret;
    ret = getrusage(who, &usage);
    return usage.ru_maxrss;
}
#endif

/*Function to get number of milliseconds elapsed since program started execution*/
double getMilliseconds() {
   return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){
    DynArr* b;

    #ifdef MEMORY_TEST_INCLUDED
    /* variables to hold memory used before and after creating DynArr */
    long m1, m2;
    /* memory used BEFORE creating DynArr */
    m1 = getMemoryUsage();
    #endif

    b = createDynArr(1000);

    if( argc != 2 ) return 0;
    int n = atoi(argv[1]);/*number of elements to add*/
    int i;
    for( i = 0 ; i < n; i++)
        addDynArr(b, (TYPE)i);/*Add elements*/

    #ifdef MEMORY_TEST_INCLUDED
    /* memory used AFTER creating DynArr */
    m2 = getMemoryUsage();
    printf("Memory used by DynArr: %ld KB \n", m2-m1);
    #endif

    double t1 = getMilliseconds();/*Time before contains()*/

    for(i=0; i<n; i++)
        containsDynArr(b, i);

    double t2 = getMilliseconds();/*Time after contains()*/

    printf("Time for running containsDynArr() on %d elements:  %g\n", n, t2-t1);

    /*  delete the dynamic array */
    deleteDynArr(b);

    return 0; }
