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
        static nodo *copia(nodo *p);
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
        //costruttore di default, non serve ridefinirlo
        bool operator==(iteratore) const;
        bool operator!=(iteratore) const;
        iteratore &operator++();
        iteratore operator++(int);
        telefonata &operator*() const;  //operatore unario
        telefonata *operator->() const; //operatore unario // il tipo di ritorno deve supportare l operatore "->" (in questo caso è un puntatore --> ok)
    };
    // ======== fine classe iteratore ===============
    //classi del contenitore che permettono di usare l iteratore
    iteratore begin() const;
    iteratore end() const;
    telefonata &operator[](iteratore) const; // non usuale per un contenitore implementato
                                             // con una lista per l accesso non in tempo costante che ci si aspetterebbe
    // metodi di bolletta che fanno uso di iteratori
    orario Somma_Durate(const bolletta &b) const; // max 24 ore!
};

#endif
