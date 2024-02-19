
#include "include/handlers/homepage_handler.h"
#include "include/handlers/products_handler.h"
#include "include/handlers/account_handler.h"
#include "include/handlers/cart_handler.h"


int main() {
    struct event_base *base = event_base_new();
    if (!base) {
        puts("Failed to create an event base");
        return 1;
    }
    struct evhttp *http = evhttp_new(base);
    if (!http) {
        puts("Failed to create HTTP");
        return 1;
    }
    if (evhttp_bind_socket(http, "0.0.0.0", 8080) != 0){
        puts("Failed to bind socket");
        return 1;
    }
    //evhttp_set_gencb(http, request_handler, NULL);

    evhttp_set_cb(http, "/", homepage_handler, NULL);
    evhttp_set_cb(http, "/products", products_handler, NULL);
    evhttp_set_cb(http, "/account", account_handler, NULL);
    evhttp_set_cb(http, "/cart", cart_handler, NULL);

    event_base_dispatch(base);

    return 0;
}