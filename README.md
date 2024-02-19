# Project name: FastTrackECommerce-CPP-Docker
prototype of an e-commerce website
## Description.
This project implements a basic version of an e-commerce website using only C or C++ programming languages with gcc inside Docker containers. This approach demonstrates how traditional system programming languages can be applied to web development, emphasizing their flexibility and efficiency.

## Technologies.
- Programming language: C/C++
- Compiler: GCC
- Development and deployment environment: Docker

### Requirements
- Docker
- GCC (already included in the Docker image)

### Install and run
### bash
```
git clone https://github.com/yourusername/FastTrackECommerce-CPP-Docker.git

cd FastTrackECommerce-CPP-Docker

docker build -t ecommerce-cpp .

docker run -d -p 8080:8080 ecommerce-cpp
```

