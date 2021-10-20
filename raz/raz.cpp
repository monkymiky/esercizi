#include "raz.h"
Raz::Raz(int n, int d) : num(n), den(d == 0 ? 1 : d){};
Raz Raz::inverso() const { return Raz(num == 0 ? 0 : den, num); };
double Raz::operator double() const { return static_cast<double>(num) / static_cast<double>(den); };
Raz Raz::operator+(const Raz &r1, const Raz &r2) const
{
    return Raz(r1.num * r2.den + r2.num * r1.den, r1.den * r2.den);
};
Raz &operator++()
{
    num += den;
    return *this;
}
Raz operator++(int)
{
    Raz aux = *this;
    num += den;
    return aux;
}
std::ostream &operator<<(std::ostream &os, const Raz::Raz &r)
{
    return os << r.operator double(); // per invocare esplicitamente
    //la funzione di conversone che si chiama proprio"operator double"
}
