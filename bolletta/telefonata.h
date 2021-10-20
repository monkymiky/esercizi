#ifndef TELEFONATA_H
#define TELEFONATA_H
#include "orario.h"
#include <iostream>
class telefonata
{
public:
    telefonata(const orario, const orario, const std::string);
    telefonata();
    orario GetInizio() const;
    orario GetFine() const;
    std::string GetNumero() const;
    bool operator==(const telefonata &) const;

private:
    orario inizio, fine;
    const std::string nr;
};
std::ostream &operator<<(std::ostream &, const telefonata::telefonata &);
#endif