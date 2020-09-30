#include "my_vector.h"


#include <cstring>
#include <cstdlib>
#include <sstream>


#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__);


namespace base_test {


    class Test {
    protected:

        static int failed_num;
        static int total_num;

        static void check(bool expr, const char *func, const char *filename, size_t line_num);

    public:
        static bool show_final_result();

        virtual void run_all_tests() = 0;
    };


    int Test::failed_num = 0;
    int Test::total_num = 0;


    void Test::check(bool expr, const char *func, const char *filename, size_t line_num) {
        total_num += 1;
        if (expr) return;
        failed_num += 1;
        std::cout << filename << ':' << line_num << ": " << func << "(): ";
        std::cout << "Test failed" << std::endl;
    }


    bool Test::show_final_result() {
        std::cout << total_num - failed_num << "/" << total_num;
        std::cout << " tests were passed" << std::endl;
        return failed_num == 0;
    }


}  // namespace base_test


namespace product {

    class Product {
    public:
        Product() = delete;
        Product(const char *name, int quantity, double price);
        Product(const Product &product);
        Product &operator=(const Product &product);
        ~Product();

        friend std::ostream &operator<<(std::ostream &out, const Product &product);

        bool operator==(const Product &product) const;

    private:
        char *name_;
        int quantity_;
        double price_;
    };


    Product::Product(const char *name, int quantity, double price) {
        name_ = new char[strlen(name) + 1];
        strcpy(name_, name);
        quantity_ = quantity;
        price_ = price;
    }


    Product::Product(const product::Product &product) {
        name_ = new char[strlen(product.name_) + 1];
        strcpy(name_, product.name_);
        quantity_ = product.quantity_;
        price_ = product.price_;
    }


    Product &Product::operator=(const Product &product) {
        if (&product != this) {
            delete[] name_;
            name_ = new char[strlen(product.name_) + 1];
            strcpy(name_, product.name_);
            quantity_ = product.quantity_;
            price_ = product.price_;
        }
        return *this;
    }


    Product::~Product() {
        delete[] name_;
    }


    std::ostream &operator<<(std::ostream &out, const Product &product) {
        out << product.name_ << ' ';
        out << product.quantity_ << ' ';
        out << product.price_ << ' ';
        return out;
    }


    bool Product::operator==(const Product &product) const {
        bool flag1 = strcmp(name_, product.name_) == 0;
        bool flag2 = quantity_ == product.quantity_;
        bool flag3 = price_ == product.price_;
        return flag1 && flag2 && flag3;
    }

}  // namespace product


namespace vector_test {


    template<typename T>
    class VectorTest : public base_test::Test {

    public:

        VectorTest(T first, T second) : first_element_(first), second_element_(second) {}

        void run_all_tests() override;

    private:

        T first_element_;
        T second_element_;

        // testing functions about construction
        void first_construction();
        void second_construction();
        void third_construction();
        void fourth_construction();
        void fifth_construction();

        // testing functions about size
        void first_size();
        void second_size();
        void third_size();

        // testing reserve() function
        void first_reserve();
        void second_reserve();
        void third_reserve();

        // testing operator[] function
        void first_square_brackets();
        void second_square_brackets();
        void third_square_brackets();

        // function push_back() was checked in the previous vector_test

        // testing functions about deleting
        void first_deleting();
        void second_deleting();
        void third_deleting();

        // testing operator<< function
        void test_output();


    };


    template<typename T>
    class VectorTestDefaultConstructable : public base_test::Test {
    public:

        VectorTestDefaultConstructable(T first, T second) : first_element_(first), second_element_(second) {}

        void run_all_tests() override;

    private:

        // testing constructor
        void constructor();

        // testing resize() function
        void first_resize();
        void second_resize();
        void third_resize();

        T first_element_;
        T second_element_;
    };



// ==========================vector_test====================================


// testing functions about construction

