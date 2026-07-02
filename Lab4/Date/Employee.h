#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Date.h"
#include <string>

using namespace std;

class Employee {
  public:
    Employee(const string, const string, const Date, const Date);
    Employee(const Employee &);
    void print() const;
    ~Employee();

  private:
    string firstName;
    string lastName;
    const Date birthDate;
    const Date hireDate;
};

#endif