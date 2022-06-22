#pragma once
#include "IUnitatiCazare.h"
#include <iostream>
using namespace std;

class CUnitatiCazare :public IUnitatiCazare
{
	string denumire;
	string locatie;
	int clasificare=0;
	vector<CRecenzie> recenzii;
	vector <CMasa> mese;
	vector <CCamera> camere;
public:
	CUnitatiCazare(){}
	CUnitatiCazare(string denumire,string locatie, int clasificare, vector<CCamera>camere, vector<CMasa>mese, vector<CRecenzie>recenzii);
	//getteri
	string get_denumire() const override;
	string get_locatie()const override;
	int get_clasificare()const override;
	vector <CMasa> get_mese() override;
	vector <CCamera> get_camere()const override;
	vector<CRecenzie>get_recenzii()const override;
	void list_informatii_camere() override;
	void list_informatii_mese() override;

	int get_nr_locuri()override;
	//setteri

	 string& set_denumire();
	 int& set_clasificare() ;
	 string& set_locatie() ;
	 vector<CMasa>& set_mese() ;
	 vector <CRecenzie>& set_recenzii();
	 vector <CCamera>& set_camere() override;
	
	
};

