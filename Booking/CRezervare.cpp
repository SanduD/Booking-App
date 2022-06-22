#include "CRezervare.h"

ostream& operator<<(ostream& out, CRezervare& rezervare)
{
	out << rezervare.get_denumireCazare() << " " << rezervare.get_tip_camera() << " " << rezervare.get_nr_camere() << " " << rezervare.get_checkIn().zi << "." << rezervare.get_checkIn().luna << "." << rezervare.get_checkIn().an << " " << rezervare.get_checkOut().zi << "." << rezervare.get_checkOut().luna << "." << rezervare.get_checkOut().an;
	return out;
}

istream& operator>>(istream& in, CRezervare& rezervare)
{
	char ch;
	in >> rezervare.set_denumireCazare() >> rezervare.set_tip_camera() >> rezervare.set_nr_camere();
	in >> rezervare.set_checkIn().zi >> ch >> rezervare.set_checkIn().luna >> ch >> rezervare.set_checkIn().an;
	in >> rezervare.set_checkOut().zi >> ch >> rezervare.set_checkOut().luna >> ch >> rezervare.set_checkOut().an;
	return in;
}
