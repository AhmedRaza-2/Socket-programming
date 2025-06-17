#ifndef SEDAN_H
#define SEDAN_H
#include "Car.h"
class Sedan : public Car {
private:
    float fuel_efficiency, trunk_capacity;
public:
    Sedan();
    Sedan(int car_id, string car_make, string car_model, float car_price, int car_seating_capacity, int car_ground_clearance, string is_car_available, float fuel_efficiency, float trunk_capacity);
    Sedan(const Sedan& obj);
    ~Sedan();
    void set_fuel_efficiency(float fuel_efficiency);
    void set_trunk_capacity(float trunk_capacity);

    float get_fuel_efficiency()const;
    float get_trunk_capacity()const;
    string toString();

    virtual void store_to_file();
    virtual void view_from_file();

    void update();
    void search();
    void del();
    void menu(Sedan& obj);
    friend ostream& operator<<(ostream& cout, const Sedan& obj);
    friend istream& operator>>(istream& cin, Sedan& obj);
};
#endif