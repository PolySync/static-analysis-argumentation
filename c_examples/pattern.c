/*
 * Copyright (c) 2018 PolySync.
 *
 * Use of ambiguous enumeration that results in unsafe memory access.
 */

#include <stdlib.h>
#include <stdint.h>

/* Basic types disallowed. */
typedef signed int SINT_32;

/* Example data, arbitrary. */
typedef struct { int32_t tux; int32_t baz; int32_t bar; } example_s;

/* Enumeration intended for use. */
typedef enum { APPLY_BRAKE = 1, APPLY_THROTTLE = 2 } action_e;

/* Ambiguous enumeration that can results dangerous behavior. */
enum { DO_NOT_SELF_DESTRUCT = 1, SELF_DESTRUCT = 2, UNDECIDED = 3 };

/* Corrupts input. */
static void black_box(int32_t pattern, example_s ** status)
{
    /* Explicit check for pointer validity. */
    if (status != NULL)
    {
        /* Match on integer as anonymous enum value. */
        switch (pattern)
        {
            /* Destructive implications. */
            case DO_NOT_SELF_DESTRUCT: { break; }
            case SELF_DESTRUCT: { *status += 2048; break; }
            case UNDECIDED: { break; }
            default: { break; }
        }
    }
}

SINT_32 main(void)
{
    /* Indended application would be as an 'action_e' enum type. */
    action_e pattern = APPLY_THROTTLE;
    /* Example data. */
    example_s data = {.tux = 1, .baz = 2, .bar = 3};
    /* Mutable alias to example data. */
    example_s * alias = &data;
    /* Mutable alias to alias. */
    example_s ** alias_to_alias = &alias;
    /* All values must be used. */
    int32_t return_value = alias->tux + alias->baz + alias->bar;

    /* Corrupts alias to data. */
    black_box(pattern, alias_to_alias);

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
