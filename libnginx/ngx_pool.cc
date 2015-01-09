#include "allinc.h"

ngx_pool_t* g_pool;

struct NgxPoolInit {
    NgxPoolInit() {
        g_pool = ngx_create_pool(1024, NULL);
    }

    ~NgxPoolInit() {
        ngx_destroy_pool(g_pool);
    }
} __g_pool_initializer;

TEST_UNIT(ngx_pool) {
    ngx_pool_t* pool = ngx_create_pool(1024, NULL);
    char* p = (char*)ngx_palloc(pool, 32);
    const char* s = "hello world\n";
    strcpy(p, s);
    H_TEST_ASSERT(strcmp(p, s) == 0);

    p = (char*)ngx_palloc(pool, 4096); // alloc a large block

    ngx_destroy_pool(pool);
}

TEST_UNIT(ngx_pool_error) {
    //size_t size = sizeof(ngx_pool_t)+4; // [ sizeof(ngx_pool_t), sizeof(ngx_pool_t)+sizeof(ngx_pool_large_t) )
    size_t size = 1024;
    ngx_pool_t* pool = ngx_create_pool(size, NULL);
    char* p = (char*)ngx_palloc(pool, 32);
    const char* s = "hello world\n";
    strcpy(p, s);
    H_TEST_ASSERT(strcmp(p, s) == 0);

    p = (char*)ngx_palloc(pool, 4096); // alloc a large block

    ngx_destroy_pool(pool);
}

