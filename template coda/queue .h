#include <iostream>
template <class T>
class Queue; // dichiarazione incompleta necessaria per dichiarare operator << !!

// dichiarazione tamplate di funzione, richiesta prima per poter creare la relazione d'amicizia siccome è una funzione esterna !!
template <class T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &); // qua non ci va il <T> all inizio...

template <class T>
class Queue
{
    friend ostream &operator<<<T>(ostream &, const Queue<T> &); // NON AGISCE da dichiarazione di Template di funzione !!
public:
    Queue();
    bool is_empy() const;
    void add(const T &);
    T remove();
    // regola del 3 profondo
    ~Queue();
    Queue(const Queue &);
    Queue &operator=(const Queue &);

private:
    template <class T>
    class QueueItem
    {
        friend class Queue<T>;
        friend ostream &operator<<<T>(ostream &, const Queue<T> &);                        // per far si che la funzione esterna abbia accesso agli Item
        friend ostream &operator<<<T>(ostream &, const typename Queue<T>::QueueItem<T> &); // AGISCE da dichiarazione di Template di funzione !!
    public:
        QueueItem(const T &ogg) : info(ogg), next(nullptr){}; // bad practice --> inline sintassi definizione esterna??
        static QueueItem *copia(const QueueItem &qi)
        {
            if (qi.next == nullptr)
            {
                return new QueueItem(qi.info);
            }
            else
            {
                QueueItem *ret = new QueueItem(qi.info);
                ret->next = copia(qi.next);
                return ret;
            }
        };
        ~QueueItem()
        {
            while (next != nullptr)
                delete *next;
        };

    private:
        T info;
        QueueItem *next;
    };
    QueueItem<T> *primo, *ultimo;
};

template <class T>
Queue<T>::Queue() : primo(nullptr), ultimo(nullptr) {}
template <class T>
Queue<T>::~Queue()
{
    delete *primo;
}
template <class T>
Queue<T>::Queue(const Queue<T> &q)
{
    primo = copia(q.primo);
    QueueItem<T> *aux = primo;
    while (aux->next != nullptr)
        aux = aux->next;
    ultimo = aux;
}
template <class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &q)
{
    if (this != &q)
    {
        delete *primo;
        primo = copia(q->primo);
        QueueItem<T> *aux = primo;
        while (aux->next != nullptr)
            aux = aux->next;
        ultimo = aux;
        return *this
    }
    return *this;
}
template <class T>
bool Queue<T>::is_empy() const
{
    return primo == nullptr;
}
template <class T>
void Queue<T>::add(const T &ogg)
{
    QueueItem<T> *qi = new QueueItem(ogg);
    if (is_empy())
    {
        primo = ultimo = qi;
    }
    else
    {
        ultimo->next = qi;
        ultimo = qi;
    }
}
template <class T>
T Queue<T>::remove()
{
    if (is_empy())
    {
        std::cerr << "remove() su coda vuota" << std::endl;
        exit(1); // bad practice --> stop programma.
    }
    else
    {
        T ret = primo->info;
        QueueItem<T> *aux = primo;
        primo = primo->next;
        delete aux;
        return ret;
    }
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &q) // qua non ci va il <T> all inizio...
{
    os << "(";
    QueueItem<T> *p = q.primo; // errore ??
    for (; p != nullptr; p->next)
    {
        os << *p << " ";
        os << ")" << endl;
    }
    return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const typename Queue<T>::QueueItem<T> &qi) // NB: sintassi strana "typename Queue<T>::"
{                                                                                     // qua non ci va il <T> all inizio...
    return os << qi.info;
}