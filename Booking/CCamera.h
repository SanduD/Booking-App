#pragma once
class CCamera
{
	int nr_camere=0;
	double pret=0;
public:
	CCamera() {}
	CCamera(int nr_camere, double pret) :nr_camere(nr_camere), pret(pret) {}
	int get_nrCamere() { return nr_camere; }
	double get_pret() { return pret; }

	int &set_nrCamere() { return nr_camere; }
	double& set_pret() { return pret; }
};

