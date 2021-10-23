#include "tree.h"
Nodo *Tree::copia(const Nodo *n)
{
    if (n)
    {
        return new Nodo(n->info, copia(n->sx), copia(n->dx));
    }
    return nullptr;
}
Nodo::~Nodo()
{
    if (this != nullptr)
    {
        delete this->dx;
        delete this->sx;
    }
}
Tree::Tree(const Tree &t)
{
    root = copia(t.root);
}
Tree::Tree &Tree::operator=(const Tree &t)
{
    if (this != &t)
    {
        delete root;
        root = copia(t.root);
    }
    return *this;
};
Tree::~Tree()
{
    delete root;
};
int main()
{
    Tree t1, t2;
    t1 = t2;
    Tree t3 = t2;
    return 0;
}