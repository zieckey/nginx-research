#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char*         buf;
    size_t        buflen;//the length of the buf
} ngx_http_helloworld_conf_t;

static char *ngx_http_helloworld_set(ngx_conf_t *cf, ngx_command_t *cmd, void*conf);

static void *ngx_http_helloworld_create_conf(ngx_conf_t *cf);

static ngx_command_t ngx_http_helloworld_commands[] =
{
    { ngx_string("helloworld_query"), //The command name, it MUST BE the same as nginx.conf location block's command

    NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
    ngx_http_helloworld_set,
    0,
    0,
    NULL },

    ngx_null_command
};

static ngx_http_module_t ngx_http_helloworld_module_ctx =
{
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    ngx_http_helloworld_create_conf, /* create location configuration */
    NULL  /* merge location configuration */
};

ngx_module_t ngx_http_helloworld_module =
{
    NGX_MODULE_V1,
    &ngx_http_helloworld_module_ctx, /* module context */
    ngx_http_helloworld_commands, /* module directives */
    NGX_HTTP_MODULE, /* module type */
    NULL, /* init master */
    NULL, /* init module */
    NULL, /* init process */
    NULL, /* init thread */
    NULL, /* exit thread */
    NULL, /* exit process */
    NULL, /* exit master */
    NGX_MODULE_V1_PADDING
};

static const char* getlocaltime(ngx_pool_t* pool)
{
    size_t buff_len = 32;
    char* buff = ngx_pcalloc(pool, buff_len);
    struct tm *pTime;
    time_t ctTime;
    time( &ctTime );
    pTime = localtime( &ctTime );

    snprintf( buff, buff_len, "%4d-%.2d-%.2d %.2d:%.2d:%.2d",
                pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday,
                pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
    return buff;
}

/**
 * Process the client request.
 * The client post data has stored in <code>r</code>
 */
static void helloworld_process_handler(ngx_http_request_t *r)
{
    ngx_int_t rc = NGX_OK;
    ngx_buf_t *b = NULL;
    ngx_chain_t out;

    ngx_http_helloworld_conf_t *conf = NULL;
    conf = (ngx_http_helloworld_conf_t *)ngx_http_get_module_loc_conf(r,ngx_http_helloworld_module);
    if (conf == NULL) {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }

    /* Prepare for output, 128 is preserved for robust */
    b = ngx_create_temp_buf( r->pool, 128 + conf->buflen );
    if (b == NULL) {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }
    out.buf = b;
    out.next = NULL;

    b->last = ngx_sprintf(b->pos, "%s\ncurrent: %s\n", conf->buf, getlocaltime(r->pool));

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = b->last - b->pos;
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *) "text/plain";

    b->last_buf = 1;/* there will be no more buffers in the request */

    rc = ngx_http_send_header(r);

    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }

    ngx_http_output_filter(r, &out);
    ngx_http_finalize_request(r, 0);
}

/**
 * Reading data handler
 * After read all the data from client we set a process handler
 */
static ngx_int_t
ngx_http_helloworld_handler(ngx_http_request_t *r)
{
    ngx_int_t rc = NGX_DONE;
    rc = ngx_http_read_client_request_body( r, helloworld_process_handler );
    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }

    return NGX_DONE;
}


/**
 * set the request reading data handler
 */
static char *
ngx_http_helloworld_set( ngx_conf_t *cf, ngx_command_t *cmd, void *conf )
{
    ngx_http_core_loc_conf_t *clcf;

    clcf = (ngx_http_core_loc_conf_t *)ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module);
    clcf->handler = ngx_http_helloworld_handler;

    return NGX_CONF_OK;
}


static void *
ngx_http_helloworld_create_conf(ngx_conf_t *cf)
{
    ngx_http_helloworld_conf_t *conf = NULL;
    const char* timebuff = getlocaltime(cf->pool);

    conf = (ngx_http_helloworld_conf_t *)ngx_pcalloc(cf->pool,sizeof(ngx_http_helloworld_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }

    conf->buf = ngx_pcalloc(cf->pool, 128);
    snprintf(conf->buf, 128, "startup: %s", timebuff);
    conf->buflen  = strlen(conf->buf);

    return conf;
}


