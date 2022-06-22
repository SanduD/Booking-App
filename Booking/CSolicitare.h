#pragma once
#include "CRezervare.h"
class CSolicitare :public CRezervare
{
	string username;
	string status;
	string nume_masa;
	double suma_totala;
public:
	CSolicitare(){}
	CSolicitare(string username, string nume_cazare, int tip_camera, int nr_camere,string nume_masa, date check_in, date check_out, string status,double suma_totala) :
		username{ username }, status{ status }, nume_masa{ nume_masa }, suma_totala{ suma_totala }, CRezervare(nume_cazare, tip_camera, nr_camere, check_in, check_out) {}

	string get_username() { return username; };
	string get_status() { return status; };
	string get_numeMasa() { return nume_masa; }
	double get_suma() { return suma_totala; }

	string& set_status() { return status; }
	string& set_username() { return username; }
	string& set_numeMasa() { return nume_masa; }
	double& set_suma() { return suma_totala; }
	friend ostream& operator<<(ostream& out, CSolicitare& rezervare);
	friend istream& operator>>(istream& in, CSolicitare& rezervare);
};

