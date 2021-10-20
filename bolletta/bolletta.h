#ifndef BOLLETTA_H
#define BOLLETTA_H
#include "telefonata.h"
#include <iostream>
class bolletta
{
    friend std::ostream &operator<<(std::ostream &, const bolletta &);

public:
    bolletta();
    bolletta(const bolletta &);
    ~bolletta();
    bool Vuota() const;
    void Aggiungi_Telefonata(const telefonata &);
    void Togli_Telefonata(const telefonata &);
    telefonata Estrai_Una();
    bolletta &operator=(const bolletta &);

private:
    class C_privata;
    C_privata *punt;
};

#endif
