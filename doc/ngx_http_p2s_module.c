
#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>

typedef struct {
    unsigned long consume;
    char* ini_buf;
    size_t buflen;//the lenght of the ini_buf

} ngx_http_p2s_conf_t;

static char *ngx_http_p2s_urlquery_set(ngx_conf_t *cf, ngx_command_t *cmd, void*conf);

static void *ngx_http_p2s_create_conf(ngx_conf_t *cf);

static uint8_t* get_raw_http_body( ngx_http_request_t* r, size_t* body_len );

static ngx_command_t ngx_http_p2s_commands[] =
{/*{{{*/

    { ngx_string("p2s_urlquery"), //The command name, it MUST BE the same as nginx.conf location block's command

    NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
    ngx_http_p2s_urlquery_set,
    0,
    0,
    NULL },

    ngx_null_command
};/*}}}*/

static ngx_http_module_t ngx_http_p2s_module_ctx =
{/*{{{*/
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    ngx_http_p2s_create_conf, /* create location configration */
    NULL /* merge location configration */
};/*}}}*/

ngx_module_t ngx_http_p2s_module =
{/*{{{*/
    NGX_MODULE_V1,
    &ngx_http_p2s_module_ctx, /* module context */
    ngx_http_p2s_commands, /* module directives */
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
* @brief Get the HTTP body data from the ngx_http_request_t struct.
* @warning DONNOT release the return pointer.
* @param[in] ngx_http_request_t * r -
* The HTTP request of NGINX struct which holds the HTTP data.
* @param[out] size_t * body_len - The body data length will stored here.
* @return uint8_t* - A pointer to a memory where
* stored the HTTP body raw binary data.
* The memory is allocated from nginx memory pool,
* so the caller don't need to warry about the memory release work.
*/
static uint8_t* get_raw_http_body( ngx_http_request_t* r, size_t* body_len )
{/*{{{*/
    printf( "%s\n", __PRETTY_FUNCTION__ );
    ngx_chain_t* bufs = r->request_body->bufs;
    *body_len = 0;

    ngx_buf_t* buf = NULL;
    uint8_t* data_buf = NULL;
    size_t content_length = 0;

    if ( r->headers_in.content_length == NULL )
    {
        return NULL;
    }

    // malloc space for data_buf

    content_length = atoi( (char*)(r->headers_in.content_length->value.data) );

    data_buf = ( uint8_t* )ngx_palloc( r->pool , content_length + 1 );

    size_t buf_length = 0;

    while ( bufs )
    {
        buf = bufs->buf;

        bufs = bufs->next;

        buf_length = buf->last - buf->pos ;

        if( *body_len + buf_length > content_length )
        {

            memcpy( data_buf + *body_len, buf->pos, content_length - *body_len);
            *body_len = content_length ;

            break;
        }

        memcpy( data_buf + *body_len, buf->pos, buf->last - buf->pos );
        *body_len += buf->last - buf->pos;
    }

    if ( *body_len )
    {
        data_buf[*body_len] = '\0';
    }

    return data_buf;
}/*}}}*/


/**
* Process the client request.
* The client post data has stored in <code>r</code>
*/
static void p2s_urlquery_process_handler(ngx_http_request_t *r)
{/*{{{*/
    printf( "%s\n", __PRETTY_FUNCTION__ );
    ngx_int_t rc = NGX_OK;
    ngx_buf_t *b = NULL;
    ngx_chain_t out;


    ngx_http_p2s_conf_t *conf = NULL;
    conf = (ngx_http_p2s_conf_t *)ngx_http_get_module_loc_conf(r,ngx_http_p2s_module);
    if (conf == NULL)
    {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);
    size_t bodylen = 0;
    uint8_t* contents = get_raw_http_body( r, &bodylen );
    printf( "time=%f http body data len=%d:\n%s\n", (tv.tv_sec +tv.tv_usec/1000000.0f ), (int)bodylen, (char*)contents );
    printf("----------------------http body data end-------------------\n");

    /* Prepare for output, 128 is preserved for robust */
    b = ngx_create_temp_buf( r->pool, 128 + conf->buflen );
    if (b == NULL)
    {
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }
    out.buf = b;
    out.next = NULL;

    b->last = ngx_sprintf(b->pos, "%s", conf->ini_buf);

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
ngx_http_p2s_urlquery_handler(ngx_http_request_t *r)
{/*{{{*/
    printf( "%s\n", __PRETTY_FUNCTION__ );
    ngx_int_t rc = NGX_DONE;
    rc = ngx_http_read_client_request_body( r, p2s_urlquery_process_handler );
    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }

    return NGX_DONE;
}/*}}}*/


/**
* set the request reading data handler
*/
static char *
ngx_http_p2s_urlquery_set( ngx_conf_t *cf, ngx_command_t *cmd, void *conf )
{/*{{{*/
    printf( "%s\n", __PRETTY_FUNCTION__ );
    ngx_http_core_loc_conf_t *clcf;

    clcf = (ngx_http_core_loc_conf_t *)ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module);
    clcf->handler = ngx_http_p2s_urlquery_handler;

	ngx_str_t* params = (ngx_str_t*)cf->args->elts;
    //printf( "%d params: %s %s %s %s\n", (int)cf->args->nelts, params[0].data, params[1].data, params[2].data, params[3].data);
    printf( "%d params: %s\n", (int)cf->args->nelts, params[0].data ); // this can get the conf paramters string
    
    return NGX_CONF_OK;
}/*}}}*/


static void *
ngx_http_p2s_create_conf(ngx_conf_t *cf)
{/*{{{*/
    printf( "%s\n", __PRETTY_FUNCTION__ );
    ngx_http_p2s_conf_t *conf;

    conf = (ngx_http_p2s_conf_t *)ngx_pcalloc(cf->pool,sizeof(ngx_http_p2s_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }

    conf->consume = 0;

    /* we open the nginx config file and send it back to client*/
    FILE *fp = fopen( "../conf/nginx.conf", "r");
    if( fp == NULL )
    {
        return NGX_CONF_ERROR;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell( fp );
    if ( len < 0 )
    {
        return NGX_CONF_ERROR;
    }
    conf->buflen = (size_t)(len + 1);
    conf->ini_buf = (char *)ngx_palloc( cf->pool, len + 1 );
    fseek(fp, 0, SEEK_SET);
    fread(conf->ini_buf, 1, len, fp);
    conf->ini_buf[len] = 0;
    fclose(fp);

    return conf;
}/*}}}*/