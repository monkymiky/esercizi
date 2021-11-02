#include <iostream>
template <class T>
class dlist
{
private:
    class nodo
    {
        friend class dlist;

    private:
        nodo *prima, dopo;
        T info;

    public:
        nodo(T i, nodo *p = nullptr, nodo *d = nullptr) : info(i), prima(p), dopo(d){};
        ~nodo();
        static nodo *copia(const nodo &);
    };
    nodo *primo, ultimo;

public:
    dlist(int k, const T &t); // costruisce una lista contenente k nodi con valore t
    dlist() : primo(0), ultimo(0){};
    dlist(const dlist &);
    ~dlist();
    dlist &operator=(const dlist &);
    void insertFront(const T &);   // O(1)
    void insertback(const T &);    // O(1)
    bool operator<(const dlist &); // ordinamento lessicografico
    class const_iterator
    {
        friend class dlist;

    private:
        nodo *punt;

    public:
        bool operator==(const const_iterator &) const;
        bool operator!=(const const_iterator &) const;
        const_iterator &operator++();
        const_iterator operator++(int);
        const_iterator &operator--();
        const_iterator operator--(int);
        const T &operator*() const;
        const T *operator->() const;
    };
    const_iterator &begin() const;
    const_iterator &end() const;
    const T &operator[](const_iterator) const;
};
// =========== nodo ============
template <class T>
dlist<T>::nodo::~nodo()
{
    if (dopo)
    {
        delete *dopo;
    }
}
template <class T>
dlist<T>::nodo *dlist<T>::nodo::copia(const nodo &n) // assumo che sia il primo nodo della lista
{
    if (n)
    {
        nodo *iter = n;
        nodo *aux = new nodo(iter.info);
        nodo *ret = aux;
        while (iter != nullptr)
        {
            aux->dopo = new nodo(iter.dopo->info, aux);
            aux = aux.dopo;
            iter = n.dopo;
        }
        return ret;
    }
    return nullptr;
}
// =========== pubblic dlist ================
template <class T>
dlist<T>::dlist(int k, const T &t) // costruisce una lista contenente k nodi con valore t
{
    if (k)
    {
        primo = new nodo(t);
        nodo *aux = primo;
        while (k != 0)
        {
            aux->dopo = new nodo(t, aux);
            aux = aux.dopo;
            --k;
        }
        ultimo = aux;
    }
    else
    {
        primo = ultimo = nullptr;
    }
}
template <class T>
dlist<T>::dlist(const dlist &d)
{
    ultimo = primo = copia(d->primo);
    while (ultimo->dopo != nullptr)
    {
        ultimo = ultimo->dopo;
    }
}
template <class T>
dlist<T>::~dlist()
{
    delete primo;
}
template <class T>
dlist<T> &dlist<T>::operator=(const dlist &d)
{
    if (this != &d)
    {
        primo = ultimo = copia(d->primo);
        while (ultimo->dopo != nullptr)
        {
            ultimo = ultimo->dopo;
        }
    }
    else
        return *this;
}
template <class T>
void dlist<T>::insertFront(const T &n)
{ // O(1)
    nodo *n1 = new nodo(n, nullptr, primo);
    primo = n1;
}
template <class T> // O(1)
void dlist<T>::insertback(const T &n)
{
    nodo *nlast = new nodo(n, ultimo, nullptr);
    ultimo = nlast;
}
template <class T>
bool dlist<T>::operator<(const dlist &l)
{ // ordinamento lessicografico
    nodo *aux = primo, aux2 = l.primo;
    while (aux->info == aux2->info && aux->dopo != nullptr && aux2->dopo != nullptr)
    {
        aux = aux->dopo;
        aux2 = aux2->dopo;
    }
    if (aux->dopo == nullptr)
    {
        if (aux2->dopo == nullptr)
            return aux->info < aux2->info;
        if (aux->info < aux2->info)
            return true;
        else
            return false;
    }
    if (aux2->dopo == nullptr)
    {
        if (aux->info < aux2->info)
            return true;
        else
            return false;
    }
    return aux->info < aux2->info;
}
// =========== iteratore dlist ==============
// ==== interne ========
template <class T>
bool dlist<T>::const_iterator::operator==(const const_iterator &ci) const { return punt == ci.punt; }
template <class T>
bool dlist<T>::const_iterator::operator!=(const const_iterator &) const { return punt != ci.punt; }
template <class T>
dlist<T>::const_iterator &dlist<T>::const_iterator::operator++()
{
    if (punt)
    {
        punt = punt->dopo;
        return *this;
    }
    else
        return *this;
}
template <class T>
dlist<T>::const_iterator dlist<T>::const_iterator::operator++(int)
{
    const_iterator aux = *this;
    if (punt)
    {
        punt = punt->dopo;
        return aux;
    }
    else
        return aux;
}
template <class T>
dlist<T>::const_iterator &dlist<T>::const_iterator::operator--()
{
}
template <class T>
dlist<T>::const_iterator dlist<T>::const_iterator::operator--(int) {}
template <class T>
const T &dlist<T>::const_iterator::operator*() const {}
template <class T>
const T *dlist<T>::const_iterator::operator->() const {};

// ===== esterne =======
template <class T>
dlist<T>::const_iterator &dlist<T>::begin() const
{
    const_iterator aux;
    aux.punt = primo;
    return aux;
}
template <class T>
dlist<T>::const_iterator &dlist<T>::end() const
{
    const_iterator aux;
    aux.punt = nullptr;
    return aux;
}
template <class T>
const T &dlist<T>::operator[](const_iterator ci) const
{
    return ci.punt->info;
}
