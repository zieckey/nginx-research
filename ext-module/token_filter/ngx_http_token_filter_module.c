
/*
* Copyright (C) Igor Sysoev
*/


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct {
    ngx_uint_t        deny;      /* unsigned  deny:1; */
} ngx_http_token_filter_rule_t;

typedef struct {
    ngx_array_t      *rules;     /* array of ngx_http_token_filter_rule_t */
} ngx_http_token_filter_loc_conf_t;


static ngx_int_t ngx_http_token_filter_handler(ngx_http_request_t *r);

static char *ngx_http_token_filter_rule(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static void *ngx_http_token_filter_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_token_filter_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);
static ngx_int_t ngx_http_token_filter_init(ngx_conf_t *cf);

static ngx_command_t  ngx_http_token_filter_commands[] = {

    { ngx_string("token_filter"),
    NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LMT_CONF
    | NGX_CONF_NOARGS | NGX_CONF_TAKE1,
    ngx_http_token_filter_rule,
    NGX_HTTP_LOC_CONF_OFFSET,
    0,
    NULL },

    ngx_null_command
};



static ngx_http_module_t  ngx_http_token_filter_module_ctx = {
    NULL,                                  /* preconfiguration */
    ngx_http_token_filter_init,                  /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */

    ngx_http_token_filter_create_loc_conf,       /* create location configuration */
    ngx_http_token_filter_merge_loc_conf         /* merge location configuration */
};


ngx_module_t  ngx_http_token_filter_module = {
    NGX_MODULE_V1,
    &ngx_http_token_filter_module_ctx,           /* module context */
    ngx_http_token_filter_commands,              /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_int_t
ngx_http_token_filter_handler(ngx_http_request_t *r)
{
    ngx_http_token_filter_loc_conf_t  *alcf;
    
    alcf = ngx_http_get_module_loc_conf(r, ngx_http_token_filter_module);

    //sample code
    if (ngx_strstr((const char*)r->uri.data, "token=xxx")) {
        return NGX_HTTP_FORBIDDEN;
    }

    return NGX_OK;
}

static char *
ngx_http_token_filter_rule(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_token_filter_loc_conf_t *alcf = conf;

    //ngx_int_t                 rc;
    ngx_str_t                *value;
    //ngx_http_token_filter_rule_t   *rule;
    
    value = cf->args->elts;

    //Add more logic code here
    
    return NGX_CONF_OK;
}


static void *
ngx_http_token_filter_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_token_filter_loc_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_token_filter_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    return conf;
}


static char *
ngx_http_token_filter_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_token_filter_loc_conf_t  *prev = parent;
    ngx_http_token_filter_loc_conf_t  *conf = child;

    if (conf->rules == NULL) {
        conf->rules = prev->rules;
    }

    return NGX_CONF_OK;
}


static ngx_int_t
ngx_http_token_filter_init(ngx_conf_t *cf)
{
    ngx_http_handler_pt        *h;
    ngx_http_core_main_conf_t  *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    h = ngx_array_push(&cmcf->phases[NGX_HTTP_ACCESS_PHASE].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }

    *h = ngx_http_token_filter_handler;

    return NGX_OK;
}
