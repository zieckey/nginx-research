
/*
* Copyright (C) Igor Sysoev
*/


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct {
    ngx_array_t  *tokens;     /* array of ngx_str_t */
} ngx_http_token_filter_loc_conf_t;


static ngx_int_t ngx_http_token_filter_handler(ngx_http_request_t *r);

static char *ngx_http_token_filter_rule(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static void *ngx_http_token_filter_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_token_filter_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);
static ngx_int_t ngx_http_token_filter_init(ngx_conf_t *cf);

static ngx_command_t  ngx_http_token_filter_commands[] = {

    { ngx_string("token_filter"),
    NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LMT_CONF
    | NGX_CONF_TAKE1,
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
    ngx_str_t                         *token;
    ngx_uint_t                          i;

    alcf = ngx_http_get_module_loc_conf(r, ngx_http_token_filter_module);

    for (i = 0; i < alcf->tokens->nelts; i++) {

        token = &((ngx_str_t*)alcf->tokens->elts)[i];

        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
            "URL=[%V] token=[%V]",
            r->unparsed_uri, token);

        if (ngx_strnstr(r->unparsed_uri.data, (char*)token->data, 
            r->unparsed_uri.len)) {
            return NGX_HTTP_FORBIDDEN;
        }
    }


    return NGX_OK;
}

static void 
add_token(ngx_pool_t* pool, ngx_array_t* tokens, u_char* begin, size_t len)
{
    ngx_str_t* token = ngx_array_push(tokens);
    token->data = ngx_pcalloc(pool, len + 1);
    ngx_memcpy(token->data, begin, len);
    token->len = len;
}

static char *
ngx_http_token_filter_rule(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_token_filter_loc_conf_t *alcf = conf;

    ngx_str_t                *value;
    
    u_char                   *begin;
    u_char                   *end;
    char                     *separator;

    value = cf->args->elts;
    begin = value[1].data;
    end = begin + value[1].len;

    /*tokens are separated by a single space*/
    while (end > begin && (separator = memchr(begin, ' ', end - begin))) {
        //TODO FIXME fix the problem when multiple spaces together
        add_token(cf->pool, alcf->tokens, begin, separator - begin);
        begin = separator + 1;
    }

    if (begin < end) {
        add_token(cf->pool, alcf->tokens, begin, end - begin);
    }
    
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

    conf->tokens = ngx_array_create(cf->pool, 4, sizeof(ngx_str_t));
    if (conf->tokens == NULL) {
        return NGX_CONF_ERROR;
    }

    return conf;
}


static char *
ngx_http_token_filter_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_token_filter_loc_conf_t  *prev = parent;
    ngx_http_token_filter_loc_conf_t  *conf = child;

    if (conf->tokens == NULL) {
        conf->tokens = prev->tokens;
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
