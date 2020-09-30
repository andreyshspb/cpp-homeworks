#include "employee.hpp"
#include "developer.hpp"
#include "salesManager.hpp"
#include "employeesArray.hpp"

#include "bin_manip.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

int main() {

    std::string command;

    EmployeesArray workers_array;

    while(cin >> command) {
        if (command == "list") {
            cout << workers_array;
        } else if (command == "add") {
            int worker_type;
            cin >> worker_type;
            Employee *employee = nullptr;
            if (worker_type == developer_type) {
                employee = new Developer;
            } else if (worker_type == saleManager_type) {
                employee = new SalesManager;
            }
            cin >> *employee;
            workers_array.add(employee);
        } else if (command == "save") {
            std::string file_name;
            cin >> file_name;
            std::ofstream file(file_name, std::ios::binary);
            file << workers_array;
        } else if (command == "load") {
            std::string file_name;
            cin >> file_name;
            std::ifstream file(file_name, std::ios::binary);
            file >> workers_array;
        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}
