#include "orario.h"
class orario::orario_rapp
{
public:
    int sec;
};
orario::orario(int secondi) : punt(new orario_rapp) { punt->sec = secondi; };
orario::orario(int ore, int min, int secondi) : punt(new orario_rapp) { punt->sec = ore * 3600 + min * 60 + secondi; };
orario::orario() : punt(new orario_rapp) { punt->sec = 0; };
int orario::Ore() const { return punt->sec / 3600; };
int orario::Minuti() const { return (punt->sec / 60) % 60; };
int orario::Secondi() const { return punt->sec % 60; };
orario::orario OraDiPranzo() { return orario(13, 15); };
orario::orario orario::UnOraPiuTardi() const
{
    orario::orario aux = *this + 1;
    return aux;
};
void orario::AvanzaUnOra() { punt->sec = punt->sec + 3600 % 86400; }
orario::orario operator+(orario::orario const &o1, orario::orario const &o2){
    //orario::orario aux = (o1.sec + o2.sec) % 86400; sbagliato perche sec è privato!
    //return aux;
};
std::ostream &operator<<(std::ostream &os, orario::orario o)
{
    std::string ore, m, s;
    ore = o.Ore() < 10 ? '0' + o.Ore() : o.Ore();
    m = o.Minuti() < 10 ? '0' + o.Minuti() : o.Minuti();
    s = o.Secondi() < 10 ? '0' + o.Secondi() : o.Secondi();
    return os << ore << ":" << m << ":" << s << std::endl;
};
bool orario::operator==(orario o) const
{
    return punt->sec == o.punt->sec;
};
void orario::operator=(orario o)
{
    punt->sec = o.punt->sec;
}
orario::~orario()
{
    delete punt;
}
orario::orario(const orario &o) : punt(new orario_rapp)
{
    punt->sec = o.punt->sec;
}