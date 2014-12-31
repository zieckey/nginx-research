#include <stdio.h>
#include "ngx_config.h"
#include "ngx_conf_file.h"
#include "nginx.h"
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_string.h"

int main() {
    ngx_str_t enc;
    ngx_str_t dec;
    ngx_str_t mystr = ngx_string("https://github.com/zieckey/gochart. gochart is a chart ploting tool which is simple to use. It used the open sources golang and highcharts which is modeled after goplot. It can plot spline/line/area/bar/column/pie.");
    int enc_len = ngx_base64_encoded_length(mystr.len);
    enc.data = malloc(enc_len + 1);
    dec.data = malloc(mystr.len);
    ngx_encode_base64(&enc, &mystr);
    printf("source string is [%s] , base64 encoded string is [%s]\n", mystr.data, enc.data);
    ngx_decode_base64(&dec, &enc);
    printf("base64 encoded string is [%s] , base64 decoded string is [%s]\n", enc.data, dec.data);
    if (ngx_strncmp(mystr.data, dec.data, dec.len) == 0) {
        printf("base64 encode/decode OK\n");
    } else {
        printf("base64 encode/decode FAILED\n");
    }
    free(enc.data);
    free(dec.data);
    return 0;
}

