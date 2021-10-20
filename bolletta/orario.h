//orario.h
#ifndef ORARIO_H
#define ORARIO_H
#include <iostream>
#include <string>

class orario
{
public:
    orario(int, int, int = 0);
    orario(int);
    orario();
    int Ore() const;
    int Minuti() const;
    int Secondi() const;
    orario static OraDiPranzo();
    orario UnOraPiuTardi() const;
    void AvanzaUnOra();
    bool operator==(orario) const;
    void operator=(orario);
    orario(const orario &);

private:
    class orario_rapp;
    orario_rapp *punt;
};
std::ostream &operator<<(std::ostream &os, orario const &o);
orario::orario operator+(orario const &o1, orario const &o2);

#endif
