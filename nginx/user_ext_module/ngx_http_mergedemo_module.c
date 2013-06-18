#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    ngx_pool_t  loc0;
    int         loc_conf_index;
    ngx_str_t   name;
    int         loc1;
} ngx_http_mergedemo_loc_conf_t;


typedef struct {
    ngx_array_t srv0;
    int         srv_conf_index;
    long        srv1;
    ngx_str_t   name;
    long        srv2;
} ngx_http_mergedemo_srv_conf_t;


typedef struct {
    ngx_str_t       main1;
    int             main_conf_index;
    int             main2;
    ngx_hash_init_t main4;
    ngx_str_t       name;
    ngx_str_t       main3;
} ngx_http_mergedemo_main_conf_t;

static char *ngx_http_mergedemo_set(ngx_conf_t *cf, ngx_command_t *cmd, void*conf);

static void *ngx_http_mergedemo_create_loc_conf(ngx_conf_t *cf);
static void *ngx_http_mergedemo_create_srv_conf(ngx_conf_t *cf);
static void *ngx_http_mergedemo_create_main_conf(ngx_conf_t *cf);

static char *ngx_http_mergedemo_init_main_conf(ngx_conf_t *cf, void *conf);

static char *ngx_http_mergedemo_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child);
static char *ngx_http_mergedemo_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);

static int main_conf_create_count = 0;
static int srv_conf_create_count = 0;
static int loc_conf_create_count = 0;
static int main_conf_init_count = 0;
static int srv_conf_merge_count = 0;
static int loc_conf_merge_count = 0;

static int ngx_http_mergedemo_set_count = 0;

static ngx_command_t ngx_http_mergedemo_commands[] =
{/*{{{*/
    { ngx_string("mergedemo_query"), //The command name, it MUST BE the same as nginx.conf location block's command

    //NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
    NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
    ngx_http_mergedemo_set,
    0,
    0,
    NULL },

    ngx_null_command
};/*}}}*/

static ngx_http_module_t ngx_http_mergedemo_module_ctx =
{/*{{{*/
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    ngx_http_mergedemo_create_main_conf, /* create main configuration */
    ngx_http_mergedemo_init_main_conf, /* init main configuration */

    ngx_http_mergedemo_create_srv_conf, /* create server configuration */
    ngx_http_mergedemo_merge_srv_conf, /* merge server configuration */

    ngx_http_mergedemo_create_loc_conf, /* create location configuration */
    ngx_http_mergedemo_merge_loc_conf /* merge location configuration */
};/*}}}*/

ngx_module_t ngx_http_mergedemo_module =
{/*{{{*/
    NGX_MODULE_V1,
    &ngx_http_mergedemo_module_ctx, /* module context */
    ngx_http_mergedemo_commands, /* module directives */
    NGX_HTTP_MODULE, /* module type */
    NULL, /* init master */
    NULL, /* init module */
    NULL, /* init process */
    NULL, /* init thread */
    NULL, /* exit thread */
    NULL, /* exit process */
    NULL, /* exit master */
    NGX_MODULE_V1_PADDING
};/*}}}*/

/**
* Process the client request.
* The client post data has stored in <code>r</code>
*/
static void mergedemo_process_handler(ngx_http_request_t *r)
{/*{{{*/
    ngx_int_t rc = NGX_OK;
    ngx_buf_t *b = NULL;
    ngx_chain_t out;


    ngx_http_mergedemo_loc_conf_t *conf = NULL;
    conf = (ngx_http_mergedemo_loc_conf_t *)ngx_http_get_module_loc_conf(r,ngx_http_mergedemo_module);
    if (conf == NULL)
    {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }

    /* Prepare for output, 128 is preserved for robust */
    b = ngx_create_temp_buf( r->pool, 128 + conf->name.len );
    if (b == NULL)
    {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }
    out.buf = b;
    out.next = NULL;

    b->last = ngx_sprintf(b->pos, "local conf index=[%d] loc_conf_create_count=[%d] ngx_http_mergedemo_set_count=[%d] text=[%s]", conf->loc_conf_index, loc_conf_create_count, ngx_http_mergedemo_set_count, conf->name.data);

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = b->last - b->pos;
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *) "text/plain";

    b->last_buf = 1;/* there will be no more buffers in the request */

    rc = ngx_http_send_header(r);

    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only)
    {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }

    ngx_http_output_filter(r, &out);
    ngx_http_finalize_request(r, 0);
}/*}}}*/

/**
* Reading data handler
* After read all the data from client we set a process handler
*/
static ngx_int_t
ngx_http_mergedemo_handler(ngx_http_request_t *r)
{/*{{{*/
    ngx_int_t rc = NGX_DONE;
    rc = ngx_http_read_client_request_body( r, mergedemo_process_handler );
    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }

    return NGX_DONE;
}/*}}}*/


