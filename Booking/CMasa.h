#pragma once
#include <string>
#include <iostream>
using namespace std;
class CMasa
{
	string denumire_masa;
	double pret=0.0f;
	string disponibilitate;
public:
	CMasa(){}
	CMasa(string denumire, string disponibilitate, double pret) :denumire_masa{ denumire }, disponibilitate{ disponibilitate }, pret{pret}{}
	string get_denumireMasa() { return denumire_masa; }
	double get_pretMasa() { return pret; }
	string get_disponibilitate() { return disponibilitate; }

	string& set_denumireMasa() { return denumire_masa; }
	double& set_pretMasa() { return pret; }
	string& set_disponibilitate() { return disponibilitate; }

};

