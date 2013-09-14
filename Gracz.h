#ifndef gracz_H_
#define gracz_H_

#include <vector>
#include <set>

#include "Karta.h"
#include "Plansza.h"

class Gracz : public QObject {
	
    Q_OBJECT

public:
	Gracz(int nr);
	
	virtual ~Gracz();
	
    virtual void setReka(std::vector<Karta> reka);
	void setPlansza(Plansza* plansza);
	
	void deklaruj();
	void grajKarte();
	
	std::string wypiszReke();

signals:
    void zadeklarowal();
    void kartaWybrana(int nrKarty);
    void kartaPolozona();

protected slots:
    void polozKarte(int);

protected:

    /* w podklasie metoda musi emitowac kartaWybrana(nrKarty) */
    virtual void wybierzKarte() = 0;

    virtual int wybierzDeklaracje() = 0;
    virtual void usunKarte(int nrKarty);

    int liczbaKart;
    Plansza* plansza;
    int nr;

};

#endif

