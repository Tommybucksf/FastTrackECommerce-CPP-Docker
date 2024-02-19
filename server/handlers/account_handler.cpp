// handlers/homepage_handler.cpp
#include "handlers/account_handler.h"

void account_handler(evhttp_request *req, void *arg) {
    const char *response = "<html><body><h1>Welcom <user>!</h1></body></html>";
    evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer");
        return;
    }
    evbuffer_add_printf(buf, "%s", response);
    evhttp_send_reply(req, HTTP_OK, "", buf);
    evbuffer_free(buf);
}