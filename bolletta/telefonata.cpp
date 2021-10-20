#include "telefonata.h"

telefonata::telefonata(orario i, orario f, std::string n) : inizio(i), fine(f), nr(n){};
telefonata::telefonata() : nr(0){};
orario telefonata::GetInizio() const { return inizio; };
orario telefonata::GetFine() const { return fine; };
std::string telefonata::GetNumero() const { return nr; };
bool telefonata::operator==(const telefonata &t) const
{
    return GetNumero() == t.GetNumero() && GetInizio() == t.GetInizio() && GetFine() == t.GetFine();
}
std::ostream &operator<<(std::ostream &os, const telefonata &t)
{
    return os << "inizio : " << t.GetInizio() << "fine : " << t.GetFine() << "numero : " << t.GetNumero();
};