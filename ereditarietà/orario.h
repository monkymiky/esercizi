//orario.h
#ifndef ORARIO_H
#define ORARIO_H
#include <iostream>
#include <string>

class orario
{
public:
    orario(int, int, int = 0);
    int Ore() const;
    int Minuti() const;
    int Secondi() const;
    bool operator==(orario) const;
    orario(const orario &);
    friend orario operator+(orario const &, orario const &);

protected:
    int sec;
};
std::ostream &operator<<(std::ostream &os, orario const &o);

orario::orario(int ore, int min, int secondi) { sec = ore * 3600 + min * 60 + secondi; };
int orario::Ore() const { return sec / 3600; };
int orario::Minuti() const { return (sec / 60) % 60; };
int orario::Secondi() const { return sec % 60; };
bool orario::operator==(orario o) const
{
    return sec == o.sec;
};
std::ostream &operator<<(std::ostream &os, orario::orario o)
{
    std::string ore, m, s;
    ore = o.Ore() < 10 ? '0' + o.Ore() : o.Ore();
    m = o.Minuti() < 10 ? '0' + o.Minuti() : o.Minuti();
    s = o.Secondi() < 10 ? '0' + o.Secondi() : o.Secondi();
    return os << ore << ":" << m << ":" << s << std::endl;
};

#endif
