#include "CAdministrator.h"
CAdministrator* CAdministrator::instance = nullptr;
CAdministrator& CAdministrator::get_instance(string name, string pass)
{
    if (!instance)
    {
        instance = new CAdministrator(name,pass);
    }
    return *instance;
}
void CAdministrator::destroy_instance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}
