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
	
	assert(d >= 0 && d <= (int)reka.size());
					
	plansza->przyjmijDeklaracje(d, nr);

    emit zadeklarowal();
}

void Gracz::grajKarte() {
    // qDebug() << "Gracz " << nr << ": grajKarte";
	
    if (reka.size() == 1) {
        wybranaKarta = reka.begin();
        polozKarte();
    } else {
        connect(this, SIGNAL(kartaWybrana()), this, SLOT(polozKarte()));
        wybierzKarte();
    }
}

void Gracz::wybierzKarte() {
    emit kartaWybrana();
}

void Gracz::polozKarte() {
    disconnect(this, SIGNAL(kartaWybrana()), this, SLOT(polozKarte()));

    assert(kartaPoprawna(wybranaKarta));
	
    plansza->dolozKarteOdGracza(*wybranaKarta, nr);
    usunKarte(wybranaKarta);

    emit kartaPolozona();
}

void Gracz::setReka(std::vector<Karta> r) {
	reka = ZestawKart(r.begin(), r.end());
    for (ItKarta it = reka.begin(); it != reka.end(); it++) {
        plansza->dajKarteGraczowi(*it, nr);
    }
}

void Gracz::setPlansza(Plansza* p) {
	plansza = p;
}

string Gracz::wypiszReke() {
	ostringstream oss;
	for (ItKarta it = reka.begin(); it != reka.end(); it++) {
		oss << *it << " ";
	}
	return oss.str();
}

void Gracz::usunKarte(ItKarta iter) {
	reka.erase(iter);
}

bool Gracz::kartaPoprawna (ItKarta iter)
{
	if (iter == reka.end()) {
		cerr << "nie znaleziona" << endl;
		return false;
	}
	
	int wychodzi = plansza->ktoWychodzi();
	if (nr == wychodzi)
		return true; // my wykladamy, wiec dowolna karta
	
	Karta k = *iter;
	int kolWyjscia = plansza->kolorWyjscia();
	if (k.kolor() == kolWyjscia)
		return true; // dolozone do koloru
	
	return !posiadaKartyWKolorze(kolWyjscia);
}

bool Gracz::posiadaKartyWKolorze(int kol) {
	for (ItKarta it = reka.begin(); it != reka.end(); it++) {
		if (it->kolor() == kol)
			return true;
	}
	return false;
}

bool Gracz::KartyComparator::operator() (const Karta& a, const Karta& b) const {
	if (a.kolor() == b.kolor())
		return a.wysokosc() > b.wysokosc();
	return a.kolor() < b.kolor();
}
