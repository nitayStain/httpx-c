#ifdef _WIN32

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "ws2_32.lib")

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR -1

#endif

#include <stdint.h>

typedef uint8_t tcp_status;

#define TCP_MEM_ERR 0
#define TCP_IP_ERR 1
#define TCP_CONFAILED 2
#define TCP_MSGFAILED 3
#define TCP_OK 99

typedef struct tcp_client {
    int sock;
    size_t last_bytes_read;
    struct sockaddr_in server_addr;
} tcp_client;

tcp_client* create_tcp_client(const char* server_ip, const uint16_t port);
tcp_status connect_tcp_client(tcp_client* self);

tcp_status close_tcp_client(tcp_client* self);
tcp_status send_tcp_data(tcp_client* self, const char* data, const size_t size);
tcp_status recv_tcp_data(tcp_client* self, char* buffer, const size_t size);

#ifdef _WIN32
void wsa_init(void);
void wsa_cleanup(void);
#endif
