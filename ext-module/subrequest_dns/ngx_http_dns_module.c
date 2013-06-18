#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#define NGX_HTTP_DNS_STATRT    0
#define NGX_HTTP_DNS_WORKING   1
#define NGX_HTTP_DNS_SUBURI    "/dns_back"
#define NGX_HTTP_DNS_SUBARGS   "host=&ip="

typedef struct {
    ngx_str_t                  subrequest;
} ngx_http_dns_loc_conf_t;

typedef struct {
    ngx_uint_t                 ret_count;
} ngx_http_dns_ctx_t;

static void *ngx_http_dns_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_dns_merge_loc_conf(ngx_conf_t *cf, void *parent,
    void *child);
static char *ngx_http_dns_post(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_dns_post_handler(ngx_http_request_t *r);
static void ngx_http_dns_post_read_body_handler(ngx_http_request_t *r);
static ngx_command_t ngx_http_dns_commands[] = {
    { ngx_string("http_dns_pass_post"),
      NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
      ngx_http_dns_post,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_dns_loc_conf_t, subrequest),
      NULL
    },
    ngx_null_command
};
static ngx_http_module_t ngx_http_dns_module_ctx = {
    NULL,      
    NULL,      
    NULL,      
    NULL,      
    NULL,      
    NULL,      
    ngx_http_dns_create_loc_conf,
               
    ngx_http_dns_merge_loc_conf,
               
};
ngx_module_t ngx_http_dns_module = {
    NGX_MODULE_V1,
    &ngx_http_dns_module_ctx,
    ngx_http_dns_commands,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING
};
static void *
ngx_http_dns_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_dns_loc_conf_t *conf;
    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_dns_loc_conf_t));
    if (conf == NULL)
    {
        return NULL;
    }
    
    return conf;
}
static char *
ngx_http_dns_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_dns_loc_conf_t *prev = parent;
    ngx_http_dns_loc_conf_t *conf = child;
    ngx_conf_merge_str_value(conf->subrequest, prev->subrequest,
        NGX_HTTP_DNS_SUBURI);
    return NGX_CONF_OK;
}
static char *
ngx_http_dns_post(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf;
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_dns_post_handler;
    ngx_conf_set_str_slot(cf, cmd, conf);
    return NGX_CONF_OK;
}
static ngx_int_t
ngx_http_dns_post_handler(ngx_http_request_t *r)
{
    ngx_int_t            rc;
    ngx_http_dns_ctx_t  *ctx;
    if (!(r->method & NGX_HTTP_POST)) {
        return NGX_HTTP_NOT_ALLOWED;
    }
    ctx = ngx_palloc(r->pool, sizeof(ngx_http_dns_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }
    ngx_http_set_ctx(r, ctx, ngx_http_dns_module);
    rc = ngx_http_read_client_request_body(r,
                              ngx_http_dns_post_read_body_handler);
    if (rc != NGX_OK) {
        return rc;
    }
    return NGX_DONE;
}
static void
ngx_http_dns_post_read_body_handler(ngx_http_request_t *r)
{
    u_char                       *p;
    ngx_uint_t                    i, flags;
    ngx_str_t                    *s, args;
    ngx_int_t                     rc, state;
    ngx_buf_t                    *buf, *b;
    ngx_chain_t                  *bufs, *out;
    ngx_array_t                  *domains;
    ngx_http_request_t           *sr;
    ngx_http_dns_ctx_t           *p_ctx;
    ngx_http_dns_loc_conf_t      *conf;
    conf = ngx_http_get_module_loc_conf(r, ngx_http_dns_module);
    state = NGX_HTTP_DNS_STATRT;
    bufs = r->request_body->bufs;
    buf = bufs->buf;
    r->discard_body = 1;
    s = NULL;
    p_ctx = ngx_http_get_module_ctx(r, ngx_http_dns_module);
    domains = ngx_array_create(r->pool, 10, sizeof(ngx_str_t));
    out = ngx_palloc(r->pool, sizeof(ngx_chain_t));
    if (out == NULL) {
        ngx_http_finalize_request(r, NGX_ERROR);
        return;
    }
    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        ngx_http_finalize_request(r, NGX_ERROR);
        return;
    }
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *) "text/plain";
    ngx_http_clear_content_length(r);
    rc = ngx_http_send_header(r);
    if (rc == NGX_ERROR ||rc > NGX_OK) {
        ngx_http_finalize_request(r, rc);
        return;
    }
    b->pos = (u_char *) "{";
    b->last = b->pos + sizeof("{") - 1;
    b->memory = 1;
    out->buf = b;
    out->next = NULL;
    if (NGX_OK != ngx_http_output_filter(r, out)) {
        ngx_http_finalize_request(r, NGX_ERROR);
        return;
    }
    
    for (p = buf->pos; p < buf->last; p++) {
        if (state == NGX_HTTP_DNS_STATRT) {
            s = ngx_array_push(domains);
            if (s == NULL) {
                ngx_http_finalize_request(r, NGX_ERROR);
                return;
            }
            s->data = p;
            s->len = 0;
            state = NGX_HTTP_DNS_WORKING;
        }
        switch(*p) {
            case LF:
                state = NGX_HTTP_DNS_STATRT;
                break;
            default:
                s->len++;
        }
    }
    p_ctx->ret_count = 4;
    s = domains->elts;
    for (i = 0; i < domains->nelts; i++) {
        args.len = sizeof("host=&ip=") - 1
                  + s[i].len
                  + r->connection->addr_text.len;
        args.data = ngx_palloc(r->pool, args.len * sizeof(u_char));
        if (args.data == NULL) {
            ngx_http_finalize_request(r, NGX_ERROR);
            return;
        }
        ngx_snprintf(args.data, args.len, "host=%V&ip=%V",
                     &s[i], &r->connection->addr_text);
        ngx_log_debug1(NGX_LOG_DEBUG_HTTP,
                                   r->connection->log, 0, "args: %V", &args);
        flags = NGX_HTTP_SUBREQUEST_WAITED;
        rc = ngx_http_subrequest(r, &conf->subrequest, &args, &sr, NULL, flags);
        if (rc == NGX_ERROR) {
            ngx_http_finalize_request(r, NGX_ERROR);
            return;
        }
        if (i != domains->nelts - 1) {
            b = ngx_calloc_buf(r->pool);
            if (b == NULL) {
                ngx_http_finalize_request(r, NGX_ERROR);
                return;
            }
            out = ngx_palloc(r->pool, sizeof(ngx_chain_t));
            if (out == NULL) {
                ngx_http_finalize_request(r, NGX_ERROR);
                return;
            }
            b->pos = (u_char *) ",";
            b->last = b->pos + sizeof(",") - 1;
            b->memory = 1;
            out->buf = b;
            out->next = NULL;
            if (NGX_OK != ngx_http_output_filter(r, out)) {
                ngx_http_finalize_request(r, NGX_ERROR);
                return;
            }
        }
    }
    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        ngx_http_finalize_request(r, NGX_ERROR);
        return;
    }
    out = ngx_palloc(r->pool, sizeof(ngx_chain_t));
    if (out == NULL) {
        ngx_http_finalize_request(r, NGX_ERROR);
        return;
    }
    b->pos = (u_char *) "}";
    b->last = b->pos + sizeof("}") - 1;
    b->last_buf = 1;
    b->memory = 1;
    out->buf = b;
    out->next = NULL;
    if (NGX_OK != ngx_http_output_filter(r, out)) {
        ngx_http_finalize_request(r, NGX_ERROR);
        return;
    }
    ngx_http_finalize_request(r, NGX_OK);
}
