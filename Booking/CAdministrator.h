#pragma once
#include <string>
using namespace std;
class CAdministrator
{
private:
	static CAdministrator* instance;
	CAdministrator() {};
	CAdministrator(string name, string pass) :password(pass), name(name) {}
	~CAdministrator() {}
	string name;
	string password;
public:
	static CAdministrator& get_instance(string name,string pass);
	static void destroy_instance();
	string get_name() { return name; }
	string get_pass() { return password; }
};

