#include "test_common.h"

#include "pool/cg_pool.h"

TEST_UNIT(cg_pool) {
    ngx_pool_t* pool = ngx_create_pool(1024);
    char* p = (char*)ngx_palloc(pool, 32);
    const char* s = "hello world\n";
    strcpy(p, s);
    H_TEST_ASSERT(strcmp(p, s) == 0);

    p = (char*)ngx_palloc(pool, 4096); // alloc a large block

    ngx_destroy_pool(pool);
}
