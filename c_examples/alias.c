/*
 * Copyright (c) 2018 PolySync.
 *
 * Aliasing that results in unsafe memory access.
 */

#include <stdlib.h>
#include <stdint.h>

/* Basic types disallowed. */
typedef signed int SINT_32;

/* Example data, arbitrary. */
typedef struct { int32_t tux; int32_t baz; int32_t bar; } example_s;

/* Corrupts input. */
static void black_box(example_s ** alias_to_alias)
{
    if (alias_to_alias != NULL)
    {
        /* Data corrupted. */
        *alias_to_alias += 2048;
    }
}

SINT_32 main(void)
{
    /* Example data. */
    example_s data = {.tux = 1, .baz = 2, .bar = 3};
    /* Mutable alias to example data. */
    example_s * alias = &data;
    /* Mutable alias to alias. */
    example_s ** alias_to_alias = &alias;
    /* All values must be used. */
    int32_t return_value = alias->tux + alias->baz + alias->bar;

    /* Corrupts alias to data. */
    black_box(alias_to_alias);

    /* All values must be used. */
    if ((return_value != 0) && (alias_to_alias != NULL))
    {
        /* Use alias after corruption. */
        alias->tux = 4;
        alias->baz = 5;
        alias->bar = 6;

        /* All values must be used. */
        return_value = alias->tux + alias->baz + alias->bar;
    }

    /* All values must be used. */
    return (SINT_32)return_value;
}
