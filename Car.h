#ifndef CAR_H
#define CAR_H
#include <iostream>
using namespace std;
class Car {
private:
    int car_id, car_seating_capacity, car_ground_clearance;
    string car_make, car_model;
    float car_price;
    string is_car_available;
public:
    Car();
    Car(int car_id, string car_make, string car_model, float car_price, int car_seating_capacity, int car_ground_clearance, string availability);
    Car(int car_id, string car_make, string car_model);
    Car(const Car& obj);
    virtual ~Car();

    void set_car_id(int id);
    void set_car_make(string make);
    void set_car_model(string model);
    void set_car_seating_capacity(int seating_capacity);
    void set_car_ground_clearance(int ground_clearance);
    void set_car_price(float car_price);
    void set_car_availability(string is_car_available);

    int get_car_id()const;
    string get_car_make()const;
    string get_car_model()const;
    int get_car_seating_capacity()const;
    int get_car_ground_clearance()const;
    float get_car_price()const;
    string get_car_availability() const;

    string tostring();
    string tostring_2();
    virtual void view_from_file() = 0;
    virtual void store_to_file() = 0;
};
#endif
