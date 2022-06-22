#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <fstream>
#include <vector>
#include <set>
#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include "CHotel.h"
#include "CPensiune.h"
#include "CSolicitare.h"
#include "MyException.h"
using namespace std;
#define DIM_X 30
#define DIM_Y 7

const int monthDays[12]
= { 31, 28, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31 };
vector<CUser> utilizatori;
int nr_rezervari_client_curent;
vector <IUnitatiCazare*> unitati_cazare;
vector <CRezervare*> rezervari;
vector <IUnitatiCazare*> unitati_disponibile;
vector <CSolicitare>solicitari;
vector<CSolicitare>istoric_client;
CUser utilizator_curent;
void welcome()
{
	string mesaj = "Welcome to Booking ATM.";
	string credit = "Made by Dragos.";
	for (int i = 0; i < DIM_X; i++)
	{
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < DIM_Y; i++, cout << endl)
	{
		for (int j = 0; j < DIM_X; j++)
		{
			if (j == 0 || j == DIM_X - 1)
				cout << "#";
			else
			{
				if (i == DIM_Y / 2 && j == DIM_X / 2 - mesaj.length() / 2)
				{
					cout << mesaj;
					j += mesaj.length() - 1;
				}
				else
				{
					if (i == DIM_Y - 1 && j == DIM_X - credit.length() - 2)
					{
						cout << credit;
						j += credit.length() - 1;
					}
					else
						cout << " ";
				}
			}
		}

	}
	for (int i = 0; i < DIM_X; i++)
	{
		cout << "#";
	}
}

date split_date(string data)
{
	date result;
	result.zi = stoi(data.substr(0, 2));
	result.luna = stoi(data.substr(3, 2));
	result.an = stoi(data.substr(6, 4));
	return result;
}

//read functions
void read_users(const char* filename)
{
	ifstream file(filename);
	string name, pass;
	int nr_rez;
	if (file.is_open())
	{
		while (file.good())
		{
			file >> name >> pass>>nr_rez;
			CUser tmp_user(name, pass,nr_rez);
			utilizatori.push_back(tmp_user);
		}
	}
	else
	{
		throw new MyException("Eroare la deschiderea fisierului.", "Eroare");
	}
	file.close();
}

void read_unitati_cazare(const char*filename)
{
	
	ifstream file(filename);
	
	string type;
	string denumire;
	string locatie;
	int clasificare;
	string aux;
	
	int k = 0;
	if (file.is_open())
	{
		while (file.good())
		{
			vector <CCamera>camere;
			vector<CMasa>mese;
			vector<CRecenzie>recenzii;
			getline(file, type, ',');
			if (k >= 1)
				type = type.substr(1, type.size() - 1);
			getline(file, denumire, ',');
			getline(file, locatie, ',');
			getline(file, aux, ',');
			clasificare = stoi(aux);
			//citire camere
			for (int i = 0; i < 4; i++)
			{
				int nr_camere;
				double pret;
				getline(file, aux, '-');
				getline(file, aux, '-');
				nr_camere = stoi(aux);
				getline(file, aux, ',');
				pret = stoi(aux);
				CCamera c(nr_camere,pret);
				camere.push_back(c);
			}

			//citire mese

			for (int i = 0; i < 5; i++)
			{
				string denumire_masa, disponibilitate;
				double pret;
				getline(file, aux, '-');
				denumire_masa = aux;
				getline(file, aux, '-');
				disponibilitate = aux;
				getline(file, aux, ',');
				pret = stoi(aux);
				CMasa m(denumire_masa, disponibilitate, pret);
				mese.push_back(m);
			}

			//citire recenzii
			while (file.peek() != '\n' && file.good())
			{
				string username; double rating; string text;
				getline(file, aux, '-');
				username = aux;
				getline(file, aux, ':');
				rating = stoi(aux);
				getline(file, aux, '|');
				text = aux;
				CRecenzie r(username, rating, text);
				recenzii.push_back(r);

			}
			
			if (type == "Hotel")
			{
				unitati_cazare.push_back(new CHotel(denumire, locatie, clasificare, camere, mese, recenzii));
			}
			else
				unitati_cazare.push_back(new CPensiune(denumire, locatie, clasificare, camere, mese, recenzii));
			k++;
			
		}
	}
	else
	{
		throw new MyException("Eroare la deschiderea fisierului.", "Eroare");
	}

	file.close();
}

