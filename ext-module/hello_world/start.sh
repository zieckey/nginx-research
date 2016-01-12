#! /bin/sh

echo 'test : curl http://localhost:18090/helloworld.html'
echo

./nginx -c `pwd`/conf/nginx.conf
