#include "Service.h"
#include"string"
// Default constructor
Service::Service()
{
    service_id = 0;
    service_name = "n/a";
}
// Parameterized constructor
Service::Service(int service_id, string service_name)
{
    this->service_id = service_id;
    this->service_name = service_name;
}
// Copy constructor
Service::Service(const Service& obj)
{
    service_id = obj.service_id;
    service_name = obj.service_name;
}
string Service::tostring() {
    return to_string(service_id) + "\t" + service_name;
}
// Setter for service_id
void Service::set_service_id(int service_id)
{
    this->service_id = service_id;
}
void Service::set_service_name(string service_name)
{
    this->service_name = service_name;
}
// Getter for service_id
int Service::get_service_id()const
{
    return service_id;
}
string Service::get_service_name()const
{
    return service_name;
}