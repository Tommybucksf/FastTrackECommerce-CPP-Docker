FROM ubuntu:latest

# Install the necessary packages
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    make \
    libevent-dev \
    sqlite3 \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

# Path to store the database within the container
COPY server/db/mydatabase.db /server/db/mydatabase.db

# Copy the static files folder into the container
COPY static/images /server/static/images

# Copy server code into the container
COPY server/ /server

# Set the working directory to /server
WORKDIR /server

# Compile the server code
RUN g++ main.cpp handlers/homepage_handler.cpp handlers/products_handler.cpp handlers/account_handler.cpp handlers/cart_handler.cpp -o my_server -levent -Iinclude -std=c++17 -lsqlite3

# Command to run the server
CMD ["./my_server"]
