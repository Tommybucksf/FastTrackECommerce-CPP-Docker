#include "handlers/products_handler.h"
#include <evhttp.h>
#include <sqlite3.h>
#include <sstream>
#include <vector>

struct Product {
    int id;
    std::string name;
    double price;
    std::string description;
    std::string imageUrl;
};

std::vector<Product> getProductsFromDatabase() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    std::vector<Product> products;

    // Opening the database
    if (sqlite3_open("/server/db/mydatabase.db", &db) == SQLITE_OK) {
        const char *sql = "SELECT id, name, price, description, imageUrl FROM products";
        
        // Preparing the SQL query
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            // Reading the results
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                Product p;
                p.id = sqlite3_column_int(stmt, 0);
                p.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                p.price = sqlite3_column_double(stmt, 2);
                p.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                p.imageUrl = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
                products.push_back(p);
            }
            // Releasing the query resource
            sqlite3_finalize(stmt);
        } else {
            // Handling SQL preparation error
            // Error logging can be added here
        }
        // Closing the database
        sqlite3_close(db);
    } else {
        // Handling database opening error
        // Error logging can be added here
    }
    
    return products;
}

void products_handler(evhttp_request *req, void *arg) {
    auto products = getProductsFromDatabase();
    
    std::stringstream html;
    html << "<html><head><style>"
         << "body { font-family: Arial, sans-serif; margin: 20px; }"
         << " .product { margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px; }"
         << " .product img { max-width: 100px; margin-right: 20px; float: left; }"
         << " .product h2 { margin: 0; padding: 0; }"
         << "</style></head><body><h1>Products list</h1>";
    
    for (const auto& product : products) {
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
