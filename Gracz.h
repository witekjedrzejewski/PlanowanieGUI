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
    void kartaWybrana();
    void kartaPolozona();

private slots:
    void polozKarte();

protected:

    struct KartyComparator {
        bool operator() (const Karta&, const Karta&) const;
    };

    typedef std::set<Karta, KartyComparator> ZestawKart;
    typedef ZestawKart::iterator ItKarta;

    virtual void wybierzKarte();
    virtual int wybierzDeklaracje() = 0;
    virtual void usunKarte(ItKarta iter);
    bool kartaPoprawna(ItKarta iter);
    virtual bool posiadaKartyWKolorze(int kol);

    ZestawKart reka;
    Plansza* plansza;
    int nr;
    ItKarta wybranaKarta;

};

#endif

