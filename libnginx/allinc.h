#ifndef NGINX_RESEARCH_ALL_HEADERS_H_
#define NGINX_RESEARCH_ALL_HEADERS_H_

#ifdef __cplusplus
extern "C" {
#endif

    #include "ngx_config.h"
    #include "ngx_conf_file.h"
    #include "nginx.h"
    #include "ngx_core.h"
    #include "ngx_string.h"
    #include "ngx_string.h"
    #include "ngx_hash.h"
    #include "ngx_array.h"
    #include "ngx_list.h"
    #include "ngx_queue.h"
    #include "ngx_http.h"

    // The global memory pool used in all of the unit test cases
    // It is defined in ngx_pool.cc
    extern ngx_pool_t* g_pool;

#ifdef __cplusplus
}
#endif

#include "test_common.h"
#include "dump_nginx_struct.h"

#define TEST_UNIT_P(name)  \
class GtestObjectClass_##name : public testing::Test{ \
public: \
    GtestObjectClass_##name() {} \
    ~GtestObjectClass_##name() {} \
    virtual void SetUp() { pool = ngx_create_pool(1024, NULL); } \
    virtual void TearDown() { ngx_destroy_pool(pool); pool = NULL; } \
public:\
    ngx_pool_t* pool;\
}; \
TEST_F(GtestObjectClass_##name, name)

#endif