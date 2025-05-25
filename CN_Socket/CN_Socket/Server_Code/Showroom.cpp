#include <iostream>
#include <fstream>
#include <string>
#include "Showroom.h"
using namespace std;

Showroom::Showroom() {
	id = 0;
	name = "n/a";
	location = "n/a";
}
Showroom::Showroom(int id, string name, string location) {
	this->id = id;
	this->name = name;
	this->location = location;
}
Showroom::Showroom(Showroom& obj) {
	this->id = obj.id;
	this->name = obj.name;
	this->location = obj.location;
}
void Showroom::set_id(int id) {
	this->id = id;
}
void Showroom::set_name(string name) {
	this->name = name;
}
void Showroom::set_location(string location) {
	this->location = location;
}
int Showroom::get_id() {
	return id;
}
string Showroom::get_name() {
	return name;
}
string Showroom::get_location() {
	return location;
}
string Showroom::toStringShowroom() {
	return to_string(id) + "\t" + name + "\t" + location;
}
void Showroom::store_to_file() {
	ofstream fout("Showroom.txt", ios::app);
	if (fout.is_open()) {
		fout << toStringShowroom() << endl;
		fout.close();
		cout << "\nData Stored To Showroom File";
	}
	else {
		cerr << "Error: Unable to open file for writing." << endl;
	}
}
void Showroom::view_from_file() {
	ifstream fin("Showroom.txt");
	if (fin.is_open()) {
		string data;
		while (getline(fin, data)) {
			cout << data << endl;
		}
		fin.close();
	}
	else {
		cerr << "Error: Unable to open file for reading." << endl;
	}
}
void Showroom::search() {
	int id;
	cout << "Enter the ID of the Showroom to search: ";
	cin >> id;

	ifstream fin("Showroom.txt");
	if (fin.is_open()) {
		bool found = false;
		while (fin >> id >> name >> location) {
			if (id == id) {
				found = true;
				cout << "\nShowroom ID : " << id;
				cout << "\nShowroom Name : " << name;
				cout << "\nShowroom  Location : " << location;
			}
			fin.close();
			if (!found) {
				cout << "Showroom with ID " << id << " not found." << endl;
			}
		}
	}
	else {
		cerr << "Error: Unable to open file for reading." << endl;
	}
}
void Showroom::update() {
	int id;
	cout << "Enter the ID of the Showroom to update: ";
	cin >> id;
	ifstream fin("Showroom.txt");
	ofstream fout("temp.txt");
	if (fin.is_open() && fout.is_open()) {
		bool found = false;
		while (fin >> id >> name >> location) {
			if (id == id) {
				found = true;
				cout << "Enter Showroom ID : : ";
				cin >> id;
				cout << "Enter Showroom Name : ";
				cin >> name;
				cout << "Enter Showroom Location : ";
				cin >> location;
				set_name(name);
				set_id(id);
				set_location(location);
			}
			fout << toStringShowroom() << endl;
		}
		fin.close();
		fout.close();
		remove("Showroom.txt");
		rename("temp.txt", "Showroom.txt");
		if (!found) {
			cout << "Showroom with ID " << id << " not found." << endl;
		}
		else {
			cout << "Showroom updated successfully." << endl;
		}
	}
	else {
		cerr << "Error: Unable to open file for reading or writing." << endl;
	}
}
void Showroom::del() {
	int id;
	cout << "Enter the ID of the Showroom to delete: ";
	cin >> id;
	ifstream fin("Showroom.txt");
	ofstream fout("temp.txt");
	if (fin.is_open() && fout.is_open()) {
		bool found = false;
		while (fin >> id >> name >> location) {
			if (id == id) {
				found = true;
			}
			else {
				fout << id << "\t" << name << "\t" << location << "\n";
			}
		}
		fin.close();
		fout.close();
		remove("Showroom.txt");
		rename("temp.txt", "Showroom.txt");
		if (!found) {
			cout << "Showroom with ID " << id << " not found." << endl;
		}
		else {
			cout << "Showroom with ID " << id << " deleted successfully." << endl;
		}
	}
	else {
		cerr << "Error: Unable to open file for reading or writing." << endl;
	}
}
void Showroom::menu() {
	int choice;
	cout << "\nMenu 1- add 2- view 3- update 4- search 5- delete";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		cout << "Enter Showroom ID: ";
		cin >> id;
		cin.ignore();
		cout << "Enter Showroom Name : ";
		getline(cin, name);
		cout << "Enter Showroom location : ";
		getline(cin, location);
		set_id(id);
		set_name(name);
		set_location(location);
		store_to_file();
		break;
	}
	case 2:
	{
		view_from_file();
		break;
	}
	case 3:
	{
		update();
		break;
	}
	case 4:
	{
		search();
		break;
	}
	case 5:
	{
		del();
		break;
	}
	default:
	{
		cout << "\nInvalid Choice";
		break;
	}
	}
}