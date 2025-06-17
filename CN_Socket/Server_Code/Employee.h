#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <fstream>
#include "Person.h" // Assuming Person class is defined in Person.h

class Employee : public Person
{
private:
    string employee_position;
    float employee_salary;

public:
    // Constructors
    Employee();
    Employee(int person_id, string person_name, string employee_position, float employee_salary);
    Employee(const Employee& obj);
    void set_employee_position(string employee_position);
    void set_employee_salary(float employee_salary);
    string get_employee_position();
    float get_employee_salary();
    string tostring();
    void promote(string new_position);
    virtual void store_to_file();
    virtual void view_from_file();
    void update();
    void search();
    void del();
    void menu(Employee& obj);
    friend ostream& operator<<(ostream& cout, const Employee& obj);
    friend istream& operator>>(istream& cin, Employee& obj);
};
#endif // EMPLOYEE_H
