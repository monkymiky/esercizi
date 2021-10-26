#ifndef VETTORE_H
#define VETTORE_H
#include <iostream>
class Vettore
{
    friend std::ostream &operator<<(std::ostream &, const Vettore &);

private:
    class nodo
    {
        friend class Vettore;

    private:
        int info;
        nodo *next;

    public:
        nodo(int i, nodo *n) : info(i), next(n){};
        ~nodo();
    };
    static nodo *copia(const nodo *n);
    nodo *inizio;

public:
    unsigned int size;
    class iteratore
    {
        friend class Vettore;

    private:
        nodo *punt;

    public:
        iteratore operator++();
        iteratore &operator++(int);
        bool operator==(iteratore);
        bool operator!=(iteratore);
        int operator*() const;
        int *operator->() const;
    };
    iteratore begin() const;
    iteratore end() const;
    iteratore last() const;
    int &operator[](iteratore) const;
    Vettore() : inizio(new nodo(0, nullptr)){};

    Vettore &append(int);
    bool operator==(const Vettore &);
    Vettore(const Vettore &);
    Vettore &operator=(Vettore);
    ~Vettore();
};
#endif
// Lezione PaO 19-10-2021 min 51