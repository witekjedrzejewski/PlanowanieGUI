#include <sstream>
#include <cassert>
#include <QDebug>

#include "Gracz.h"

using namespace std;

Gracz::Gracz(int nr) : nr(nr) { }

Gracz::~Gracz() { }

void Gracz::deklaruj() {
	int d = wybierzDeklaracje();
	
    qDebug() << "Gracz " << nr << ": deklaracja " << d;
	
    assert(d >= 0 && d <= liczbaKart);
					
	plansza->przyjmijDeklaracje(d, nr);

    emit zadeklarowal();
}

void Gracz::grajKarte() {
    qDebug() << "Gracz " << nr << ": grajKarte";
    assert(nr == plansza->ktoWyklada());
    if (liczbaKart == 1) {
        polozKarte(0);
    } else {
        connect(this, SIGNAL(kartaWybrana(int)), this, SLOT(polozKarte(int)));
        wybierzKarte();
    }
}

void Gracz::polozKarte(int nrKarty) {
    disconnect(this, SIGNAL(kartaWybrana(int)), this, SLOT(polozKarte(int)));

    assert(plansza->kartaONumerzePoprawna(nrKarty, nr));
	
    plansza->dolozKarteOdGracza(nrKarty);
    usunKarte(nrKarty);

    emit kartaPolozona();
}

void Gracz::setReka(std::vector<Karta> r) {
    // qDebug() << "Gracz.setReka";
    liczbaKart = r.size();
    plansza->dajKartyGraczowi(r, nr);
}

void Gracz::setPlansza(Plansza* p) {
	plansza = p;
}

void Gracz::usunKarte(int) {
    liczbaKart--;
}

/*
bool Gracz::KartyComparator::operator() (const Karta& a, const Karta& b) const {
	if (a.kolor() == b.kolor())
		return a.wysokosc() > b.wysokosc();
	return a.kolor() < b.kolor();
}*/
