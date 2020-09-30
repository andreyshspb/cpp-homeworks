#pragma once


#include <iostream>


namespace product {


class Product {
public:
    Product() = default;
    Product(const char *name, int quantity, double price);
    Product(const Product &product);
    Product &operator=(const Product &product);
    ~Product();

    friend std::ostream &operator<<(std::ostream &out, const Product &product);

    bool operator==(const Product product) const;

private:
    char *name_ = nullptr;
    int quantity_ = 0;
    double price_ = 0.0;
};


}  // namespace product

