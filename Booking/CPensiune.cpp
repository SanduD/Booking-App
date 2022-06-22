#include "CPensiune.h"

void CPensiune::print_descriere()
{
	cout << "Pensiunea " << get_denumire() << " este situata in orasul " << get_locatie() + " si are " << get_clasificare() << " margarete.";
    cout << " Recenzii clienti:";
    vector<CRecenzie>recenzii = get_recenzii();
    for (auto it = recenzii.begin(); it != recenzii.end(); it++)
        cout <<endl<< (*it).get_username() + "-" << (*it).get_rating() << " :" << (*it).get_text() << "|";
    cout << "\n\n";

}

void CPensiune::list_informatii_camere()
{
	cout << "------------------------------------\nAti selectat Pensiunea " << get_denumire() + "." << endl;
    CUnitatiCazare::list_informatii_camere();
}



istream& operator>>(istream& in, CPensiune& unitate)
{
    vector<CCamera>& camere= unitate.set_camere(); vector<CMasa>& mese=unitate.set_mese();
    CCamera c;
    CMasa m;
    cout << "Introduceti numele cazarii:\n";
    in >> unitate.set_denumire();
    cout << "Intoduceti locatia in care se afla cazarea:\n";
    in >> unitate.set_locatie();
    cout << "Introduceti numarul de margarete:\n";
    in >> unitate.set_clasificare();

    for (int i = 1; i <= 4; i++)
    {
        if (i == 1)
            cout << "Introduceti numarul de camere pentru o persoana si pretul per camera: ";
        else
            cout << "Introduceti numarul de camere pentru " << i << " persoane si pretul per camera: ";
        in >>c.set_nrCamere() >>c.set_pret() ;
        camere.push_back(c);
    }
    

    cout << "Introduceti optiunile de mese disponibile, raspunzand cu da/nu si pret(0, daca raspunsul este nu).\n";
    cout << "Mic Dejun: ";
    m.set_denumireMasa() = "mic_dejun";
    in >> m.set_disponibilitate() >> m.set_pretMasa();
    mese.push_back(m);
    cout << "Pranz: ";
    m.set_denumireMasa() = "pranz";
    in >> m.set_disponibilitate() >> m.set_pretMasa();
    mese.push_back(m);
    cout << "Cina: ";
    m.set_denumireMasa() = "cina";
    in >> m.set_disponibilitate() >> m.set_pretMasa();
    mese.push_back(m);
    cout << "Mic dejun si pranz: ";
    m.set_denumireMasa() = "mic_dejun si pranz";
    in >> m.set_disponibilitate() >> m.set_pretMasa();
    mese.push_back(m);
    cout << "Mic dejun si cina: ";
    m.set_denumireMasa() = "mic_dejun si cina";
    in >> m.set_disponibilitate() >> m.set_pretMasa();
    mese.push_back(m);
    return in;
   
}

ostream& operator<<(ostream& out, CPensiune& unitate)
{
    out << "\n" <<"Pensiune" << "," << unitate.get_denumire() << "," << unitate.get_locatie() << "," << unitate.get_clasificare() << ",";
    int i = 1;
    vector <CCamera> camere=unitate.get_camere();
    for (auto it = camere.begin(); it != camere.end(); it++)
         {
       out << i << "-" << (*it).get_nrCamere() << "-" << (*it).get_pret() << ",";
        i++;
         }
   vector<CMasa> mese=unitate.get_mese();
    for (auto it = mese.begin(); it != mese.end(); it++)
        {
        out << (*it).get_denumireMasa() + "-" + (*it).get_disponibilitate() + "-" << (*it).get_pretMasa()<< ",";
        }
    vector<CRecenzie>recenzii = unitate.get_recenzii();
    for (auto it = recenzii.begin(); it != recenzii.end(); it++)
        {
        out << (*it).get_username() + "-" << (*it).get_rating() << ": " << (*it).get_text() + "|";
        }
    return out;
}
