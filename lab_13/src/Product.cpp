#include "Product.hpp"


#include <cstring>
#include <sstream>


namespace product {


Product::Product(const char *name, int quantity, double price) {
    if (name != nullptr) {
        name_ = new char[strlen(name) + 1];
        strcpy(name_, name);
    }
    quantity_ = quantity;
    price_ = price;
}


Product::Product(const product::Product &product) {
    if (product.name_ != nullptr) {
        name_ = new char[strlen(product.name_) + 1];
        strcpy(name_, product.name_);
    }
    quantity_ = product.quantity_;
    price_ = product.price_;
}


Product &Product::operator=(const Product &product) {
    if (&product != this) {
        delete[] name_;
        name_ = nullptr;
        if (product.name_ != nullptr) {
            name_ = new char[strlen(product.name_) + 1];
            strcpy(name_, product.name_);
        }
        quantity_ = product.quantity_;
        price_ = product.price_;
    }
    return *this;
}


Product::~Product() {
    delete[] name_;
}


std::ostream &operator<<(std::ostream &out, const Product &product) {
    if (product.name_ != nullptr) {
        out << product.name_ << ' ';
        out << product.quantity_ << ' ';
        out << product.price_;
        return out;
    }
    out << "Nothing";
    return out;
}


bool Product::operator==(const Product product) const {
    std::stringstream first;
    std::stringstream second;
    first << *this;
    second << product;
    return first.str() == second.str();
}


}  // namespace product

