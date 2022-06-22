#include "CSolicitare.h"

ostream& operator<<(ostream& out, CSolicitare& rezervare)
{
	out<< rezervare.get_denumireCazare() << " " << rezervare.get_tip_camera() << " " << rezervare.get_nr_camere()
		<< " " <<rezervare.get_numeMasa()<<" " << rezervare.get_checkIn().zi << "." << rezervare.get_checkIn().luna << "." << rezervare.get_checkIn().an << " "
		<< rezervare.get_checkOut().zi << "." << rezervare.get_checkOut().luna << "." << rezervare.get_checkOut().an<<" "<<rezervare.get_status()<<" "<<rezervare.get_suma();
	return out;
}

istream& operator>>(istream& in, CSolicitare& rezervare)
{
	char ch;
	in >> rezervare.set_denumireCazare() >> rezervare.set_tip_camera() >> rezervare.set_nr_camere()
		>> rezervare.set_numeMasa();
	in >> rezervare.set_checkIn().zi >> ch >> rezervare.set_checkIn().luna >> ch >> rezervare.set_checkIn().an;
	in >> rezervare.set_checkOut().zi >> ch >> rezervare.set_checkOut().luna >> ch >> rezervare.set_checkOut().an;
	in >> rezervare.set_status()>>rezervare.set_suma();
	return in;
}
