nginx-research
==============

中文介绍页面：[http://blog.codeg.cn/2015/01/02/nginx-research-readme](http://blog.codeg.cn/2015/01/02/nginx-research-readme)

This project is created for researching the source code of Nginx. It has some features :

- Compile and debug can use Visual Studio 2013(VS2013), not only GDB
- Treat Nginx as an outstanding C library, and write some example code of using it as a C library. 

Project homepage : [https://github.com/zieckey/nginx-research](https://github.com/zieckey/nginx-research)

## 1. Windows Usage

Oepn `nginx-win32-src\nginx.sln` using VS2013, and we can tow projects :

- nginx ： The windows version of Nginx, we can compile and run it directly without any dependent.
- nginxresearch : Some example code using Nginx as a C libraray

##### Nginx binary

We have written some Nginx modules:

- ngx_http hello world module
- ngx_http merge module
- ngx_http memcached module
- ngx_http upstream sample code

When it runs on windows using VS2013, it listens 80 port. You can open a browser and navigate to [http://localhost/helloworld.html](http://localhost/helloworld.html) this page will return the current time and the nginx startup time, as below :

	startup: 2015-01-01 19:26:16
	current: 2015-01-01 19:26:57

##### Using Nginx as a C library

Compile and run the nginxresearch project on Windows using VS2013. It contains some example code as below:

- ngx_encode_base64
- ngx_str_t
- ngx_pool_t
- ngx_hash_t
- ngx_list_t
- ngx_array_t
- ngx_queue_t

## 2. Linux Usage

##### Nginx Binary

Entering the Nginx sub module dir, use `make` directly.

##### Using Nginx as a C library

Entering `libnginx` dir and execute `make check`. It will run all the example codes.

## 3. Referrence:

1. [http://nginx.org/](http://nginx.org/)
2. [https://github.com/zieckey/nginx-1.0.14_comment](https://github.com/zieckey/nginx-1.0.14_comment)