#include <stdio.h>
#include "ngx_config.h"
#include "ngx_conf_file.h"
#include "nginx.h"
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_string.h"

/**
 * define variable and function used by nginx source code
 */
volatile ngx_cycle_t  *ngx_cycle;
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
            const char *fmt, ...)
{
}

int main()
{
    u_char* p = NULL;
    ngx_uint_t size;
    ngx_str_t dst;
    ngx_str_t mystr = ngx_string("hello, world !");
    ngx_keyval_t pair = {ngx_string("url"), ngx_string("http://rainx.cn/index.php?test=1")};
    int dst_len = ngx_base64_encoded_length(mystr.len);
    printf("source length is %lu, destination length is %d\n", mystr.len, dst_len );
    p = malloc(ngx_base64_encoded_length(mystr.len) + 1);
    dst.data = p;
    ngx_encode_base64(&dst, &mystr);
    printf("source str is %s\ndestination str is %s\n", mystr.data, dst.data);
    free(p);
    size = pair.value.len + 2 * ngx_escape_uri(NULL, pair.value.data, pair.value.len, NGX_ESCAPE_URI);
    p = malloc(size * sizeof(u_char));
    ngx_escape_uri(p, pair.value.data, pair.value.len, NGX_ESCAPE_URI);
    printf("escaped %s is : %s (%lu)\noriginal url size is %lu\n", pair.key.data, p, size, pair.value.len);
    free(p);
    return 0;

}

