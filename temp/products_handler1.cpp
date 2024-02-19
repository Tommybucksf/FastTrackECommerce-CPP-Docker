
#include "handlers/products_handler.h"
#include <stdlib.h>

typedef struct {
    int id;
    char *name;
    float price;
} Product;



void products_handler(evhttp_request *req, void *arg) {
    const char *response = "<html><body><h1>Products list.</h1></body></html>";
    evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer");
        return;
    }
    evbuffer_add_printf(buf, "%s", response);
    evhttp_send_reply(req, HTTP_OK, "", buf);
    evbuffer_free(buf);
}