#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <fstream>
#include "Person.h"
#include "Car.h"
#include "Transaction.h"
#include"Insurance.h"
#include"Service.h"
using namespace std;
class Customer : public Person , public Transaction,public Car,public Insurance,public Service{
private:
    string customer_vehicle_status, customer_payment_status,membership;
public:
    // Constructors
    Customer();
    Customer(int person_id, string person_name, string customer_vehicle_status, string customer_payment_status,string membership,int transaction_id,float transaction_amount,int car_id,string car_make,string car_model, int insurance_id, int service_id, string insurance_type, string service_name);
    Customer(const Customer& obj);
    // Setters
    void set_customer_vehicle_status(string customer_vehicle_status);
    void set_customer_payment_status(string customer_payment_status);
    void set_customer_membership(string membership);
    // Getters
    string get_customer_vehicle_status();
    string get_customer_payment_status();
    string get_customer_membership();
    // Utility functions
    string tostring() ;
    void customer_membership(string new_membership);
    virtual void store_to_file();
    virtual void view_from_file();
    void update();
    void search();
    void del();
    void menu(Customer& obj);
    // Stream operator
    friend ostream& operator<<(ostream& cout, const Customer& obj);
    friend istream& operator>>(istream& cin, Customer& obj);
};
#endif // CUSTOMER_H