void read_rezervari(const char* filename)
{
	ifstream file(filename);
	string check_in, check_out, nume_cazare;
	int tip_camera, nr_camere;
	date in, out;
	if (file.is_open())
	{
		while (file.good())
		{
			CRezervare* r=new CRezervare();
			file >> *r;
			rezervari.push_back(r);
		}
	}
	else
		throw new MyException("Eroare la deschiderea fisierului.", "Eroare");
	file.close();
}

void read_solicitari(string filename)
{
	ifstream file(filename);
	bool ok = false;
	if (file.is_open())
	{
		while (file.good())
		{
			CSolicitare istoric;
			file >> istoric;
			istoric_client.push_back(istoric);
		}
	}
	else
		throw MyException("Fisierul nu s-a putut deschide.", "Eroare");
}
CUser& find_user(string username)
{
	for (auto it = utilizatori.begin(); it != utilizatori.end(); it++)
	{
		if ((*it).get_name() == username)
			return *it;
	}
	exit(-1);
}
void verifica_solicitari(CSolicitare s)
{
	int i = 1;
	if (s.get_status() == "waiting")
	{
		cout <<s;
		cout << "\nY/N?";
		char choice;
		cin >> choice;
		if (choice == 'Y')
		{
			s.set_status() = "approved";
			CRezervare rezervare(s.get_denumireCazare(), s.get_tip_camera(), s.get_nr_camere(), s.get_checkIn(), s.get_checkOut());
			ofstream file("Rezervari.txt",ofstream::app);
			file <<"\n"<< rezervare;
			file.close();
			CUser& user = find_user(s.get_username());
			user.set_rezervari() += 1;
		}
		else
		{
			if(choice=='N')
				s.set_status() = "rejected";
		}
		string filename ="Istoric_"+ s.get_username()+".txt";
		ofstream file(filename,ofstream::app);
		file <<"\n"<< s;
		file.close();
	}
}

void read_solicitari(const char* filename)
{
	ifstream file(filename);
	char ch;
	if (file.is_open())
	{
		while (file.good())
		{
			CSolicitare s;
			file >> s.set_username();
			file >> s;
			verifica_solicitari(s);
		}
	}
	else
		throw new MyException("Fisierul nu s-a putut deschide.", "Eroare");
	file.close();
	ofstream file2(filename);
	file2.close();
}
//Login and register functions
bool verifica_utilizator(string name, string pass)
{
	for (auto it = utilizatori.begin(); it != utilizatori.end(); it++)
	{
		if ((*it).get_name() == name && (*it).get_pass() == pass)
		{
			CUser utilizator(name, pass, (*it).get_rezervari());
			utilizator_curent = utilizator;
			return true;
		}
	}
	return false;
}

void read_password(string& password)
{
	char pass[26];
	int p = 0;
	char ch;
	do {
		ch = _getch();
		if (ch == '\b' && p>1)
		{
			pass[--p] = '\0';
			cout << "\b \b";
		}
		else
		{
			pass[p] = ch;
			if (pass[p] != 13) {
				cout << "*";
			}
			p++;
		}
		
	} while (pass[p - 1] != 13);
	pass[p - 1] = '\0';
	password = pass;
}

void Log_in(string& tmp_name, string& tmp_pass)
{
	string name;
	cout << "Username: ";
	cin >> name;
	cout << "Password: ";
	string pass;
	read_password(pass);

	tmp_name = name;
	tmp_pass = (string)pass;
}

