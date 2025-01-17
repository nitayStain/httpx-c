#include <stdio.h>
#include <stdbool.h>
#include "tcp_client.h"
#include <stdlib.h>

#define LOCALHOST "127.0.0.1"

int main(int argc, char** argv)
{
    char* buffer = (char*) malloc(1024);
    tcp_client* client = create_tcp_client(LOCALHOST, 8045);
    bool is_connected = connect_tcp_client(client) == TCP_OK;
    if(!is_connected)
    {
        printf("Failed to connect.\n");
        close_tcp_client(client);
        return 1;
    }

    char* data = "HELLO";
    send_tcp_data(client, data, 5);
    tcp_status status = recv_tcp_data(client, buffer, 1024);
    
    if(status != TCP_OK)
    {
        printf("Failed to connect.\n");
        close_tcp_client(client);
        return 1;
    }

    buffer[client->last_bytes_read - 1] = '\0';

    printf("%s\n", buffer);

    close_tcp_client(client);
    return 0;
}

