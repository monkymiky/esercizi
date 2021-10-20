#include "bolletta.h"
//================ metodi e classi private bolletta
class bolletta::C_privata
{
public:
    class nodo
    { // nascosto perchè è un modo usato per implementare
        // la struttura che deve restare nascosto all'utente

    public: // non ha la parte privata quindi tutte le funzioni
            //di bolletta hanno accesso a tutti i dati della classe nodo
        nodo();
        nodo(const telefonata &, nodo *);
        telefonata info;
        nodo *next;
        ~nodo(); // cosi però se voglio rimuovere un nodo in mezzo alla lista devo
                 // mettere next = nullptr perche altrimenti distruggo tutta la lista restante
        static nodo *copia(nodo *p)
        {
            if (!p)
                return nullptr;
            else
                return new nodo(p->info, copia(p->next));
        };
    };

    nodo *first;
    C_privata();
};
bolletta::C_privata::C_privata() : first(new nodo()) {}
//costruttore di default per il campo nodo
bolletta::C_privata::nodo::nodo() : next(0){};
bolletta::C_privata::nodo::nodo(const telefonata &t, nodo *s) : info(t), next(s) {}
bolletta::C_privata::nodo::~nodo()
{
    //if (next != nullptr) // non necessario perche delete nullptr non fa niente
    delete next;
};
bolletta::bolletta &bolletta::operator=(const bolletta &b)
{
    if (&b != this) // messo perche: bug nel caso in cui faccio b = b
                    // --> attenzione quando ho un array di bollette
    {
        delete punt->first;
        punt->first = punt->first->copia(b.punt->first); // ha senso?????????????????
    }
    return *this;
}
// ============= metodi pubblici bolletta =======================
bolletta::bolletta() : punt(new C_privata){};
bolletta::bolletta(const bolletta &b) : punt(new C_privata)
{
    punt->first = punt->first->copia(b.punt->first); // ha senso??????????????????
}
bolletta::~bolletta()
{
    //if (punt->first) non necessario perche "delete nullptr" non fa niente.
    delete punt->first;
}
bool bolletta::Vuota() const
{
    return punt->first == 0;
}
void bolletta::Aggiungi_Telefonata(const telefonata &t)
{
    punt->first = new C_privata::nodo(t, punt->first);
}
void bolletta::Togli_Telefonata(const telefonata &t)
// fa side-effect solo se la telefonata da togliere
//è il primo nodo della lista ---> non va messo il const!
{
    C_privata::nodo *p = punt->first;
    C_privata::nodo *prec = nullptr;
    while (p && !(p->info == t))
    {
        prec = p;
        p = p->next;
    }
    if (p)
    {
        if (!prec)
            punt->first = p->next;
        else
            prec->next = p->next;
        delete p; // è importantissimo deallocare manualmente la memoria sullo HEAP!
    }
}
telefonata bolletta::Estrai_Una()
{
    // precondizione bolletta non vuota!
    C_privata::nodo *p = punt->first;
    punt->first = punt->first->next;
    telefonata aux = p->info; // costruttore copia
    delete p;
    return aux;
}
std::ostream &operator<<(std::ostream &os, const bolletta &b)
{
    os << "telefonate nella bolletta:" << std::endl;
    bolletta::C_privata::nodo *p = b.punt->first;
    int i = 1;
    while (p)
    {
        os << i++ << ") " << p->info << std::endl;
        p = p->next;
    }
    return os;
}
