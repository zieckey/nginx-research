
    This is an example to explain how to create a NGX_HTTP_ACCESS_PHASE
filter handler.
    This nginx module is model after ngx_http_access_module. The usage 
of ngx_http_token_filter_module is also similar to ngx_http_access_module.
For example:
        location /helloworld.html {
        	helloworld_query;
			token_filter token=xxx;
            allow all;
        }    
    This configuration will deny the URL which contains 'token=xxx'.