void Log_in_Admin()
{
	cout << "\nVa rugam introduceti datele Administratorului.\nUsername: ";
	string name, pass;
	cin >> name;
	cout << "Parola: ";
	read_password(pass);
	CAdministrator &admin=CAdministrator::get_instance(name, pass);
	auto check_admin = [](string name, string pass) {return (name == "admin" && pass == "admin"); };
	if (check_admin(name,pass))
		cout << "\nAdministratorul s-a logat cu succes.\n";
	else
	{
		int count = 1;
		while (count != 3)
		{
			cout << "\nUsername-ul sau parola Administratorului sunt gresite.\nMai aveti " << 3 - count << " incercari.\n";
			Log_in(name, pass);
			if (check_admin(name, pass))
			{
				cout << "\nAdministratorul s-a logat cu succes.\n";
				break;
			}
			else
				count++;
		}

		if (count == 3)
		{
			cout << "\nIncercarile dumneavoastra de autentificare au esuat. Va rugam sa incercati mai tarziu.\n";
			throw new MyException("Eroare la autentificare.", "Alerta");
		}
			
	}
}

bool compare_dates(date d1, date d2)
{
	if (d1.luna > d2.luna)
		return true;
	else
	{
		if (d1.luna == d2.luna && d1.zi >= d2.zi)
			return true;
	}
	return false;
}

bool check_dates_overlap(date startA, date endA, date startB, date endB)
{
	if (compare_dates(startA, endB) == false && compare_dates(startB, endA) == false)
		return true;
	else
		return false;
}

#pragma region Utilizator
//check dates

void Credentiale()
{
	cout << "\nCe operatiune doriti sa efectuati?\n1. Login.\n2. Crearea unui cont nou de utilizator.\n";
	int nr; cin >> nr;
	if (nr == 1)
	{
		cout << "\nPentru a continua va rugam sa va introduceti datele de logare:\n";
		string name, pass;
		Log_in(name, pass);
		int count = 1;
		if (verifica_utilizator(name, (string)pass) == true)
		{
			cout << endl << "V-ati autentificat cu succes!\n";
			cout << "Meniul pentru utilizatori se incarca...";
			std::this_thread::sleep_for(std::chrono::milliseconds(2500));
			system("cls");
		}
		else
		{
			while (count != 3)
			{
				cout << "\nUsername-ul sau parola sunt gresite." << endl;
				cout << "Mai aveti " << 3 - count << " incercari." << endl;
				Log_in(name, pass);
				if (verifica_utilizator(name, pass) == true)
				{
					cout << "\nV-ati autentificat cu succes!\n";
					cout << "Meniul pentru utilizatori se incarca...";
					std::this_thread::sleep_for(std::chrono::milliseconds(2500));
					system("cls");
					break;
				}
				else
					count++;
			}
			if (count == 3)
			{
				cout << "\nIncercarile dumneavoastra de autentificare au esuat. Va rugam sa incercati mai tarziu.\n";
				throw new MyException("Eroare la autentificare.", "Alerta");
			}

		}
	}
	else
	{
		string aux_name, aux_pass;
		cout << "Introduceti Username-ul contului:\n";
		cin >> aux_name;
		cout << "Introduceti parola contului:\n";
		read_password(aux_pass);

		ofstream file;
		file.open("baza_date_utilizatori.txt", ofstream::app);
		file << endl << aux_name + " " + aux_pass << " " << 0;
		cout << "\nContul a fost creat cu succes.\n";
	}

}
bool isValidDate(date data)
{
	int d = data.zi, m = data.luna, y = data.an;
	if (y <= 2021 || y >= 2023)
		return false;
	if (m < 1 || m > 12)
		return false;
	if (d < 1 || d > 31)
		return false;
	if (m == 2)
	{
		auto loop_year = [](int y) {return (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)); };
		if (loop_year(y))
			return (d <= 29);
		else
			return (d <= 28);
	}
	if (m == 4 || m == 6 ||m == 9 || m == 11)
		return (d <= 30);
	return true;
}

