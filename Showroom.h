// Showroom.h
#ifndef SHOWROOM_H
#define SHOWROOM_H

#include <string>

class Showroom {
private:
    int id;
    std::string name;
    std::string location;

public:
    // Constructors
    Showroom();
    Showroom(int id, std::string name, std::string location);
    Showroom(Showroom& obj);

    // Setters
    void set_id(int id);
    void set_name(std::string name);
    void set_location(std::string location);

    // Getters
    int get_id();
    std::string get_name();
    std::string get_location();

    // Utility
    std::string toStringShowroom();

    // File operations
    void store_to_file();
    void view_from_file();
    void search();
    void update();
    void del();

    // Menu
    void menu();
};

#endif // SHOWROOM_H
