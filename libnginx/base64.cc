#include "allinc.h"

/*
 * 关于ngx_str_t更多解释请参考：http://tengine.taobao.org/book/chapter_02.html#ngx-str-t-100
 */
TEST_UNIT_P(base64) {
    ngx_str_t enc;
    ngx_str_t dec;
    ngx_str_t mystr = ngx_string("https://github.com/zieckey/gochart. gochart is a chart ploting tool which is simple to use. It used the open sources golang and highcharts which is modeled after goplot. It can plot spline/line/area/bar/column/pie.");
    int enc_len = ngx_base64_encoded_length(mystr.len);
    enc.data = (u_char*)ngx_pcalloc(pool, enc_len + 1);
    dec.data = (u_char*)ngx_pcalloc(pool, mystr.len + 1);
    ngx_encode_base64(&enc, &mystr);
    printf("source string is [%s] , base64 encoded string is [%s]\n", mystr.data, enc.data);
    ngx_decode_base64(&dec, &enc);
    dec.data[dec.len] = 0;
    printf("base64 encoded string is [%s] , base64 decoded string is [%s]\n", enc.data, dec.data);
    if (ngx_strncmp(mystr.data, dec.data, dec.len) == 0) {
        printf("base64 encode/decode OK\n");
    }
    else {
        printf("base64 encode/decode FAILED\n");
    }
}
