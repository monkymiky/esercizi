#include <iostream>
template <class T>
class albero;
template <class T>
std::ostream &operator<<(std::ostream &, const albero<T> &);

template <class T>
class albero
{
    friend std::ostream &operator<<<T>(std::ostream &, const albero<T> &);

private:
    class nodot
    {

    private:
        T info;
        nodot *xl, xc, xr;

    public:
        static nodot *copia(const nodot &);
        nodot(T i, nodot *l = nullptr, nodot *c = nullptr, nodot *r = nullptr);
        ~nodot();
    };
    nodot *root;

public:
    albero() : root(nullptr);
    albero(const albero &);
    bool operator=(const albero);
    ~albero();
    bool operator==(const albero &) const;
    bool operator!=(const albero &) const;
    void insert(const T &); // diventa la radice e come sottoalberi ha 3 copie dell albero precedente
    bool search(const T &);
    bool search_ric(const T &ogg, nodot *r);
    std::ostream &print_ric(std::ostream &, const nodot &);
};

// ========== nodot  =================

template <class T>
albero<T>::nodot *albero<T>::nodot::copia(const nodot &n)
{
    return new nodot(n.info,
                     if (n.xl) copia(n->xl) else nullptr,
                     if (n.xc) copia(n->xc) else nullptr,
                     if (n.xr) copia(n->xr) else nullptr);
};
template <class T>
albero<T>::nodot::nodot(T i, nodot *l, nodot *c, nodot *r) : info(i), xl(l), xc(c), xr(r){};
template <class T>
albero<T>::nodot::~nodot()
{
    if (xl)
        delete *xl;
    if (xc)
        delete *xc;
    if (xr)
        delete *xr;
}

// ========== public albero ==========

template <class T>
albero<T>::albero(const albero &a)
{
    if (a.root)
    {
        root = copia(a->root);
    }
    else
        root = nullptr;
};

template <class T>
bool albero<T>::operator=(const albero a)
{
    if (this != &a)
    {
        delete root;
        root = copia(a->root);
        return *this;
    }
    return *this;
};

template <class T>
albero<T>::~albero()
{
    delete *root;
};

template <class T>
bool albero<T>::operator==(const albero &a) const
{
    return root == a.root;
};

template <class T>
bool albero<T>::operator!=(const albero &a) const
{
    return root != a.root;
};

template <class T> // diventa la radice e come sottoalberi ha 3 copie dell albero precedente
void albero<T>::insert(const T &i)
{
    if (root)
    {
        albero<T>::nodot *aux = root;
        root = new nodot(i, aux, copia(aux), copia(aux));
    }
    else
    {
        root = new nodot(i);
    }
};
template <class T>
bool albero<T>::search_ric(const T &ogg, nodot *r)
{
    if (r == nullptr)
        return false;
    return r.info == ogg || search_ric(ogg, r->xl) || search_ric(ogg, r->xc) || search_ric(ogg, r->xr);
}

template <class T>
bool albero<T>::search(const T &ogg){return search_ric(ogg, root)};

//=========== oprator << ==========

template <class T>
std::ostream &albero<T>::print_ric(std::ostream &os, const nodot &n)
{
    os << n.info;
    os = print_ric(os, n->xl);
    os = print_ric(os, n->xc);
    return os = print_ric(os, n->xr);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const albero<T> &a)
{
    return albero<T>::print_ric(os, a->root);
}
int main()
{
    albero<char> t1, t2, t3;
    t1.insert('b');
    t1.insert('a');
    t2.insert('a');
    t3 = t1;
    t3.insert('c');
    std::cout << (t1 == t2) << std::endl;
    std::cout << t1.search('b') << std::endl;
    std::cout << t1 << std::endl
              << t2 << std::endl
              << t3 << std::endl;
}