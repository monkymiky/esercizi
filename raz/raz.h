#ifndef RAZ_H
#define RAZ_H
#include <iostream>

class Raz
{
private:
    int num, den; // invariante : den != 0
public:
    //conversione int x => Raz(x,1) bloccata
    explicit Raz(int = 0, int = 1); // se d == 0 viene sostituito con 1
    Raz inverso() const;
    operator double() const;
    Raz operator+(const Raz &) const;
    bool operator==(const Raz &) const;
    Raz &operator++();
    Raz operator++(int);
    static Raz unTerzo()
    {
        return Raz(1, 3);
    }
};
std::ostream &operator<<(std::ostream &, const Raz::Raz &);

#endif