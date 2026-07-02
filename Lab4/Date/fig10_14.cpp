#include "Employee.h"
#include <iostream>

using namespace std;

int main() {
    Date birth(7, 24, 1949);
    Date hire(3, 12, 1988);
    Employee manager("Bob", "Blue", birth, hire);
    Employee newEmployee(manager);

    cout << endl;
    manager.print();
    newEmployee.print();

    cout << "\nTest Date constructor with invalid values:\n";
    Date lastDayOff(14, 35, 1994);
    cout << endl;
}