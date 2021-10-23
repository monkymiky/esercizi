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