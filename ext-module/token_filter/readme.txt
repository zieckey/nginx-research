    This is an example to explain how to create a NGX_HTTP_ACCESS_PHASE
filter handler.
    This nginx module is model after ngx_http_access_module. The usage 
of ngx_http_token_filter_module is also similar to ngx_http_access_module.
For example:
        location /helloworld.html {
        	helloworld_query;
			token_filter "token=xxx token=yyy token=zzz";
            allow all;
        }    
    This configuration will deny the URL which contains 'token=xxx' 
or 'token=yyy' or 'token=yyy'. The following URLs will all be denied:
    http://domain/helloworld.html?x=y&token=xxx
    http://domain/helloworld.html?x=y&token=yyy
    http://domain/helloworld.html?x=y&token=zzz&a=b
    http://domain/helloworld.html?x=y&token=yyyyz&c=d
