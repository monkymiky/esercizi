#include <iostream>
template <class T>
class dList
{
private:
    class nodo
    {
    public:
        nodo *prima, *dopo;
        T info;
        // consvertitore T => nodo(T,nullptr,nullptr)
        nodo(T i, nodo *p = nullptr, nodo *d = nullptr) : info(i), prima(p), dopo(d){};
        nodo();
        ~nodo();
    };
    nodo *primo;
    nodo *ultimo;
    nodo *copia(nodo *);
    static bool smallerThan(nodo *a, nodo *b)
    {
        if (b == nullptr)
            return false;
        if (a == nullptr)
            return true;
        return (a->info < b->info) || ((a->info == b->info) &&
                                       smallerThan(a->dopo, b->dopo));
    }

public:
    dList(unsigned int k, const T &t); // costruisce una lista contenente k nodi con valore t
    dList() : primo(0), ultimo(0){};
    dList(const dList &);
    ~dList();
    dList &operator=(const dList &);
    void insertFront(const T &);   // O(1)
    void insertback(const T &);    // O(1)
    bool operator<(const dList &); // ordinamento lessicografico
    class const_iterator
    {
        friend class dList;

    private:
        nodo *punt;
        bool pastend;
        const_iterator(nodo *p, bool b = false) : punt(p), pastend(b){};

    public:
        const_iterator() : punt(nullptr), pastend(false){};
        bool operator==(const const_iterator &) const;
        bool operator!=(const const_iterator &) const;
        const_iterator &operator++();
        const_iterator operator++(int);
        const_iterator &operator--();
        const_iterator operator--(int);
        const T &operator*() const;
        const T *operator->() const;
    };
    const_iterator begin() const;
    const_iterator end() const;
    const T &operator[](const_iterator) const;
};
// =========== nodo ============
template <class T>
dList<T>::nodo::~nodo()
{
    if (dopo)
    {
        delete dopo;
    }
}
template <class T>
typename dList<T>::nodo *dList<T>::copia(nodo *n) // assumo che sia il primo nodo della lista
{
    if (!n)
        return ultimo = nullptr; // setta ultimo = 0 e ritorna 0
    nodo *iter = n;
    nodo *first = new nodo(iter->info);
    nodo *current = first;
    while (iter != nullptr)
    {
        current->dopo = new nodo(iter->dopo->info, current);
        current = current->dopo;
        iter = n->dopo;
    }
    ultimo = current;
    return first;
}
// =========== pubblic dList ================
template <class T>
dList<T>::dList(unsigned int k, const T &t) : ultimo(nullptr), primo(nullptr)
{ // costruisce una lista contenente k nodi con valore t
    while (k > 0)
    {
        insertFront(t); //T => nodo(T,nullptr,nullptr)
    }
}
template <class T>
dList<T>::dList(const dList &d) : ultimo(nullptr), primo(copia(d->primo)){};
template <class T>
dList<T>::~dList()
{
    if (primo)
        delete primo;
}
template <class T>
dList<T> &dList<T>::operator=(const dList &d)
{
    if (this != &d)
    {
        delete primo;
        primo = copia(d.primo);
    }
    return *this;
}
template <class T>
void dList<T>::insertFront(const T &n)
{ // O(1)
    primo = new nodo(n, nullptr, primo);
    if (ultimo == nullptr)
        ultimo = primo;
    else
        primo->dopo->prima = primo;
}
template <class T> // O(1)
void dList<T>::insertback(const T &n)
{
    ultimo = new nodo(n, ultimo, nullptr);
    if (primo == nullptr)
        primo = ultimo;
    else
        ultimo->prima->dopo = ultimo;
}
template <class T>
bool dList<T>::operator<(const dList &l)
{ // ordinamento lessicografico
    return smallerThan(primo, l.primo);
}
// =========== iteratore dList ==============
// ==== interne ========
template <class T>
bool dList<T>::const_iterator::operator==(const const_iterator &ci) const { return punt == ci.punt; }
template <class T>
bool dList<T>::const_iterator::operator!=(const const_iterator &ci) const { return punt != ci.punt; }
template <class T>
typename dList<T>::const_iterator &dList<T>::const_iterator::operator++()
{
    if (punt && !pastend)
    {
        if (punt->dopo)
            punt = punt->dopo;
        else
        {
            ++punt;
            pastend = true;
        }
    }
    return *this;
}
template <class T>
typename dList<T>::const_iterator dList<T>::const_iterator::operator++(int)
{
    const_iterator aux = *this;
    if (punt && !pastend)
    {
        if (punt->dopo)
            punt = punt->dopo;
        else
        {
            ++punt;
            pastend = true;
        }
    }
    return aux;
}
template <class T>
typename dList<T>::const_iterator &dList<T>::const_iterator::operator--()
{
    if (punt)
    {
        if (pastend)
        {
            --punt;
            pastend = false;
        }
        else
        {
            punt = punt->prima;
        }
    }
    return *this;
}
template <class T>
typename dList<T>::const_iterator dList<T>::const_iterator::operator--(int)
{
    const_iterator aux = *this;
    if (punt)
    {
        if (pastend)
        {
            --punt;
            pastend = false;
        }
        else
        {
            punt = punt->prima;
        }
    }
    return aux;
}
template <class T>
const T &dList<T>::const_iterator::operator*() const { return punt->info; }
template <class T>
const T *dList<T>::const_iterator::operator->() const { return &punt->info; }

// ===== esterne =======
template <class T>
typename dList<T>::const_iterator dList<T>::begin() const { return primo; }
template <class T>
typename dList<T>::const_iterator dList<T>::end() const
{
    if (primo == nullptr)
        return const_iterator(nullptr, false);
    else
        return const_iterator(ultimo + 1, true);
}
template <class T>
const T &dList<T>::operator[](const_iterator ci) const
{
    return ci.punt->info;
}
