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
};

#endif
