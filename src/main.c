#include <stdio.h>
#include <stdbool.h>
#include "tcp_client.h"
#include <stdlib.h>

#define LOCALHOST "127.0.0.1"

int main(int argc, char** argv)
{
    int result = 0;
    char* buffer = (char*) malloc(1024);
    tcp_client* client = create_tcp_client(LOCALHOST, 8045);
    if (client == NULL)
    {
        result = 1;
        goto defer;
    }

    bool is_connected = connect_tcp_client(client) == TCP_OK;

    if(!is_connected)
    {
        result = 1;
        goto defer;
    }

    char* data = "HELLO";
    send_tcp_data(client, data, 5);
    tcp_status status = recv_tcp_data(client, buffer, 1024);

    if(status != TCP_OK)
    {
        result = 1;
        goto defer;
    }

    buffer[client->last_bytes_read - 1] = '\0';

    printf("%s\n", buffer);

defer:
    if (result == 1) printf("Failed to connect.\n");
    if (client) close_tcp_client(client);
    if (buffer) free(buffer);
    return result;
}

