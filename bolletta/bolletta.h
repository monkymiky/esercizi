#ifndef BOLLETTA_H
#define BOLLETTA_H
#include "telefonata.h"
#include <iostream>
class bolletta
{
    friend std::ostream &operator<<(std::ostream &, const bolletta &);
    //friend class iteratore; non più necessario dopo C++03
private:
    // ======== inizio classe nodo ===============
    class nodo
    {
    public: // non ha la parte privata quindi tutte le funzioni
            //di bolletta hanno accesso a tutti i dati della classe nodo
        nodo() : next(0){};
        nodo(const telefonata &x, nodo *p) : info(x), next(p){};
        telefonata info;
        nodo *next;
        ~nodo(); // cosi però se voglio rimuovere un nodo in mezzo alla lista devo
                 // mettere next = nullptr perche altrimenti distruggo tutta la lista restante
        static nodo *copia(nodo *p)
            /* {
            if (!p)
                return nullptr;
            else
                return new nodo(p->info, copia(p->next));
        } */
            ;
    };
    // ================ fine classe nodo ===============
    nodo *first;

public:
    bolletta() : first(0){};
    bolletta(const bolletta &);
    ~bolletta();
    bool Vuota() const;
    void Aggiungi_Telefonata(const telefonata &);
    void Togli_Telefonata(const telefonata &);
    telefonata Estrai_Una();
    bolletta &operator=(const bolletta &);
    // ======== inizio classe iteratore ===============
    class iteratore
    {
        friend class bolletta;

    private:
        bolletta::nodo *punt;

    public:
        bool operator==(iteratore &) const;
        bool operator!=(iteratore &) const;
        iteratore &operator++();
        iteratore operator++(int);
        iteratore &operator[](unsigned int);
        iteratore &operator*(int);
        // iteratore& operator->();
    };
    // ======== fine classe iteratore ===============
};

#endif
