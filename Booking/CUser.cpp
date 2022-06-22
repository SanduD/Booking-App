#include "CUser.h"

ostream& operator<<(ostream& out, CUser &user)
{
    out << user.username << " " << user.password << " " << user.nr_rezervari<<"\n";
    return out;
}
