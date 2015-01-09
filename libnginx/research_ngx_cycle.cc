
#include "allinc.h"

TEST_UNIT_P(ngx_cycle)
{
    ngx_cycle_t* cycle = (ngx_cycle_t*)ngx_pcalloc(pool, sizeof(ngx_cycle_t));
    cycle->conf_ctx = (void****)ngx_pcalloc(pool, sizeof(void*)* 100);
    
    ngx_core_conf_t* ngx_core_conf = (ngx_core_conf_t*)ngx_pcalloc(pool, sizeof(ngx_core_conf_t));
    ((void**)cycle->conf_ctx)[0] = ngx_core_conf;

    void*** ngx_event_core_ctx = (void***)ngx_pcalloc(pool, sizeof(void*)* 100);
    ((void**)cycle->conf_ctx)[3] = ngx_event_core_ctx;
    
    ngx_event_conf_t* ngx_event_conf = (ngx_event_conf_t*)ngx_pcalloc(pool, sizeof(ngx_event_conf));
    ((void**)ngx_event_core_ctx)[0] = ngx_event_conf;
#ifdef WIN32
    ngx_iocp_conf_t* ngx_iocp_conf = (ngx_iocp_conf_t*)ngx_pcalloc(pool, sizeof(ngx_iocp_conf_t));
    ((void**)ngx_event_core_ctx)[3] = ngx_iocp_conf;
#endif

    void*** ngx_http_core_ctx = (void***)ngx_pcalloc(pool, sizeof(void*)* 100);
    ((void**)cycle->conf_ctx)[8] = ngx_http_core_ctx;
    ngx_http_conf_ctx_t* ngx_http_conf_ctx = (ngx_http_conf_ctx_t*)ngx_pcalloc(pool, sizeof(ngx_http_conf_ctx_t));
    ((void**)ngx_http_core_ctx)[0] = ngx_http_conf_ctx;

    ngx_http_conf_ctx->main_conf = (void**)ngx_pcalloc(pool, sizeof(void*)* 100);
    ngx_http_conf_ctx->srv_conf = (void**)ngx_pcalloc(pool, sizeof(void*)* 100);
    ngx_http_conf_ctx->loc_conf = (void**)ngx_pcalloc(pool, sizeof(void*)* 100);

    ngx_http_conf_ctx->main_conf[0] = ngx_pcalloc(pool, sizeof(ngx_http_core_main_conf_t));
    ngx_http_conf_ctx->srv_conf[0] = ngx_pcalloc(pool, sizeof(ngx_http_core_srv_conf_t));
    ngx_http_conf_ctx->loc_conf[0] = ngx_pcalloc(pool, sizeof(ngx_http_core_loc_conf_t));
}



