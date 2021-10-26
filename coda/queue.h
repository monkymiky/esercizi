#include <iostream>
template <class T>
class Queue;
template <class T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &);
template <class T>
class Queue
{
    friend std::ostream &operator<<<T>(std::ostream os, const Queue<T> &);

private:
    class QueueItem
    {
        friend class Queue<T>;
        friend std::ostream &operator<<<T>(std::ostream &os, const typename Queue<T>::QueueItem &);

    private:
        T info;
        QueueItem *next;
    };

    QueueItem *primo, *ultimo;

public:
    //...
};
template <class T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &q)
{
    //...
    return os;
}
template <class T>
std::ostream &operator<<(std::ostream &os, const typename Queue<T>::QueueItem &qi)
{
    //...
    return os;
}