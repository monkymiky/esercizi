#include "bolletta.h"
//================ metodi e classi private bolletta

bolletta::bolletta() : first(new nodo()) {}
//costruttore di default per il campo nodo
bolletta::nodo::nodo() : next(0){};
bolletta::nodo::nodo(const telefonata &t, nodo *s) : info(t), next(s) {}
bolletta::nodo::~nodo()
{
    //if (next != nullptr) // non necessario perche delete nullptr non fa niente
    delete next;
};
bolletta::bolletta &bolletta::operator=(const bolletta &b)
{
    if (&b != this) // messo perche: bug nel caso in cui faccio b = b
                    // --> attenzione quando ho un array di bollette
    {
        delete first;
        first = first->copia(b.first); // ha senso?????????????????
    }
    return *this;
}
// ============= metodi pubblici bolletta =======================
bolletta::bolletta() : first(0){};
bolletta::bolletta(const bolletta &b)
{
    first = first->copia(b.first); // ha senso??????????????????
}
bolletta::~bolletta()
{
    //if (first) non necessario perche "delete nullptr" non fa niente.
    delete first;
}
bool bolletta::Vuota() const
{
    return first == 0;
}
void bolletta::Aggiungi_Telefonata(const telefonata &t)
{
    first = new nodo(t, first);
}
void bolletta::Togli_Telefonata(const telefonata &t)
// fa side-effect solo se la telefonata da togliere
//è il primo nodo della lista ---> non va messo il const!
{
    nodo *p = first;
    nodo *prec = nullptr;
    while (p && !(p->info == t))
    {
        prec = p;
        p = p->next;
    }
    if (p)
    {
        if (!prec)
            first = p->next;
        else
            prec->next = p->next;
        delete p; // è importantissimo deallocare manualmente la memoria sullo HEAP!
    }
}
telefonata bolletta::Estrai_Una()
{
    // precondizione bolletta non vuota!
    nodo *p = first;
    first = first->next;
    telefonata aux = p->info; // costruttore copia
    delete p;
    return aux;
}
std::ostream &operator<<(std::ostream &os, const bolletta &b)
{
    os << "telefonate nella bolletta:" << std::endl;
    bolletta::nodo *p = b.first;
    int i = 1;
    while (p)
    {
        os << i++ << ") " << p->info << std::endl;
        p = p->next;
    }
    return os;
}
