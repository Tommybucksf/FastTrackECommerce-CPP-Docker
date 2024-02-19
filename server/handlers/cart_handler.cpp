// handlers/homepage_handler.cpp
#include "handlers/cart_handler.h"

void cart_handler(evhttp_request *req, void *arg) {
    const char *response = "<html><body><h1> Add your product to the cart! </h1></body></html>";
    evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer");
        return;
    }
    evbuffer_add_printf(buf, "%s", response);
    evhttp_send_reply(req, HTTP_OK, "", buf);
    evbuffer_free(buf);
}
