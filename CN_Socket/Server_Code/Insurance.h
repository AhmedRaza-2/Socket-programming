#pragma once
#include<iostream>
using namespace std;
class Insurance
{
private:
	int Insurance_id;
	string Insurance_type;
public:
	Insurance();
	Insurance(int Insurance_id, string Insurance_type);
	Insurance(const Insurance& obj);
	string tostring();
	void set_Insurance_id(int Insurance_id);
	void set_Insurance_type(string Insurance_type);
	int get_Insurance_id()const;
	string get_Insurance_type()const;
};
