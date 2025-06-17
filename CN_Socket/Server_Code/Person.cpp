#include <iostream>
#include"Person.h"
#include "string"
#include <fstream>

using namespace std;
Person::Person()
{
    person_id = 0;
    person_name = "N/A";
}
Person::Person(int person_id, string person_name)
{
    this->person_id = person_id;
    this->person_name = person_name;
}
Person::Person(const Person& obj)
{
    this->person_id = obj.person_id;
    this->person_name = obj.person_name;
}

//Setter methods
void Person::set_person_id(int person_id) { this->person_id = person_id; }
void Person::set_person_name(string person_name) { this->person_name = person_name; }

// Getter methods
int Person::get_person_id() const
{
    return person_id;
}
string Person::get_person_name() const
{
    return person_name;
}
string Person::tostring() {
    return  to_string(person_id) +"\t" + person_name+"\t";
}
