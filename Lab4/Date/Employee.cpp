#include "Employee.h"
#include "Date.h"
#include <iostream>

using namespace std;

Employee::Employee(string first, string last, Date dateOfBirth, Date dateOfHire)
    : firstName(first), lastName(last), birthDate(dateOfBirth), hireDate(dateOfHire) {
    cout << "Employee object constructor: " << firstName << ' ' << lastName << endl;
}

Employee::Employee(const Employee &e)
    : firstName(e.firstName), lastName(e.lastName), birthDate(e.birthDate), hireDate(e.hireDate) {
    cout << "Employee object copy constructor: " << firstName << ' ' << lastName;
    cout << " Hired: ";
    hireDate.print();
    cout << " Birthday: ";
    birthDate.print();
    cout << endl;
}

void Employee::print() const {
    cout << lastName << "," << firstName << " Hired: ";
    hireDate.print();
    // cout << hireDate.month << '/' << hireDate.day << '/' << hireDate.year;
    cout << " Birthday: ";
    birthDate.print();
    cout << endl;
}

Employee::~Employee() {
    cout << "Employee object destructor: " << lastName << ", " << firstName << endl;
}