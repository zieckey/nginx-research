
#include "allinc.h"

static ngx_str_t names[] = { 
        ngx_string("zieckey"),
        ngx_string("codeg"),
        ngx_string("jane") };

static char* descs[] = { "zieckey's id is 1", "codeg's id is 2", "jane's id is 3" };

// hash table的一些基本操作
TEST_UNIT(ngx_hash)
{
    ngx_uint_t          k; //, p, h;
    ngx_pool_t*         pool = g_pool;
    ngx_hash_init_t     hash_init;
    ngx_hash_t*         hash;
    ngx_array_t*        elements;
    ngx_hash_key_t*     arr_node;
    char*               find;
    int                 i;

    //ngx_cacheline_size = 32;

    // hash key cal start
    ngx_str_t str = ngx_string("hello, world");
    k = ngx_hash_key_lc(str.data, str.len);
    printf("calculated key is %u \n", k);
    // hask key cal end
    //
    hash = (ngx_hash_t*)ngx_pcalloc(pool, sizeof(ngx_hash_t));
    hash_init.hash = hash;                      // hash结构
    hash_init.key = &ngx_hash_key_lc;          // hash算法函数
    hash_init.max_size = 1024 * 10;                   // max_size
    hash_init.bucket_size = 64; // ngx_align(64, ngx_cacheline_size);
    hash_init.name = "yahoo_guy_hash";          // 在log里会用到
    hash_init.pool = pool;                 // 内存池
    hash_init.temp_pool = NULL;

    // 创建数组
    elements = ngx_array_create(pool, 32, sizeof(ngx_hash_key_t));
    for (i = 0; i < 3; i++) {
        arr_node = (ngx_hash_key_t*)ngx_array_push(elements);
        arr_node->key = (names[i]);
        arr_node->key_hash = ngx_hash_key_lc(arr_node->key.data, arr_node->key.len);
        arr_node->value = (void*)descs[i];
        // 
        printf("key: %s , key_hash: %u\n", arr_node->key.data, arr_node->key_hash);
    }

    if (ngx_hash_init(&hash_init, (ngx_hash_key_t*)elements->elts, elements->nelts) != NGX_OK){
        return ;
    }

    // 查找
    k = ngx_hash_key_lc(names[0].data, names[0].len);
    printf("%s key is %d\n", names[0].data, k);
    find = (char*)
        ngx_hash_find(hash, k, (u_char*)names[0].data, names[0].len);

    if (find) {
        printf("get desc of rainx: %s\n", (char*)find);
    }

    ngx_array_destroy(elements);

}
