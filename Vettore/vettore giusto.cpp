#include <iostream>
class Vettore
{
private:
    int *a;
    unsigned int size; // size ≧ 0 (garantito da unsigned int)
                       // vettore vuoto IFF a==nullptr && size == 0
                       // vettore non vuoto IFF a!=nullptr && size>0
public:
    // unsigned int => Vettore
    Vettore(unsigned int s = 0, int init = 0) : a(s == 0 ? nullptr : new int[s]), size(s)
    {
        for (int j = 0; j < size; ++j)
            a[j] = init;
    }
    Vettore(const Vettore &v) : a(v.size == 0 ? nullptr : new int[v.size]), size(v.size)
    {
        for (unsigned int j = 0; j < size; ++j)
            a[j] = v.a[j];
    }
    Vettore &operator=(const Vettore &v)
    {
        if (this != &v)
        {
            delete[] a; // attenzione: delete[] e NON delete
            size = v.size;
            a = size == 0 ? nullptr : new int[size];
            for (int i = 0; i < size; i++)
                a[i] = v.a[i];
        }
        return *this;
    }
    ~Vettore()
    {
        if (a)
            delete[] a;
    }
    Vettore &append(const Vettore &v)
    {
        if (v.size != 0)
        {
            int *aux = new int[size + v.size];
            for (int i = 0; i < size; i++)
                aux[i] = a[i];
            for (int i = 0; i < v.size; i++)
                aux[size + i] = v.a[i];
            size += v.size;
            delete[] a; // FONDAMENTALE
            a = aux;
        }
        return *this;
    }
    Vettore operator+(const Vettore &v) const
    {
        Vettore aux(*this);
        aux.append(v);
        return aux;
    }
    bool operator==(const Vettore &v) const
    {
        if (this == &v)
            return true;
        if (size != v.size)
            return false;
        // size == v.size >= 0
        for (int i = 0; i < size; i++)
            if (a[i] != v.a[i])
                return false;
        // forall i in [0,size-1], a[i]==v.a[i]
        return true;
    }
    int &operator[](unsigned int i) const
    {
        return *(a + i);
    }
    unsigned int getSize() const
    {
        return size;
    } //FINE CLASSE
};
std::ostream &operator<<(std::ostream &os, const Vettore &v)
{
    os << '[';
    int i = 0;
    while (i < (v.getSize()))
    {
        os << v[i] << ((i != v.getSize() - 1) ? ',' : ']');
        i++;
    }
    if (v.getSize() == 0)
        os << ']';
    return os;
}
int main()
{
    Vettore v1(4), v2(3, 2), v3(5, -3);
    v1 = v2 + v3;
    v2.append(v2);
    v3.append(v1).append(v3);
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
}