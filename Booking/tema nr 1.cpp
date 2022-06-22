#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
#include "MyException.h"
using namespace std;

/* Date_Cazari este de forma: Tip(hotel/pensiune),Denumire,clasificare,tip_camera(single,duble,tripla,apartament)-nr_camere-pret,combinatii mese-pret,recenzii([Username]-rating:text_recenzie|) 
	baza_date_utilizatori : Username pass nr_rezervari
	Istoric_client: nume_cazare tip_camera nr_camere masa_aleasa check_in check_out status pret_total
	Rezervari.txt: nume_cazare tip_camera nr_camere check_in check_out
	Solicitari_admin: nume_cazare tip_camera nr_camere masa_aleasa check_in check_out status pret_total
*/
int main()
{
	try
	{
		Menu::running();
	}
	catch (MyException* exception)
	{
		cout <<endl<< exception->get_category() << ": " + exception->get_mesaj();
	}
}