int dayofweek(int date, int month, int year)
{
	static int t[] = { 0, 3, 2, 5, 0, 3,
					   5, 1, 4, 6, 2, 4 };//magic month array
	year -= month<3;
	return (year + year / 4 -year/100+year/400+ date + t[month - 1]) % 7;
}

bool verifica_date_cazare(date in, date out)
{
	if (out.zi < in.zi || out.luna < in.luna || out.an < in.an)
		return false;
	return isValidDate(in) && isValidDate(out);
}

double bonusFidelitate(int nr_rezervari)
{
	if (nr_rezervari == 0)
		return 0;
	if (nr_rezervari > 5)
		return 0.18;
	if (nr_rezervari == 1)
		return 0.02;
	else
		return 0.02 + 0.04 * nr_rezervari;
}

void pret_final(double& pret,date check_in,date check_out)
{
	int nr_zile=0;
	int nr_zile_weekend = 0;
	if (check_in.luna == check_out.luna)
	{
		for (int i = check_in.zi; i<= check_out.zi-1; i++)
		{
			auto checkWeekday = [](int day) {return (day == 0) || (day == 6);  };

			if (checkWeekday(dayofweek(i, check_in.luna, 2022)))
				nr_zile_weekend++;
			else
				nr_zile++;
		}
	}
	else
	{
		if (check_in.luna < check_out.luna)
		{
			for (int i = check_in.zi; i != check_out.zi-1; i++)
			{
				i = i % monthDays[check_in.luna];
				auto checkWeekday = [](int day) {return (day == 0) || (day == 6);  };

				if (checkWeekday(dayofweek(i, check_in.luna, 2022)))
					nr_zile_weekend++;
				else
					nr_zile++;
			}
		}
	}
	pret= pret*(nr_zile + nr_zile_weekend * 1.25)-pret*bonusFidelitate(utilizator_curent.get_rezervari());
}

//check for booking

void check_unitati_disponibile(date start,date end)
{

	unitati_disponibile = unitati_cazare;
	for (auto it = unitati_disponibile.begin(); it != unitati_disponibile.end(); it++)
	{
		vector <CCamera>& camere_disponibile = (*it)->set_camere();
		for (auto rez = rezervari.begin(); rez != rezervari.end(); rez++)
		{
			if ((*it)->get_denumire() == (*rez)->get_denumireCazare())
			{
				if (check_dates_overlap(start, end, (*rez)->get_checkIn(), (*rez)->get_checkOut()) == true)
				{
					camere_disponibile[(*rez)->get_tip_camera() - 1].set_nrCamere() -= (*rez)->get_nr_camere();
				}
			}
		}
	}
}

void display_unitati_disponibile(string locatie)
{
	int i = 1;
	for (auto it = unitati_disponibile.begin(); it != unitati_disponibile.end(); it++)
	{
		if ((*it)->get_locatie() == locatie)
			(*it)->print_descriere();
	}
}

IUnitatiCazare* find_unitate(string denumire)
{
	for (auto it = unitati_disponibile.begin(); it != unitati_disponibile.end(); it++)
	{
		if ((*it)->get_denumire() == denumire)
		{
			return *it;
		}
	}
	throw new MyException("Unitatea de cazare nu a fost gasita.", "Eroare");
}

void display_orase_disponibile()
{
	set<string>orase;
	int i = 0;
	cout << "(";
	for (auto it = unitati_disponibile.begin(); it != unitati_disponibile.end(); it++)
	{
		orase.insert((*it)->get_locatie());
	}
	for (auto it = orase.begin(); it != orase.end(); it++)
	{
		if (i != orase.size() - 1)
			cout << (*it) << ",";
		else
			cout << (*it) << "):\n";
		i++;
	}
	
}

