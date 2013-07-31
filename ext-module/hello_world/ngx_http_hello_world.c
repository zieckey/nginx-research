#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int           index;
    char*         buf;
    size_t        buflen;//the length of the buf
} ngx_http_helloworld_conf_t;

static char *ngx_http_helloworld_set(ngx_conf_t *cf, ngx_command_t *cmd, void*conf);

static void *ngx_http_helloworld_create_conf(ngx_conf_t *cf);

static int loc_conf_create_count = 0;
static int ngx_http_helloworld_set_count = 0;

static ngx_command_t ngx_http_helloworld_commands[] =
{/*{{{*/
    { ngx_string("helloworld_query"), //The command name, it MUST BE the same as nginx.conf location block's command

    NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
    ngx_http_helloworld_set,
    0,
    0,
    NULL },

    ngx_null_command
};/*}}}*/

static ngx_http_module_t ngx_http_helloworld_module_ctx =
{/*{{{*/
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    ngx_http_helloworld_create_conf, /* create location configuration */
    NULL /* merge location configuration */
};/*}}}*/

ngx_module_t ngx_http_helloworld_module =
{/*{{{*/
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
};/*}}}*/


void* ngx_datadup( ngx_pool_t* pool, const void* srcdata, size_t len )                                               
{/*{{{*/
    u_char* data = (u_char*)ngx_palloc( pool, len + 1 );
    memcpy( data, srcdata, len );
    data[len] = 0;                                                                                                    
    return (void*)data;
}/*}}}*/

void ngx_add_header( ngx_http_request_t *r, const char* key, size_t key_len, const char* data, size_t data_len )
{/*{{{*/                                                                                                              
    ngx_table_elt_t * header = (ngx_table_elt_t *)ngx_list_push(&r->headers_out.headers);                             
    header->hash             = 1;
    header->key.len          = key_len;
    header->key.data         = (u_char*)ngx_datadup(r->pool, key, key_len);                                          
    header->value.len        = data_len;                                                                              
    header->value.data       = (u_char*)ngx_datadup(r->pool, data, data_len);                                        
}/*}}}*/

void ngx_foreach_header( ngx_http_request_t *r )
{/*{{{*/                                                                                                              
   // ngx_table_elt_t * header = (ngx_table_elt_t *)ngx_list_push(&);                             
    ngx_list_part_t* part = &r->headers_out.headers.part;
    ngx_table_elt_t* table = part->elts;
    ngx_table_elt_t* header = NULL;
    int i = 0;
    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            table = part->elts;
            i = 0;
        }

        header = &table[i];
        printf("find a header : key=[%s] value=[%s]\n", (char*)header->key.data, (char*)header->value.data);
    }                                   
}/*}}}*/

ngx_uint_t ngx_fetch_httpcode( ngx_http_request_t *r )
{/*{{{*/                                                                                                              
    ngx_list_part_t* part = &r->headers_out.headers.part;
    ngx_table_elt_t* table = part->elts;
    ngx_table_elt_t* header = NULL;
    int i = 0;
    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            table = part->elts;
            i = 0;
        }

        header = &table[i];
        printf("find a header : key=[%s] value=[%s]\n", (char*)header->key.data, (char*)header->value.data);
        if (strncmp("httpcode", header->key.data, header->key.len) == 0)
        {
            return atoi((char*)header->value.data);
        }
    }
    return NGX_HTTP_OK;
}/*}}}*/

/**
* Process the client request.
* The client post data has stored in <code>r</code>
*/
static void helloworld_process_handler(ngx_http_request_t *r)
{/*{{{*/
    ngx_int_t rc = NGX_OK;
    ngx_buf_t *b = NULL;
    ngx_chain_t out;
    const char* key = "httpcode";
    const char* value = "201";
    const char* key1 = "httpcode2";
    const char* value1 = "302xx";

    ngx_http_helloworld_conf_t *conf = NULL;
    conf = (ngx_http_helloworld_conf_t *)ngx_http_get_module_loc_conf(r,ngx_http_helloworld_module);
    if (conf == NULL)
    {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }

    /* Prepare for output, 128 is preserved for robust */
    b = ngx_create_temp_buf( r->pool, 128 + conf->buflen );
    if (b == NULL)
    {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }
    out.buf = b;
    out.next = NULL;


    ngx_add_header(r, key, strlen(key), value, strlen(value));
    ngx_add_header(r, key1, strlen(key1), value1, strlen(value1));
    ngx_foreach_header(r);

    b->last = ngx_sprintf(b->pos, "local conf index=[%d] loc_conf_create_count=[%d] ngx_http_helloworld_set_count=[%d] text=[%s]", conf->index, loc_conf_create_count, ngx_http_helloworld_set_count, conf->buf);

#if 1
    r->headers_out.status = NGX_HTTP_OK;
#else
    //test set http code
    r->headers_out.status = ngx_fetch_httpcode(r);
#endif
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
ngx_http_helloworld_handler(ngx_http_request_t *r)
{/*{{{*/
    ngx_int_t rc = NGX_DONE;
    rc = ngx_http_read_client_request_body( r, helloworld_process_handler );
    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }

    return NGX_DONE;
}/*}}}*/


/**
* set the request reading data handler
*/
static char *
ngx_http_helloworld_set( ngx_conf_t *cf, ngx_command_t *cmd, void *conf )
{/*{{{*/
    ngx_http_core_loc_conf_t *clcf;

    clcf = (ngx_http_core_loc_conf_t *)ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module);
    clcf->handler = ngx_http_helloworld_handler;

    ngx_http_helloworld_set_count++;

    return NGX_CONF_OK;
}/*}}}*/


static void *
ngx_http_helloworld_create_conf(ngx_conf_t *cf)
{/*{{{*/
    ngx_http_helloworld_conf_t *conf = NULL;

    conf = (ngx_http_helloworld_conf_t *)ngx_pcalloc(cf->pool,sizeof(ngx_http_helloworld_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }

    conf->index = loc_conf_create_count++;
    conf->buf = "Hello NGINX.";
    conf->buflen  = strlen(conf->buf);

    return conf;
}/*}}}*/