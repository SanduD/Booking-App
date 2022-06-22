#include "CUnitatiCazare.h"

CUnitatiCazare::CUnitatiCazare(string denumire, string locatie,int clasificare, vector<CCamera> camere, vector<CMasa> mese, vector<CRecenzie> recenzii)
{
  
    this->denumire = denumire;
    this->clasificare = clasificare;
    this->locatie = locatie;
    this->camere = camere;
    this->mese = mese;
    this->recenzii = recenzii;
}

string CUnitatiCazare::get_denumire ()const
{
    return denumire;
}

string CUnitatiCazare::get_locatie ()const
{
    return locatie;
}

vector<CMasa> CUnitatiCazare::get_mese()
{
    return mese;
}

vector<CCamera> CUnitatiCazare::get_camere ()const
{
    return camere;
}

vector<CCamera>& CUnitatiCazare::set_camere()
{
	return camere;
}


vector<CRecenzie> CUnitatiCazare::get_recenzii()const
{
    return recenzii;
}

void CUnitatiCazare::list_informatii_camere()
{
	cout << "Camerele disponibile pentru perioada selectata sunt:\n\n";
	int i = 1;
	for (auto jt = camere.begin(); jt != camere.end(); jt++)
	{
		switch (i)
		{
		case 1:
			cout << i << ". Camera single este la pretul de " << (*jt).get_pret() << " lei, si mai sunt disponibile " << (*jt).get_nrCamere() << ".\n";
			break;
		case 2:
			cout << i << ". Camera dubla este la pretul de " << (*jt).get_pret() << " lei, si mai sunt disponibile " << (*jt).get_nrCamere() << ".\n";
			break;
		case 3:
			cout << i << ". Camera tripla este la pretul de " << (*jt).get_pret() << " lei, si mai sunt disponibile " << (*jt).get_nrCamere() << ".\n";
			break;
		case 4:
			cout << i << ". Apartamentul este la pretul de " << (*jt).get_pret() << " lei, si mai sunt disponibile " << (*jt).get_nrCamere() << ".\n";
			break;
		}
		i++;
	}
}

void CUnitatiCazare::list_informatii_mese()
{
	int i = 1;
	for (auto it = mese.begin(); it != mese.end(); it++)
	{
		if ((*it).get_disponibilitate() == "da")
		{
			cout << i++ << "." << (*it).get_denumireMasa() << " care costa: " << (*it).get_pretMasa() << " lei pentru o persoana.\n";
		}
	}
}
int CUnitatiCazare::get_nr_locuri()
{
	int nr_total= 0;
	int i = 1;
	for (auto it = camere.begin(); it != camere.end(); it++)
	{
		nr_total += i * (*it).get_nrCamere();
		i++;
	}
	return nr_total;
}
int CUnitatiCazare::get_clasificare()const
{
	return clasificare;
}

//setteri
string& CUnitatiCazare::set_denumire()
{
	return denumire;
}

int& CUnitatiCazare::set_clasificare()
{
	return clasificare;
}

string& CUnitatiCazare::set_locatie()
{
	return locatie;
}

vector<CMasa>& CUnitatiCazare::set_mese()
{
	return mese;
}

vector<CRecenzie>& CUnitatiCazare::set_recenzii()
{
	return recenzii;
}
