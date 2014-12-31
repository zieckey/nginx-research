
include build.mk

NGINX_ROOT = ../nginx-$(NGINX_VERSION)

NGINX_MAKEFILE = $(NGINX_ROOT)/Makefile

LDFLAGS = -lpthread -lcrypt -lpcre -lcrypto -lcrypto -lz

NGINX_OBJS = \
			 $(NGINX_ROOT)/objs/src/core/nginx.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_log.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_palloc.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_array.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_list.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_hash.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_buf.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_queue.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_output_chain.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_string.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_parse.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_inet.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_file.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_crc32.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_murmurhash.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_md5.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_rbtree.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_radix_tree.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_slab.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_times.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_shmtx.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_connection.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_cycle.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_spinlock.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_cpuinfo.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_conf_file.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_resolver.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_open_file_cache.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_crypt.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_proxy_protocol.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_syslog.o \
			 $(NGINX_ROOT)/objs/src/event/ngx_event.o \
			 $(NGINX_ROOT)/objs/src/event/ngx_event_timer.o \
			 $(NGINX_ROOT)/objs/src/event/ngx_event_posted.o \
			 $(NGINX_ROOT)/objs/src/event/ngx_event_busy_lock.o \
			 $(NGINX_ROOT)/objs/src/event/ngx_event_accept.o \
			 $(NGINX_ROOT)/objs/src/event/ngx_event_connect.o \
			 $(NGINX_ROOT)/objs/src/event/ngx_event_pipe.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_time.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_errno.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_alloc.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_files.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_socket.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_recv.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_readv_chain.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_udp_recv.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_send.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_writev_chain.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_channel.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_shmem.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_process.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_daemon.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_setaffinity.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_setproctitle.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_posix_init.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_user.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_process_cycle.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_linux_init.o \
			 $(NGINX_ROOT)/objs/src/event/modules/ngx_epoll_module.o \
			 $(NGINX_ROOT)/objs/src/os/unix/ngx_linux_sendfile_chain.o \
			 $(NGINX_ROOT)/objs/src/core/ngx_regex.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_core_module.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_special_response.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_request.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_parse.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_header_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_write_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_copy_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_log_module.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_request_body.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_variables.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_script.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_upstream.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_upstream_round_robin.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_parse_time.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_static_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_index_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_chunked_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_range_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_headers_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_not_modified_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_busy_lock.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_file_cache.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_gzip_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/ngx_http_postpone_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_ssi_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_charset_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_userid_filter_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_autoindex_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_auth_basic_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_access_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_limit_conn_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_limit_req_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_geo_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_map_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_split_clients_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_referer_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_rewrite_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_proxy_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_fastcgi_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_uwsgi_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_scgi_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_memcached_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_empty_gif_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_browser_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_upstream_hash_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_upstream_ip_hash_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_upstream_least_conn_module.o \
			 $(NGINX_ROOT)/objs/src/http/modules/ngx_http_upstream_keepalive_module.o \
			 $(NGINX_ROOT)/objs/ngx_modules.o 

LIBNGINX = libnginx.a

SUBDIR = 

all : $(LIBNGINX)

$(LIBNGINX) : $(NGINX_MAKEFILE)
	$(AR) $(ARFLAGS) $@ $(NGINX_OBJS) 
	ranlib $@

libnginx.so :
	cc -static -o $@ $(LDFLAGS) $(NGINX_OBJS)

$(NGINX_MAKEFILE) : 
	tar zxvf $(NGINX_ROOT).tar.gz -C ..
	sed -i "s|-Werror|-Werror -fPIC|g" $(NGINX_ROOT)/auto/cc/gcc               #Add -fPIC
	sed -i "s|main(int argc|__xmain(int argc|g" $(NGINX_ROOT)/src/core/nginx.c #Rename main --> __xmain
	cd $(NGINX_ROOT); ./configure ; (make||echo)

clean :
	rm -rf $(NGINX_ROOT)
	rm -rf $(LIBNGINX) *.so *.a
