
#include "handlers/products_handler.h"
#include <evhttp.h>
#include <sstream>
#include <vector>

struct Product {
    int id;
    std::string name;
    double price;
    std::string description;
    std::string imageUrl;
};

std::vector<Product> Products = {
    {1, "Laptop", 999.99, "High performance laptop", "http://localhost:8080/products/laptop.jpg"},
    {2, "Smartphone", 499.49, "Latest model smartphone", "http://localhost:8080/products/smartphone.jpg"},
    {3, "Tablet", 250.30, "Portable and powerful tablet", "http://localhost:8080/products/tablet.jpg"}
};

void products_handler(evhttp_request *req, void *arg) {
    std::stringstream html;
    html << "<html><head><style>"
         << "body { front-family: Arial, sans-serif; margin: 20px; }"
         << " .product { margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px; }"
         << " .product img { max-width: 100px; margin-right: 20px; float: left; }"
         << " .product h2 { margin: 0; padding: 0; }"
         << "</style></head><body><h1>Products list</h1>";
    
    for (const auto& product : Products) {
        html << "<div class='product'><img src='" << product.imageUrl << "' alt='" << product.name << "'>"
             << "<h2>" << product.name << " - $" << product.price << "</h2>"
             << "<p>" << product.description << "</p></div><div style='clear:both;'></div>";
    }

    html << "</body></html>";

    evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer");
        return;
    }

    evbuffer_add_printf(buf, "%s", html.str().c_str());
    evhttp_send_reply(req, HTTP_OK, "", buf);
    evbuffer_free(buf);
    
}