#ifndef HATCHBACK_H
#define HATCHBACK_H
#include "Car.h"
class Hatchback : public Car {
private:
    int cargo_space;string fuel_type;
public:
    Hatchback();
    Hatchback(int car_id, string car_make, string car_model, float car_price, int car_seating_capacity, int car_ground_clearance, string is_car_available, int cargo_space, string fuel_type);
    Hatchback(const Hatchback& obj);
    ~Hatchback();
    void set_cargo_space(int cargo_space);
    void set_fuel_type(string fuel_type);

    int get_cargo_space() const;
    string get_fuel_type()const;
    string toString();

    virtual void store_to_file();
    virtual void view_from_file();

    void update();
    void search();
    void del();
    void menu(Hatchback& obj);
    friend ostream& operator<<(ostream& cout, const Hatchback& obj);
    friend istream& operator>>(istream& cin, Hatchback& obj);
};
#endif
