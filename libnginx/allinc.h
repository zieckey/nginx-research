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

    // The global memory pool used in all of the unit test cases
    // It is defined in ngx_pool.cc
    extern ngx_pool_t* g_pool;

#ifdef __cplusplus
}
#endif

#include "test_common.h"

#endif