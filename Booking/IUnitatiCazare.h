#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#include "CUser.h"
#include "CCamera.h"
#include "CMasa.h"
#include "CRecenzie.h"
#include "CRezervare.h"
class IUnitatiCazare
{
public:
	virtual string get_type() = 0;
	virtual string get_denumire() const= 0;
	virtual int get_clasificare() const = 0;
	virtual string get_locatie() const= 0;
	virtual vector <CMasa> get_mese() = 0;
	virtual vector <CCamera> get_camere()const = 0;
	virtual vector<CRecenzie> get_recenzii()const = 0;
	virtual void list_informatii_camere()= 0;
	virtual void print_descriere() = 0;
	virtual void list_informatii_mese() = 0;
	virtual int get_nr_locuri() = 0;

	virtual string& set_denumire() = 0;
	virtual int& set_clasificare() = 0;
	virtual string& set_locatie() = 0;
	virtual vector<CMasa>& set_mese() = 0;
	virtual vector <CRecenzie>& set_recenzii() = 0;
	virtual vector <CCamera>& set_camere() = 0;

};

