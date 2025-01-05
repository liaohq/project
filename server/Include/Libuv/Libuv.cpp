#include<iostream>
#include<cstdlib>
#include<sstream>
#include<thread>
#include "Libuv.h"
using namespace std;

Libuv::Libuv(){

}

string get_client_ip(uv_tcp_t* client){
// 获取客户端的 socket 信息  
    struct sockaddr_storage peer_addr;  
    int peer_addr_len = sizeof(peer_addr);  
    if (uv_tcp_getpeername(client, (struct sockaddr*)&peer_addr, &peer_addr_len) == 0) {  
        char ip_str[INET6_ADDRSTRLEN];  
        void* addr;
		int port;
        if (peer_addr.ss_family == AF_INET) {  
            struct sockaddr_in* in = (struct sockaddr_in*)&peer_addr;  
            addr = &(in->sin_addr);
			port= ntohs(in->sin_port);
        } else {  
            struct sockaddr_in6* in6 = (struct sockaddr_in6*)&peer_addr;  
            addr = &(in6->sin6_addr); 
			port=ntohs(in6->sin6_port);
        }  
        inet_ntop(peer_addr.ss_family, addr, ip_str, sizeof(ip_str));  
        //printf("Accepted connection from client IP: %s\n", ip_str); 
    
		std::ostringstream oss;
		oss<<ip_str<<":"<<port;
		return oss.str();
	} else {  
        // 如果获取客户端信息失败，可以获取错误信息  
        //fprintf(stderr, "Getpeername error %s\n", uv_strerror(uv_last_error(uv_default_loop())));  
		cout<<"getpeername error"<<endl;
	}

	return "";
}
void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {  
    *buf = uv_buf_init((char*)malloc(suggested_size), suggested_size);  
}  
 

void on_write(uv_write_t *req, int status){
	if(status<0){
		std::cout<<"on_write error:"<<uv_strerror(status)<<std::endl;
	}
	free(req);
}

void read_cb(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {  
	string ip_str = get_client_ip((uv_tcp_t*)stream);
    if (nread > 0) {  
        std::cout <<"client:"<< ip_str<< ",Received: " << buf->base << std::endl; 
		uv_write((uv_write_t*)malloc(sizeof(uv_write_t)), stream, buf, 1, on_write);
    } else if (nread < 0) {  
        if (nread != UV_EOF)  
            //std::cerr << "Read error " << uv_err_name(uv_last_error(uv_default_loop())) << std::endl;  
        uv_close((uv_handle_t*) stream, NULL);
		cout<<"close by client,ip:"<<ip_str<<endl;
    } else {  
        /* EOF: call uv_close() */  
        cout<<"close by eof"<<endl;
		uv_close((uv_handle_t*) stream, NULL);  
    }  
  
    free(buf->base);  
}


void on_connect_cb(uv_stream_t* server, int status) {  
    if (status == -1) {  
	    //std::cerr << "Connection error: " << uv_strerror(uv_last_error(uv_default_loop())) << std::endl;  
		cout<<"connection error"<<endl;
		return;
	}

	uv_tcp_t* client =(uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(uv_default_loop(),client);
	if(uv_accept(server, (uv_stream_t*)client) == 0) {
		string ip_str = get_client_ip(client);
		cout<<"accepted new connection, ip:"<<ip_str<<endl;
		uv_read_start((uv_stream_t*)client, alloc_buffer, read_cb);
	}else{
		cout<<"accepted error"<<endl;
		free(client);
	}
}

void Libuv::Init(){
	cout<<"Libuv Init, listen ip: 0.0.0.0, port:9999"<<endl;
	uv_loop_t *loop = uv_default_loop();

	uv_tcp_t server;
	uv_tcp_init(loop, &server);
	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", 9999, &addr);
	uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
	uv_listen((uv_stream_t*)&server, 128, on_connect_cb);

	//thread t1(uv_run, loop, UV_RUN_DEFAULT);
	//t1.detach();
	uv_run(loop, UV_RUN_DEFAULT);
}

