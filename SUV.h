#ifndef SUV_H
#define SUV_H
#include "Car.h"
class SUV : public Car {
private:
    int offroad_capability, towing_capacity;
public:
    SUV();
    SUV(int car_id, string car_make, string car_model, float car_price, int car_seating_capacity, int car_ground_clearance, string is_car_available, int offroad_capability, int towing_capacity);
    SUV(const SUV& obj);
    ~SUV();
    void set_offroad_capability(int offroad_capability);
    void set_towing_capacity(int towing_capacity);

    int get_offroad_capability()const;
    int get_towing_capacity()const;
    string toString();

    virtual void store_to_file();
    virtual void view_from_file();

    void update();
    void search();
    void del();
    void menu(SUV& obj);
    friend ostream& operator<<(ostream& cout, const SUV& obj);
    friend istream& operator>>(istream& cin, SUV& obj);
};
#endif