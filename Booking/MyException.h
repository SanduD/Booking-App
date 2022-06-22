#pragma once
#include <iostream>
#include <string>
using namespace std;
class MyException
{
	string category;
	string mesaj;
public:
	MyException(string mesaj, string category) :mesaj{ mesaj },category{category}{}
	string get_category() { return category; }
	string get_mesaj() { return mesaj; }
};

