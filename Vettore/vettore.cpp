#include "Vettore.h"
// ======= class nodo =====
Vettore::nodo *Vettore::copia(const nodo *n)
{
    return new nodo(n->info, copia(n->next));
};
Vettore::nodo::~nodo()
{
    delete this->next;
};
// ========== class iteratore ==============
Vettore::iteratore::iteratore Vettore::iteratore::operator++()
{
    iteratore aux = *this;
    if (punt)
    {
        aux.punt = aux.punt->next;
    }
    return aux;
};
Vettore::iteratore::iteratore &Vettore::iteratore::operator++(int)
{
    punt = punt->next;
    return *this;
};
bool Vettore::iteratore::operator==(iteratore i)
{
    return punt == i.punt;
};
bool Vettore::iteratore::operator!=(iteratore i)
{
    return punt != i.punt;
};
int Vettore::iteratore::operator*() const
{
    return punt->info;
};
int *Vettore::iteratore::operator->() const
{
    return &punt->info;
};
// ========== class vettore ===================
Vettore::iteratore::iteratore Vettore::begin() const
{
    iteratore i;
    i.punt = inizio;
    return i;
};
Vettore::iteratore::iteratore Vettore::end() const
{
    iteratore i;
    i.punt = nullptr;
    return i;
};
int &Vettore::operator[](iteratore i) const
{
    return i.punt->info;
};

Vettore::Vettore &Vettore::append(int nr)
{
    ++size;
    nodo *n = new nodo(nr, begin().punt);
    inizio = n;
    return *this;
};
bool Vettore::operator==(const Vettore &v)
{
    if (size != v.size)
        return false;
    for (Vettore::iteratore i = begin(); i != end(); i++)
    {
        if (i.punt->info != v[i])
            return false;
    }
    return true;
};
Vettore::Vettore(const Vettore &v)
{
    inizio = copia(v.inizio);
    size = v.size;
};
Vettore::Vettore &Vettore::operator=(Vettore v)
{
    if (this != &v)
    {
        delete this->inizio;
        inizio = copia(v.inizio);
        size = v.size;
    }
    return *this;
};
Vettore::~Vettore()
{
    delete inizio;
};
std::ostream &operator<<(std::ostream &os, const Vettore &v)
{
    for (Vettore::iteratore i = v.begin(); i != v.end(); i++)
    {
        os << " [" << v[i] << "] ";
    }
    return os << std::endl;
};