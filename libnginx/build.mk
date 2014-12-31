
CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))

NGINX_OBJS_PATH =../../nginx-1.7.9/objs
NGINX_SRC_PATH  =../../nginx-1.7.9/src
CFLAGS = -pipe -O -W -Wall -Wpointer-arith \
		 -Wunused-value -Wno-unused-parameter -Wunused-function -Wunused-variable \
		 -fPIC\
		 -I $(NGINX_OBJS_PATH) \
		 -I $(NGINX_SRC_PATH)/core \
		 -I $(NGINX_SRC_PATH)/os \
		 -I $(NGINX_SRC_PATH)/os/unix \
		 -I $(NGINX_SRC_PATH)/os/event \

LDFLAGS = -lpcre -lcrypto -lz

TARGET=$(shell basename `pwd`)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@


