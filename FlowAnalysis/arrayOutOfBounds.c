#include <stdio.h>
#include <stdlib.h>
#include "dbutil.h"

#define CACHE_SIZE 1000

Person* cache[CACHE_SIZE];

int32_t clip(int32_t n, int32_t l, int32_t h)
{
    return (n > h) ? h : ((n < l) ? l : n);
}


Person* selectPerson()
{
    int32_t id;
    printf("Please enter person id: \n");
    scanf("%d", &id);
   
    /* Uncomment to fix accessing out of bounds */
    /* id = clip(id, 0, CACHE_SIZE - 1); */
   
    if (cache[id] == 0) {
        cache[id] = retrievePersonFromDB(id);
    }
    return cache[id];
}

void clearCache(int32_t from_id, int32_t to_id)
{
    int32_t i;
    for (i = from_id; i <= to_id; i++) {
        if (cache[i] != 0) {
            free(cache[i]);
            cache[i] = 0;
        }
    }
}

void clearAllCache()
{
    clearCache(0, CACHE_SIZE /* -1 */ ); /* Uncomment to fix accessing out of bounds */
}
