/*
 * Copyright (c) 2018 PolySync.
 *
 * Data race that results in unsafe memory access.
 */

#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

/* Basic types disallowed. */
typedef signed int SINT_32;
/* Basic types disallowed. */
typedef unsigned int UINT_32;

/* Prototypes always required. */
SINT_32 pthread_create(
    pthread_t * thread,
    const pthread_attr_t * attr,
    void * (*start_routine) (void *),
    void * arg);
/* Prototypes always required. */
SINT_32 pthread_join(
    pthread_t thread,
    void ** value_ptr);
/* Prototypes always required. */
UINT_32 sleep(UINT_32 seconds);

/* Example data, arbitrary. */
typedef struct { int32_t tux; int32_t baz; int32_t bar; } example_s;

/* Corrupts input. */
static void * black_box(void * const args)
{
    /* Reference to resource shared across thread_count. */
    example_s * alias = (example_s*)args;

    /* Arbitrary bound. */
    while ((alias != NULL) && (alias->tux < 10))
    {
        /* "Think" to simulate some ammount of work. */
        (void)sleep(0);

        /* If this occurs another thread has changed the shared resource. */
        if (alias->tux >= 10)
        {
            alias += 2048;
        }
        else
        {
            /* Increment potentially corrupted alias. */
            alias->tux += 1;
        }
    }

    /* Can't return NULL. */
    return (int32_t*)0;
}

SINT_32 main(void)
{
    /* Thread resource. */
    const uint32_t thread_count = (uint32_t)5U;
    /* Thread resource. */
    pthread_t tid[5U];

    /* Counter / array index. */
    uint64_t index;

    /* Declare and initialize a shared resource. */
    example_s data = {.tux = 1, .baz = 2, .bar = 3};
    /* Mutable alias to example data. */
    example_s * alias = &data;

    /* Set index for use in loop. */
    index = 0U;

    /* Spawn threads. */
    while (index < thread_count)
    {
        (void)pthread_create(&(tid[index]), NULL, &black_box, alias);
        index += 1U;
    }

    /* Reset index for use in next loop. */
    index = 0U;

    /* Allow threads to finish work. */
    while (index < thread_count)
    {
        (void)pthread_join(tid[index], NULL);
        index += 1U;
    }

    return (SINT_32)0;
}
