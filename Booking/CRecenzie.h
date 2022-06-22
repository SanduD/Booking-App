#pragma once
#include <string>
#include <iostream>
using namespace std;
class CRecenzie
{
	string username;
	double rating=0.0f;
	string text;
public:
	CRecenzie() {}
	CRecenzie(string username, double rating=0, string text="") :username{username}, rating{rating}, text{text}{}
	string get_username() { return username; }
	double get_rating() { return rating; }
	string get_text() { return text; }

	string& set_username() { return username; }
	double& set_rating() { return rating; }
	string& set_text() { return text; }

	friend istream& operator >>(istream& in, CRecenzie& recenzie);
};

