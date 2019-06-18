/*
 * Copyright (c) 2018 PolySync.
 *
 * Const aliasing that results in unsafe memory access.
 */

#include <stdlib.h>
#include <stdint.h>

/* Basic types disallowed. */
typedef signed int SINT_32;

/* Example data, arbitrary. */
typedef struct { int32_t tux; int32_t baz; int32_t bar; } example_s;

/* Corrupts input. */
static void black_box(const example_s * const * alias_to_alias)
{
    if (alias_to_alias != NULL)
    {
        /* Cast away const to corrupt data. */
        *((example_s **)(alias_to_alias)) += 2048;
    }
}

SINT_32 main(void)
{
    /* Example data. */
    example_s data = {.tux = 1, .baz = 2, .bar = 3};
    /* Constant alias to example data. */
    const example_s * const alias = &data;
    /* Constant alias to alias. */
    const example_s * const * alias_to_alias = &alias;
    /* All values must be used. */
    int32_t return_value = alias->tux + alias->baz + alias->bar;

    /* Corrupts constant alias to data. */
    black_box(alias_to_alias);

    /* All values must be used. */
    if (alias_to_alias != NULL)
    {
        /* Dereference corrupted data. */
        example_s mutable_alias = *alias;

        if (return_value != 0)
        {
            /* Update corrupted dereference. */
            mutable_alias.tux += 4;
            mutable_alias.baz += 5;
            mutable_alias.bar += 6;

            /* All values must be used. */
            return_value =
                mutable_alias.tux + mutable_alias.baz + mutable_alias.bar;
        }
        else
        {
            /* All values must be used. */
            return_value =
                mutable_alias.tux + mutable_alias.baz + mutable_alias.bar;
        }
    }

    /* All values must be used. */
    return (SINT_32)return_value;
}
