#include "allinc.h"

namespace {
    struct ArrayElement {
        ngx_str_t name;
        ngx_str_t url;
        int id;
    };
}


/*
* 
*/
TEST_UNIT_P(ngx_array) {
    ngx_array_t* a = ngx_array_create(pool, 10, sizeof(ArrayElement));

    H_TEST_ASSERT(a->nalloc == 10);
    H_TEST_ASSERT(a->size == sizeof(ArrayElement));

    // Add one element to the array
    ArrayElement* u = (ArrayElement*)ngx_array_push(a);
    u->name.data = (u_char*)ngx_pcalloc(pool, 32);
    strcpy((char*)u->name.data, "CodeG");
    u->name.len = strlen("CodeG");
    ngx_str_set(&u->url, "http://blog.codeg.cn/2015/01/03/ngx_array_t");
    u->id = 0;
    H_TEST_ASSERT(a->nelts == 1);
    H_TEST_ASSERT(a->elts == u); // elts指向数组的首地址，因此与第一个数组元素地址相同

    // Add another one element to the array
    u = (ArrayElement*)ngx_array_push(a);
    u->name.data = (u_char*)ngx_pcalloc(pool, 32);
    strcpy((char*)u->name.data, "zieckey");
    u->name.len = strlen("zieckey");
    ngx_str_set(&u->url, "http://blog.codeg.cn/2014/12/13/Hello-CodeG");
    u->id = 1;
    H_TEST_ASSERT(a->nelts == 2);

    // Add 3rd element to the array
    u = (ArrayElement*)ngx_array_push(a);
    u->name.data = (u_char*)ngx_pcalloc(pool, 32);
    strcpy((char*)u->name.data, "zieckey");
    u->name.len = strlen("zieckey");
    ngx_str_set(&u->url, "https://github.com/zieckey");
    u->id = 2;
    H_TEST_ASSERT(a->nelts == 3);

    // Traversal the array
    for (ngx_uint_t i = 0; i < a->nelts; ++i) {
        u = (ArrayElement*)((char*)a->elts + sizeof(ArrayElement)*i);
        H_TEST_ASSERT(u->id == (int)i);
        printf("id=%d name=[%s] url=[%s]\n", u->id, (char*)u->name.data, (char*)u->url.data);
    }

    ngx_array_destroy(a);
}
