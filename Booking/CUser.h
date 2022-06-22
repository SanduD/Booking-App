#pragma once
#include <string>
#include <iostream>
using namespace std;

class CUser
{
	string username;
	string password;
	int nr_rezervari;
public:
	CUser() {}
	CUser(string name, string pass, int nr_rez=0) :username(name), password(pass), nr_rezervari(nr_rez) {}
	string get_name() { return username; }
	string get_pass() { return password; }
	int get_rezervari()const { return nr_rezervari; }
	int &set_rezervari() { return nr_rezervari; }
	friend ostream& operator <<(ostream& out, CUser &user);
};

