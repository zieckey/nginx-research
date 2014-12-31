
include ../build.mk

NGINX_OBJS = $(NGINX_OBJS_PATH)/src/core/ngx_string.o \
			 $(NGINX_OBJS_PATH)/src/core/ngx_palloc.o \
			 $(NGINX_OBJS_PATH)/src/os/unix/ngx_alloc.o

$(TARGET) : $(OBJS)
	gcc -o $@ $(NGINX_OBJS) $^ $(LDFLAGS) 


clean :
	rm -rf *.o $(TARGET)

