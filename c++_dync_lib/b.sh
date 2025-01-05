#gcc -shared -o libcore.so libcore.c  -I/root/lua-5.4.6/src -L/root/lua-5.4.6/src -fPIC
gcc -shared -o libcore.so libcore.cpp  -I/root/lua-5.4.6/src -L/root/lua-5.4.6/src -fPIC