    template<typename T>
    void VectorTest<T>::first_construction() {
        my_vector::my_vector<T> vector;
        bool flag1 = vector.size() == 0;
        bool flag2 = vector.capacity() == 0;
        bool flag3 = vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::second_construction() {
        my_vector::my_vector<T> temp;
        temp.push_back(first_element_);
        temp.push_back(first_element_);
        temp.push_back(second_element_);
        temp.pop_back();
        my_vector::my_vector<T> vector(temp);
        bool flag1 = vector.size() == 2;
        bool flag2 = vector.capacity() == 2;
        bool flag3 = vector[0] == first_element_;
        flag3 = flag3 && (vector[1] == first_element_);
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::third_construction() {
        my_vector::my_vector<T> temp;
        temp.push_back(first_element_);
        temp.push_back(first_element_);
        my_vector::my_vector<T> vector;
        vector.push_back(second_element_);
        vector.push_back(second_element_);
        vector = temp;
        bool flag1 = vector.size() == 2;
        bool flag2 = vector.capacity() == 2;
        bool flag3 = vector[0] == first_element_;
        bool flag4 = vector[1] == first_element_;
        DO_CHECK(flag1 && flag2 && flag3 && flag4)
    }

    template<typename T>
    void VectorTest<T>::fourth_construction() {
        my_vector::my_vector<T> temp;
        temp.push_back(first_element_);
        temp.push_back(first_element_);
        my_vector::my_vector<T> vector;
        vector.push_back(second_element_);
        vector.push_back(second_element_);
        vector = std::move(temp);
        bool flag1 = vector.size() == 2;
        bool flag2 = vector.capacity() == 2;
        bool flag3 = vector[0] == first_element_;
        bool flag4 = vector[1] == first_element_;
        DO_CHECK(flag1 && flag2 && flag3 && flag4)
    }

    template<typename T>
    void VectorTest<T>::fifth_construction() {
        my_vector::my_vector<T> temp;
        temp.push_back(first_element_);
        temp.push_back(first_element_);
        my_vector::my_vector<T> vector(std::move(temp));
        bool flag1 = vector.size() == 2;
        bool flag2 = vector.capacity() == 2;
        bool flag3 = vector[0] == first_element_;
        bool flag4 = vector[1] == first_element_;
        DO_CHECK(flag1 && flag2 && flag3 && flag4)
    }


// testing functions about size

    template<typename T>
    void VectorTest<T>::first_size() {
        my_vector::my_vector<T> vector;
        bool flag1 = vector.size() == 0;
        bool flag2 = vector.capacity() == 0;
        bool flag3 = vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::second_size() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        bool flag1 = vector.size() == 1;
        bool flag2 = vector.capacity() == 1;
        bool flag3 = !vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::third_size() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        bool flag1 = vector.size() == 3;
        bool flag2 = vector.capacity() == 4;
        bool flag3 = !vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }


// testing reserve() function

    template<typename T>
    void VectorTest<T>::first_reserve() {
        my_vector::my_vector<T> vector;
        vector.reserve(10);
        bool flag1 = vector.size() == 0;
        bool flag2 = vector.capacity() == 16;
        bool flag3 = vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::second_reserve() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.reserve(10);
        bool flag1 = vector.size() == 1;
        bool flag2 = vector.capacity() == 16;
        bool flag3 = vector[0] == first_element_;
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::third_reserve() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(first_element_);
        vector.push_back(first_element_);
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        vector.reserve(3);
        bool flag1 = vector.size() == 5;
        bool flag2 = vector.capacity() == 8;
        bool flag3 = !vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }


// testing operator[] function

    template<typename T>
    void VectorTest<T>::first_square_brackets() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        bool flag1 = vector.size() == 2;
        bool flag2 = vector[0] == first_element_;
        bool flag3 = vector[1] == second_element_;
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::second_square_brackets() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        vector[0] = second_element_;
        bool flag1 = vector.size() == 2;
        bool flag2 = vector[0] == second_element_;
        bool flag3 = vector[1] == second_element_;
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::third_square_brackets() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        vector.push_back(first_element_);
        const my_vector::my_vector<T> other(vector);
        bool flag1 = other.size() == 3;
        bool flag2 = other.capacity() == 4;
        bool flag3 = other[1] == second_element_;
        DO_CHECK(flag1 && flag2 && flag3)
    }


// testing pop_back() function

    template<typename T>
    void VectorTest<T>::first_deleting() {
        my_vector::my_vector<T> vector;
        vector.pop_back();
        bool flag1 = vector.size() == 0;
        bool flag2 = vector.capacity() == 0;
        bool flag3 = vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::second_deleting() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        vector.push_back(first_element_);
        vector.clear();
        bool flag1 = vector.size() == 0;
        bool flag2 = vector.capacity() == 4;
        bool flag3 = vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTest<T>::third_deleting() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        vector.push_back(first_element_);
        vector.pop_back();
        vector.pop_back();
        bool flag1 = vector.size() == 1;
        bool flag2 = vector.capacity() == 4;
        bool flag3 = !vector.empty();
        DO_CHECK(flag1 && flag2 && flag3)
    }


// test operator<< function

    template<typename T>
    void VectorTest<T>::test_output() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        std::stringstream stream1;
        std::stringstream stream2;
        stream1 << vector;
        stream2 << first_element_ << ' ';
        stream2 << second_element_ << ' ';
        std::string buffer1, buffer2;
        char first, second;
        while (stream1 >> first) buffer1 += first;
        while (stream2 >> second) buffer2 += second;
        bool flag1 = buffer1.size() == buffer2.size();
        bool flag2 = buffer1 == buffer2;
        DO_CHECK(flag1 && flag2)
    }


// definition run_all_tests() function

