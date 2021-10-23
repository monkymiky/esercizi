#ifndef TREE_H
#define TREE_H
class Nodo
{
    friend class Tree;

private:
    Nodo(char c = '*', Nodo *s = 0, Nodo *d = 0) : info(c), sx(s), dx(d) {}
    char info;
    Nodo *sx;
    Nodo *dx;
    ~Nodo();
};
class Tree
{
public:
    Tree() : root(0) {}
    Tree(const Tree &);
    Tree &operator=(const Tree &);
    ~Tree();

private:
    Nodo *root;
    static Nodo *copia(const Nodo *);
};
#endif