CMasa find_masa(IUnitatiCazare* unitate,string nume_masa)
{
	vector<CMasa> mese=unitate->get_mese();
	for (auto it = mese.begin(); it != mese.end(); it++)
	{
		if ((*it).get_denumireMasa() == nume_masa)
		{
			return (*it);
		}
	}
	throw new MyException("Masa nu a fost gasita.", "Eroare");
}

void book_aRoom(int tip,int nr_camere,IUnitatiCazare* unitate,double& pret,string&nume_masa)
{
	pret = 0;//pretul pentru o noapte de cazare
	pret += unitate->get_camere()[tip - 1].get_pret() * nr_camere;
	switch (tip)
	{
	case 1:
		cout << "Ati selectat sa rezervati " << nr_camere << " camere single.\n\n";
		break;
	case 2:
		cout << "Ati selectat sa rezervati " << nr_camere << " camere pentru 2 persoane.\n\n";
		break;
	case 3:
		cout << "Ati selectat sa rezervati " << nr_camere << " camere pentru 3 persoane.\n\n";
		break;
	case 4:
		cout << "Ati selectat sa rezervati " << nr_camere << " camere pentru 4 persoane.\n\n";
		break;
	}
	cout << "Va rugam sa selectati una dintre optiunile pentru mese de mai jos(numele acestora) sau raspundeti cu N daca nu doriti:\n\n";
	unitate->list_informatii_mese();
	int nr_persoane;
	cin.ignore();
	getline(cin, nume_masa);
	if (nume_masa == "N")
		return;


	cout << "Introduceti numarul de persoane care doresc sa ia masa:";
	cin >> nr_persoane;
	CMasa masa_selectata = find_masa(unitate, nume_masa);
	pret += masa_selectata.get_pretMasa() * nr_persoane;
}

void Book()
{
	date check_in, check_out;
	while (true)
		{
			cout << "Te rugam sa introduci data de check-in si de check-out, conform formatului(zz.ll.aaaa):\n";
			string date_in, date_out;
			cin >> date_in >> date_out;
			check_in = split_date(date_in); check_out = split_date(date_out);
			if (verifica_date_cazare(check_in, check_out))
				break;
			else
			{
				cout << "Datele de check-in si check-out sunt gresite. \n";
			}
		}
	check_unitati_disponibile(check_in, check_out);
	cout << "\nVa rugam sa introduceti unul dintre orasele disponibile";
	display_orase_disponibile();
	string locatie;
	cin >> locatie;
	cout << "Loading...\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	cout << "Locatiile disponibile conform datelor introduse sunt:\n";
	display_unitati_disponibile(locatie);
	cout << "--------------------------------\nIntrodu numele unitatii de cazare pentru a continua: ";
	string nume_unitate;
	cin >> nume_unitate;
	IUnitatiCazare* unitate= find_unitate(nume_unitate);
	unitate->list_informatii_camere();
	cout << "\n\nAlegeti tipul[1-4] si numarul de camere pe care doriti sa il rezervati:\n";
	int tip, nr_camere;
	cin >> tip >> nr_camere;
	double pret;
	string nume_masa;
	book_aRoom(tip, nr_camere,unitate,pret,nume_masa);

	for (auto it = istoric_client.begin(); it != istoric_client.end(); it++)
	{
		CSolicitare istoric = *it;
		if (istoric.get_checkIn().zi == check_in.zi && istoric.get_checkIn().luna == check_in.luna && istoric.get_checkOut().zi == check_out.zi && istoric.get_checkOut().luna == check_out.luna
			&& istoric.get_denumireCazare() == unitate->get_denumire() && istoric.get_tip_camera() == tip && istoric.get_nr_camere() == nr_camere && istoric.get_numeMasa() == nume_masa)
			throw new MyException("Utilizatorul a ales aceleasi optiuni ca intr-o rezervare anterioara.", "Rezervare");
	}
	//calculeaza pret_final
	pret_final(pret, check_in, check_out);
	cout << "Pretul final al rezervarii este de: " << pret << endl;
	cout << "----------------------------------\nRezervarea a fost efectuata cu succes. In scurt timp un administrator o va aproba sau respinge. \n";
	//afisare rezervare in fisier admin pentru a aproba

	ofstream file("Solicitari_admin.txt", ofstream::app);
	if(!file.is_open())
		throw new MyException("Fisierul nu s-a putut deschide.", "Eroare");
	CSolicitare rezervare_client(utilizator_curent.get_name(), nume_unitate, tip, nr_camere, nume_masa, check_in, check_out, "waiting",pret);
	file <<"\n"<< utilizator_curent.get_name()<<" " << rezervare_client;
	file.close();

}

