#pragma once

#include "allinc.h"

inline void dump_pool(ngx_pool_t* pool)
{
    while (pool)
    {
        printf("pool = 0x%p\n", pool);
        printf("  .d\n");
        printf("    .last = 0x%p\n", pool->d.last);
        printf("    .end = 0x%p\n", pool->d.end);
        printf("    .next = 0x%p\n", pool->d.next);
        printf("    .failed = %d\n", pool->d.failed);
        printf("  .max = %d\n", pool->max);
        printf("  .current = 0x%p\n", pool->current);
        printf("  .chain = 0x%p\n", pool->chain);
        printf("  .large = 0x%p\n", pool->large);
        printf("  .cleanup = 0x%p\n", pool->cleanup);
        printf("  .log = 0x%p\n", pool->log);
        printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);
        pool = pool->d.next;
    }
}