/**
* set the request reading data handler
*/
static char *
ngx_http_mergedemo_set( ngx_conf_t *cf, ngx_command_t *cmd, void *conf )
{/*{{{*/
    ngx_http_core_loc_conf_t *clcf;

    ngx_str_t* value = (ngx_str_t*)cf->args->elts;
    ngx_http_mergedemo_loc_conf_t * loc_conf = ( ngx_http_mergedemo_loc_conf_t *)ngx_http_conf_get_module_loc_conf( cf, ngx_http_mergedemo_module );
    ngx_http_mergedemo_srv_conf_t * srv_conf = ( ngx_http_mergedemo_srv_conf_t *)ngx_http_conf_get_module_srv_conf( cf, ngx_http_mergedemo_module );
    ngx_http_mergedemo_main_conf_t * main_conf = ( ngx_http_mergedemo_main_conf_t *)ngx_http_conf_get_module_main_conf( cf, ngx_http_mergedemo_module );
    loc_conf->loc1 = value[0].len;
    srv_conf->srv1 = value[0].len;
    main_conf->main3 = *value;
    ngx_http_mergedemo_set_count++;

    clcf = (ngx_http_core_loc_conf_t *)ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module);
    clcf->handler = ngx_http_mergedemo_handler;

    return NGX_CONF_OK;
}/*}}}*/


static void *
ngx_http_mergedemo_create_main_conf(ngx_conf_t *cf)
{/*{{{*/
    ngx_http_mergedemo_main_conf_t *conf = NULL;

    conf = (ngx_http_mergedemo_main_conf_t *)ngx_pcalloc(cf->pool,sizeof(ngx_http_mergedemo_main_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }

    conf->main_conf_index = main_conf_create_count++;
    ngx_str_set(&(conf->name), "main conf");
    ngx_str_set(&conf->main3, "3333");

    return conf;
}/*}}}*/

static char *
ngx_http_mergedemo_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_http_mergedemo_main_conf_t* mconf = conf;

    ngx_str_t* value = (ngx_str_t*)cf->args->elts;
    ngx_http_mergedemo_loc_conf_t * loc_conf = ( ngx_http_mergedemo_loc_conf_t *)ngx_http_conf_get_module_loc_conf( cf, ngx_http_mergedemo_module );
    ngx_http_mergedemo_srv_conf_t * srv_conf = ( ngx_http_mergedemo_srv_conf_t *)ngx_http_conf_get_module_srv_conf( cf, ngx_http_mergedemo_module );
    ngx_http_mergedemo_main_conf_t * main_conf = ( ngx_http_mergedemo_main_conf_t *)ngx_http_conf_get_module_main_conf( cf, ngx_http_mergedemo_module );
    loc_conf->loc1 = value[0].len;
    srv_conf->srv1 = value[0].len;
    main_conf->main3 = *value;
    ngx_http_mergedemo_set_count++;

    ngx_str_set(&mconf->main3, "initialized 3333");
    ngx_str_set(&(mconf->name), "initialized main conf name");
    main_conf_init_count++;
    return NGX_CONF_OK;
}

static void *
ngx_http_mergedemo_create_srv_conf(ngx_conf_t *cf)
{/*{{{*/
    ngx_http_mergedemo_srv_conf_t *conf = NULL;

    conf = (ngx_http_mergedemo_srv_conf_t *)ngx_pcalloc(cf->pool,sizeof(ngx_http_mergedemo_srv_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }

    conf->srv_conf_index = srv_conf_create_count++;
    ngx_str_set(&(conf->name), "server conf");

    return conf;
}/*}}}*/

static void *
ngx_http_mergedemo_create_loc_conf(ngx_conf_t *cf)
{/*{{{*/
    ngx_http_mergedemo_loc_conf_t *conf = NULL;

    conf = (ngx_http_mergedemo_loc_conf_t *)ngx_pcalloc(cf->pool,sizeof(ngx_http_mergedemo_loc_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }

    conf->loc_conf_index = loc_conf_create_count++;
    ngx_str_set(&(conf->name), "local conf");

    return conf;
}/*}}}*/


static char *
ngx_http_mergedemo_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_mergedemo_srv_conf_t *prev = parent;
    ngx_http_mergedemo_srv_conf_t *conf = child;

    srv_conf_merge_count++;

    ngx_str_set(&(conf->name), "merged server conf");

    return NGX_CONF_OK;
}

static char *
ngx_http_mergedemo_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_mergedemo_loc_conf_t *prev = parent;
    ngx_http_mergedemo_loc_conf_t *conf = child;

    loc_conf_merge_count++;

    ngx_str_set(&(conf->name), "merged loc conf");


    return NGX_CONF_OK;
}

