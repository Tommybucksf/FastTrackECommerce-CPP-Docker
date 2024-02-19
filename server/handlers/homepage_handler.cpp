// handlers/homepage_handler.cpp
#include "handlers/homepage_handler.h"

void homepage_handler(evhttp_request *req, void *arg) {
    const char *response = "<html><body>"
        "<h1>Welcome to Our Webshop</h1>"
        "<ul>"
        "<li><a href='/products'>Products</a></li>"
        "<li><a href='/account'>Account</a></li>"
        "<li><a href='/cart'>Cart</a></li>"
        "</ul>"
        "</body></html>";
    evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer");
        return;
    }
    evbuffer_add_printf(buf, "%s", response);
    evhttp_send_reply(req, HTTP_OK, "", buf);
    evbuffer_free(buf);
}