#include "tcp_client.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
static bool wsa_initialized = false;
#endif

tcp_status set_tcp_address(tcp_client* self, const char* server_ip, const uint16_t port);

tcp_client* create_tcp_client(const char* server_ip, const uint16_t port)
{
#ifdef _WIN32
    if(!wsa_initialized)
    {
        wsa_init();
        wsa_initialized = true;
    }
#else

#endif

    tcp_client* self = (tcp_client*) malloc(sizeof(tcp_client*));
    if(self == NULL)
        return NULL;

    self->sock = socket(AF_INET, SOCK_STREAM, 0);
    if(self->sock == INVALID_SOCKET) 
    {
        free(self);
        return NULL;
    }

    if(set_tcp_address(self, server_ip, port) != TCP_OK)
    {
        free(self);
        return NULL;
    }
    
    return self;
}

tcp_status connect_tcp_client(tcp_client* self)
{
    if(connect(self->sock, (struct sockaddr*) &self->server_addr, sizeof(self->server_addr)) != 0) {
        return TCP_CONFAILED;
    }

    return TCP_OK;
}

tcp_status send_tcp_data(tcp_client* self, const char* data, const size_t size)
{
    if(send(self->sock, data, size, 0) == -1)
        return TCP_MSGFAILED;
    return TCP_OK;
}

tcp_status recv_tcp_data(tcp_client* self, char* data, const size_t size)
{
    size_t last_bytes_read = recv(self->sock, data, size, 0); 
    if(last_bytes_read <= 0)
        return TCP_MSGFAILED;

    self->last_bytes_read = last_bytes_read;
    return TCP_OK;
}

tcp_status close_tcp_client(tcp_client* self)
{
    if(self == NULL)
        return TCP_MEM_ERR;

#ifdef _WIN32
    closesocket(self->sock);
#else
    close(self->sock);
#endif

    free(self);
    return TCP_OK;
}

tcp_status set_tcp_address(tcp_client* self, const char* server_ip, const uint16_t port)
{
    memset(&self->server_addr, 0, sizeof(&self->server_addr));
    self->server_addr.sin_family = AF_INET;
    self->server_addr.sin_port = htons(port);

#ifdef _WIN32
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
#else
    if(inet_pton(AF_INET, server_ip, &self->server_addr.sin_addr) <= 0) {
        return TCP_IP_ERR;
    }
#endif

    return TCP_OK;
}

// define functions for winsock

#ifdef _WIN32

void wsa_init(void)
{
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        perror("Failed to load wsa. exiting.\n");
        exit(1);
    }
}

void wsa_cleanup(void)
{
    WSACleanup();
}

#else

#endif