    template<typename T>
    void VectorTest<T>::run_all_tests() {
        first_construction();
        second_construction();
        third_construction();
        fourth_construction();
        fifth_construction();
        first_size();
        second_size();
        third_size();
        first_reserve();
        second_reserve();
        third_reserve();
        first_square_brackets();
        second_square_brackets();
        third_square_brackets();
        first_deleting();
        second_deleting();
        third_deleting();
        test_output();
    }


// ==========================VectorTestDefaultConstructable========================


    template<typename T>
    void VectorTestDefaultConstructable<T>::constructor() {
        my_vector::my_vector<T> vector(10);
        bool flag1 = vector.size() == 10;
        bool flag2 = vector.capacity() == 16;
        bool flag3 = true;
        for (int i = 0; i < 10; i++) {
            flag3 = flag3 && (vector[i] == T());
        }
        DO_CHECK(flag1 && flag2 && flag3)
    }


// testing resize() function

    template<typename T>
    void VectorTestDefaultConstructable<T>::first_resize() {
        my_vector::my_vector<T> vector;
        vector.resize(10);
        bool flag1 = vector.size() == 10;
        bool flag2 = vector.capacity() == 16;
        bool flag3 = true;
        for (int i = 0; i < 10; i++) {
            flag3 = flag3 && (vector[i] == T());
        }
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTestDefaultConstructable<T>::second_resize() {
        my_vector::my_vector<T> vector;
        T temp(first_element_);
        vector.push_back(std::move(temp));          // testing push_back() with 'move'
        vector.push_back(second_element_);
        vector.resize(10);
        bool flag1 = vector.size() == 10;
        bool flag2 = vector.capacity() == 16;
        bool flag3 = vector[0] == first_element_;
        flag3 = flag3 && (vector[1] == second_element_);
        for (int i = 2; i < 10; i++) {
            flag3 = flag3 && (vector[i] == T());
        }
        DO_CHECK(flag1 && flag2 && flag3)
    }

    template<typename T>
    void VectorTestDefaultConstructable<T>::third_resize() {
        my_vector::my_vector<T> vector;
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        vector.push_back(first_element_);
        vector.push_back(second_element_);
        vector.push_back(first_element_);
        vector.resize(3);
        bool flag1 = vector.size() == 3;
        bool flag2 = vector.capacity() == 8;
        bool flag3 = vector[0] == first_element_;
        flag3 = flag3 && (vector[1] == second_element_);
        flag3 = flag3 && (vector[2] == first_element_);
        DO_CHECK(flag1 && flag2 && flag3)
    }


// definition run_all_tests() function

    template<typename T>
    void VectorTestDefaultConstructable<T>::run_all_tests() {
        constructor();
        first_resize();
        second_resize();
        third_resize();
    }


}  // namespace vector_test



template<typename T>
void test_my_vector(T first, T second) {
    vector_test::VectorTest<T> test(first, second);
    test.run_all_tests();
}


template<typename T>
void test_my_vector_default_constructable(T first, T second) {
    vector_test::VectorTestDefaultConstructable<T> test(first, second);
    test.run_all_tests();
}


#include <vector>


int main() {

    test_my_vector<int>(5, 10);
    test_my_vector_default_constructable(5, 10);


    product::Product product1("hello", 4, 12.0);
    product::Product product2("qwerty", -1, 7.5);
    test_my_vector<product::Product>(product1, product2);


    if (base_test::Test::show_final_result()) return 0;
    return 1;

}


