

MODULE_DIR=$(shell pwd)
NGINX_BINARY=$(NGINXHOME)/objs/nginx
NGINX_MAKEFILE=$(NGINXHOME)/Makefile
NGINXHOME=$(MODULE_DIR)/../../nginx-1.0.15
NGINX_BIN_INSTALL=$(NGINXHOME)/nginx


DEUBG_FLAGS=-DNDEBUG -g3 
CFLAGS=$(DEUBG_FLAGS) -DH_ENABLE_QLOG -fPIC -pipe -c \
		-Wshadow -Wcast-align -Wwrite-strings -Wsign-compare \
		-Winvalid-pch -fms-extensions -Woverloaded-virtual -Wsign-promo \
		-fno-gnu-keywords -Wfloat-equal -Wextra -Wall -Werror -Wno-unused-parameter \
		-Wno-unused-function -Wunused-variable -Wunused-value \
		-I../include -I $(MODULE_DIR)/qmodule/include\
		-I $(NGINXHOME)/src/core -I $(NGINXHOME)/src/event -I $(NGINXHOME)/src/event/modules \
		-I $(NGINXHOME)/src/os/unix -I $(NGINXHOME)/objs -I $(NGINXHOME)/src/http \
		-I $(NGINXHOME)/src/http/modules -I $(NGINXHOME)/src/mail \
		-I$(NGINX_MODULE_IPDISADM)/qmodule  $(BUSINESS_CFLAGS) \
		-I /home/s/include \
		-I/usr/local/include -MMD 

CXXFLAGS=$(CFLAGS)
LDFLAGS=

CC=gcc
CXX=g++

all : $(NGINX_MAKEFILE) $(NGINX_BINARY)
	cp $(NGINX_BINARY) .

start : $(NGINX_BINARY)
	./nginx -c `pwd`/nginx.conf 

$(NGINX_MAKEFILE) : config  
	cd $(NGINXHOME); ./configure --prefix=$(NGINX_BIN_INSTALL) --add-module=$(MODULE_DIR) --with-debug

$(NGINX_BINARY) : ngx_http_subrequest_test_module.c 
	$(MAKE) CFLAGS=" -pipe -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g" -j -C $(NGINXHOME)
	$(MAKE) install -C $(NGINXHOME)

-include $(DEPS)

clean :
	(cd $(NGINXHOME); $(MAKE) clean)				

.PHONY : clean distclean t sed engine


