#include "matrix.hpp"


#include <iostream>
#include <vector>


static const int COUNT_MATRICES = 10;


static int get_reg_number(const std::string &reg) {
    int number;
    sscanf(reg.c_str(), "$%d", &number);
    return number;
}


int main() {

    std::vector<Matrix> matrices(COUNT_MATRICES);

    std::string command;

    while (true) {

        std::cin >> command;

        if (command == "load") {
            std::string reg_str, file_name;
            std::cin >> reg_str >> file_name;
            int reg_int = get_reg_number(reg_str);

            try {
                matrices[reg_int].load(file_name);
            } catch (const MatrixException &exception) {
                std::cout << exception.what() << std::endl;
            } catch (const std::bad_alloc &exception) {
                std::cout << "Unable to allocate memory." << std::endl;
            }

        } else if (command == "print") {
            std::string reg_str;
            std::cin >> reg_str;
            int reg_int = get_reg_number(reg_str);
            matrices[reg_int].print();

        } else if (command == "add") {
            std::string reg1_str, reg2_str;
            std::cin >> reg1_str >> reg2_str;
            int reg1_int = get_reg_number(reg1_str);
            int reg2_int = get_reg_number(reg2_str);

            try {
                matrices[reg1_int].add(matrices[reg2_int]);
            } catch (const MatrixException &exception) {
                std::cout << exception.what() << std::endl;
            }

        } else if (command == "mul") {
            std::string reg1_str, reg2_str;
            std::cin >> reg1_str >> reg2_str;
            int reg1_int = get_reg_number(reg1_str);
            int reg2_int = get_reg_number(reg2_str);

            try {
                matrices[reg1_int].mul(matrices[reg2_int]);
            } catch (const MatrixException &exception) {
                std::cout << exception.what() << std::endl;
            } catch (const std::bad_alloc &exception) {
                std::cout << "Unable to allocate memory." << std::endl;
            }

        } else if (command == "elem") {
            std::string reg_str;
            std::cin >> reg_str;
            int reg_int = get_reg_number(reg_str);
            int row, column;
            std::cin >> row >> column;

            try {
                matrices[reg_int].elem(row, column);
            } catch (const MatrixException &exception) {
                std::cout << exception.what() << std::endl;
            }

        } else if (command == "exit") {
            break;
        }

    }

    return 0;
}
