class Nodo
{
private:
    Nodo(char c = '*', Nodo *s = 0, Nodo *d = 0) : info(c), sx(s), dx(d) {}
    char info;
    Nodo *sx;
    Nodo *dx;
};
class Tree
{
public:
    Tree() : root(0) {}
    Tree(const Tree &);
    void operator=(const Tree &);
    ~Tree();

private:
    Nodo *root;
};