void print_istoric(string filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		while (file.good())
		{
			CSolicitare istoric;
			file >> istoric;
			cout << istoric<<endl;
		}
	}
	else
	{
		cout << "Nu nicio rezervare facuta.\n";
	}
}
#pragma endregion

void adaugare_cazare()
{
	ofstream file;
	file.open("Date_cazari.txt", ofstream::app);
	if (!file.is_open())
		throw new MyException("Fisierul nu s-a putut deschide.", "Eroare");
	cout << "Pentru adaugarea unei unitati de cazare este necesar sa introduceti urmatoarele date:\n";
	cout << "Introduceti tipul cazarii(Hotel/Pensiune):\n";
	string type;
	cin >> type;
	if (type == "Hotel")
	{
		CHotel tmp_hotel;
		cin >> tmp_hotel;
		unitati_cazare.push_back(new CHotel(tmp_hotel.get_denumire(),tmp_hotel.get_locatie(),tmp_hotel.get_clasificare(),tmp_hotel.get_camere(),tmp_hotel.get_mese(),tmp_hotel.get_recenzii()));
		file << tmp_hotel;
	}
	else
	{
		CPensiune tmp_pensiune;
		cin >> tmp_pensiune;
		unitati_cazare.push_back(new CHotel(tmp_pensiune.get_denumire(), tmp_pensiune.get_locatie(), tmp_pensiune.get_clasificare(), tmp_pensiune.get_camere(), tmp_pensiune.get_mese(), tmp_pensiune.get_recenzii()));
		file << tmp_pensiune;
	}
}

void list_unitati_cazare()
{
	int i = 0;
	cout << "(";
	for (auto it = unitati_cazare.begin(); it != unitati_cazare.end(); it++)
	{
		if (i != unitati_cazare.size()-1)
		{
			cout << (*it)->get_denumire() << ", ";
		}
		else
		{
			cout << (*it)->get_denumire();
		}
		i++;
	}
	cout << ").\n";
}
#pragma region Administrator
typedef struct
{
	string nume_cazare;
	int nr_aparitii;
}top;

int nr_aparitii_cazare(IUnitatiCazare* unitate,int luna)
{
	int count = 0;
	for (auto it = rezervari.begin(); it != rezervari.end(); it++)
	{
		if (((*it)->get_checkIn().luna == luna || (*it)->get_checkOut().luna == luna) && (unitate->get_denumire() == (*it)->get_denumireCazare()))
		{
			count++;
		}
	}
	return count;
}

void top_cazari()
{
	vector<top>cazari;
	cout << "Introduceti luna pentru care doriti sa afisati topul unitatilor rezervate:\n";
	int luna;
	cin >> luna;

	for(auto it=unitati_cazare.begin();it!=unitati_cazare.end();it++)
	{
		top tmp;
		tmp.nume_cazare = (*it)->get_denumire();
		tmp.nr_aparitii = nr_aparitii_cazare((*it), luna);
		cazari.push_back(tmp);
	}
	sort(cazari.begin(), cazari.end(), [](top a, top b) {return a.nr_aparitii > b.nr_aparitii; });
	int i = 1;
	for_each(cazari.begin(), cazari.end(), [&i](top a) {cout << i++ << ". " << a.nume_cazare << " a avut " << a.nr_aparitii << " solicitari in perioada selectata." << endl; });
}

