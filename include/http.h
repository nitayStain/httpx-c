#include "tcp_client.h"

typedef enum http_req_method {
    GET = 0,
    POST,
    DELETE,
    UPDATE
} http_req_method;

typedef struct http_request {
    http_req_method method;
} request;



