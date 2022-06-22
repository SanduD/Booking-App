#pragma once
#include <iostream>
#include<string>
#include "CUnitatiCazare.h"
using namespace std;
class CHotel :public CUnitatiCazare
{
public:
	CHotel(){}
	CHotel(string denumire, string locatie, int clasificare, vector<CCamera>camere, vector<CMasa>mese, vector<CRecenzie>recenzii) :CUnitatiCazare(denumire, locatie, clasificare, camere, mese, recenzii) {}
	friend istream& operator >>(istream& in, CHotel& unitate);
	friend ostream& operator <<(ostream& out, CHotel& unitate);
	void print_descriere()override;
	void list_informatii_camere() override;
	string get_type() { return "Hotel"; }
};

