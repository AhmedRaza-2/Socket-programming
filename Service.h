#pragma once
#include<iostream>
using namespace std;

class Service
{
private:
	int service_id;
	string service_name;
public:
	Service();
	Service(int service_id, string service_name);
	Service(const Service& obj);
	string tostring();
	void set_service_id(int service_id);
	void set_service_name(string service_name);
	int get_service_id()const;
	string get_service_name()const;
};