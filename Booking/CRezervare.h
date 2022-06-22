#pragma once
#include <string>
#include <iostream>
using namespace std;
typedef struct
{
	int zi, luna, an;
}date;

class CRezervare
{
	string nume_cazare;
	int tip_camera=0;
	int nr_camere=0;
	date check_in = { 1,01,1970 };
	date check_out={ 1,01,1970 };
public:
	CRezervare() {}
	CRezervare(string nume_cazare, int tip_camera, int nr_camere, date check_in, date check_out) :nume_cazare{ nume_cazare }, tip_camera{ tip_camera }, nr_camere{ nr_camere }, check_in{ check_in }, check_out{ check_out }{};
	string get_denumireCazare() { return nume_cazare; }
	int get_tip_camera() { return tip_camera; }
	int get_nr_camere() { return nr_camere; }
	date get_checkIn() { return check_in; }
	date get_checkOut() { return check_out; }

	string& set_denumireCazare() { return nume_cazare; }
	int &set_tip_camera() { return tip_camera; }
	int& set_nr_camere() { return nr_camere; }
	date& set_checkIn() { return check_in; }
	date&set_checkOut() { return check_out; }
	friend ostream& operator<<(ostream& out, CRezervare& rezervare);
	friend istream& operator>>(istream& in, CRezervare& rezervare);
};

