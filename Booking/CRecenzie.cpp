#include "CRecenzie.h"

istream& operator>>(istream& in, CRecenzie& recenzie)
{
    cout << "\nIntroduceti ratingul (0-5) cazarii: "; in >> recenzie.set_rating();
    cout << "\nVa rugam sa scrieti review: "; cin.ignore(); getline(in, recenzie.set_text());
    return in;
}