IUnitatiCazare* find_cazare(string name)
{
	for (auto it = unitati_cazare.begin(); it != unitati_cazare.end(); it++)
	{
		if ((*it)->get_denumire() == name)
		{
			return *it;
		}
	}
}
void grad_ocupare()
{
	cout << "Introduceti numele unitatii de cazare din cele disponibile";
	list_unitati_cazare();
	string nume_cazare; cin >> nume_cazare;
	cout << "Introduceti data(zz.ll.an) pentru care doriti statistica:\n";
	date d;
	char ch;
	cin >> d.zi >> ch >> d.luna >> ch >> d.an;
	IUnitatiCazare* unitate = find_cazare(nume_cazare);
	int nr_camere_rezervate = 0;
	for (auto it = rezervari.begin(); it != rezervari.end(); it++)
	{
		if ((*it)->get_denumireCazare() == nume_cazare && check_dates_overlap(d, d, (*it)->get_checkIn(), (*it)->get_checkOut()) == true)
		{
			nr_camere_rezervate += (*it)->get_tip_camera() * (*it)->get_nr_camere();
		}
	}
	cout << "Gradul de ocupare este de " << (float)nr_camere_rezervate / unitate->get_nr_locuri() * 100 <<"%"<< endl;
}

void pret_mediu_cazari()
{
	cout << "Introduceti luna pentru care doriti pretul mediu al cazarilor:\n";
	int luna;
	cin >> luna;
	int nr_total_camere=0;
	double pret=0;
	for (auto it = rezervari.begin();it != rezervari.end(); it++)
	{
		if (luna==(*it)->get_checkIn().luna || luna==(*it)->get_checkOut().luna)
		{
			nr_total_camere += (*it)->get_nr_camere();
			IUnitatiCazare* unitate = find_cazare((*it)->get_denumireCazare());
			pret += unitate->get_camere()[(*it)->get_tip_camera() - 1].get_pret()*(*it)->get_nr_camere();
		}
	}
	cout << "Pretul mediu al cazarilor efectuate este de: " << pret / nr_total_camere<<endl;
}



void update_istoricFile(string filename)
{
	ofstream file(filename);
	if (file.is_open())
		for_each(istoric_client.begin(), istoric_client.end(), [&](CSolicitare istoric) {file << "\n" << istoric; });
	else
		throw MyException("Fisierul nu s-a putut deschide.", "Eroare");
	file.close();

}

void update_unitatiCazare_file(string filename)
{
	ofstream file(filename);
	for (auto it = unitati_cazare.begin(); it!= unitati_cazare.end(); it++)
	{
		file << "\n";
		IUnitatiCazare* unitate = *it;
		file << unitate->get_type() << "," << unitate->get_denumire() << "," << unitate->get_locatie() << "," << unitate->get_clasificare() << ",";
		int i = 1;
		vector <CCamera> camere = unitate->get_camere();
		for (auto it = camere.begin(); it != camere.end(); it++)
		{
			file << i << "-" << (*it).get_nrCamere() << "-" << (*it).get_pret() << ",";
			i++;
		}
		vector<CMasa> mese = unitate->get_mese();
		for (auto it = mese.begin(); it != mese.end(); it++)
		{
			file << (*it).get_denumireMasa() + "-" + (*it).get_disponibilitate() + "-" << (*it).get_pretMasa() << ",";
		}
		vector<CRecenzie>recenzii = unitate->get_recenzii();
		for (auto it = recenzii.begin(); it != recenzii.end(); it++)
		{
			file << (*it).get_username() + "-" << (*it).get_rating() << ": " << (*it).get_text() + "|";
		}
	}
	file.close();
}

