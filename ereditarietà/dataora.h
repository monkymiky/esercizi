#ifndef DATAORA_H
#define DATAORA_H
#include "orario.h"
enum settimana
{
    lun,
    mar,
    mer,
    gio,
    ven,
    sab,
    dom
};

class dataora : public orario
{
public:
    settimana GiornoSettimama() const { return giornosettiamana; };
    void AvanzaUnGiorno()
    {
        if (giorno < GiorniDelMese())
            giorno++;
        else if (mese < 12)
        {
            giorno = 1;
            mese++;
        }
        else
        {
            giorno = 1;
            mese = 1;
            anno++;
        }
    }
    dataora operator+(const orario &o) const
    { // ridefinizione di un metodo con segnatura diversa
        dataora aux = *this;
        aux.sec = sec + 3600 * o.Ore() + 60 * o.Minuti() + o.Secondi();
        //protected quindi posso accedere a sec ma non a o.sec
        if (aux.sec >= 86400)
        {
            aux.sec = aux.sec - 86400;
            aux.AvanzaUnGiorno();
        }
        return aux;
    }

    int Giorno();
    int Mese();
    int Anno();

private:
    int giorno, mese, anno;
    settimana giornosettiamana;
};

#endif