void check_for_review()
{
	bool ok = false;
	for (auto it = istoric_client.begin(); it != istoric_client.end(); it++)
	{
		CSolicitare& istoric = *it;
		if (istoric.get_status() == "approved")
		{
			ok = true;
			cout << "\nUltima dumneavoastra vizita a fost la " << istoric.get_denumireCazare() << ". Doriti sa le lasati un review? (Y/N): ";
			string choice; cin >> choice;
			if (choice == "Y")
			{
				istoric.set_status() = "approved_and_reviewed";
				IUnitatiCazare* unitate = find_cazare(istoric.get_denumireCazare());
				string nume_utilizator = "[" + utilizator_curent.get_name() + "]";
				CRecenzie recenzie(nume_utilizator);
				cin >> recenzie;
				unitate->set_recenzii().push_back(recenzie);
			}
		}
	}
	if(ok==false)
		cout << "Nu aveti nicio recenzie de oferit.\n";
	else
	{
		string filename = "Istoric_" + utilizator_curent.get_name() + ".txt";
		update_istoricFile(filename);
		update_unitatiCazare_file("Date_Cazari.txt");
	}

}

void update_usersFile(string filename)
{
	ofstream file(filename);
	if (file.is_open())
	{
		for (auto it = utilizatori.begin(); it != utilizatori.end(); it++)
			file << *it;
	}
	file.close();

}

void Meniu_Admin()
{
	Log_in_Admin();
	cout << "\nAlegeti una dintre variantele de mai jos:\n1. Adauga o noua cazare.\n2.Raspunde la solicitari.\n3.Afiseaza topul unitatilor de cazare solicitate.\n4.Afiseaza gradul de ocupare al unei unitati de cazare."
		<<"\n5.Afiseaza pretul mediu al cazarilor efectuate.\n";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		adaugare_cazare();
		break;
	case 2:
		cout << "\nAprobati sau respingeti solicitarile raspunzand cu Y/N.\n";
		read_solicitari("Solicitari_admin.txt");
		update_usersFile("baza_date_utilizatori.txt");
		break;
	case 3: 
		top_cazari();
		break;
	case 4:
		grad_ocupare();
		break;
	case 5:
		pret_mediu_cazari();
		break;
	}
	cout << "Apasa orice tasta pentru a reincepe\n";
	char ch2 = _getch();
	system("cls");
}
#pragma endregion

void Meniu_User()
{
	Credentiale();
	read_solicitari("Istoric_" + utilizator_curent.get_name() + ".txt");
	cout << "Meniu utilizator:\n1.Cauta o cazare.\n2.Afiseaza istoricul rezervarilor tale.\n3.Lasa un review pentru cazarile la care ai fost.\n";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "!!! Rezervarile se pot face doar pentru anul 2022 si pe o perioada de maxim 28 de zile.\n";
		Book();
	
		
		break;
	case 2:
	{
		cout << "Istoricul clientului " << utilizator_curent.get_name() << " este:\n";
		string filename = "Istoric_" + utilizator_curent.get_name() + ".txt";
		print_istoric(filename);
		break;
	}
		
	case 3:
		check_for_review();
		break;
	}
	cout << "Apasa orice tasta pentru a reincepe\n";
	char ch = _getch();
	system("cls");
}


void Menu::running()
{
	read_users("baza_date_utilizatori.txt");
	read_unitati_cazare("Date_Cazari.txt");
	read_rezervari("Rezervari.txt");
	while (true)
	{

			welcome();
			cout << "\nAlegeti o optiune de conectare din cele de mai jos:\n1.User.\n2.Administrator.\n0.Exit.\n";
			int choice;
			cin >> choice;
			switch (choice)
			{
			case 1:
				Meniu_User();
				break;
			case 2:
				Meniu_Admin();
				break;
			case 0:
				cout << "Sa aveti o zi buna in continuare!";
				break;
			}
			if (choice == 0)
				break;
	}
}
