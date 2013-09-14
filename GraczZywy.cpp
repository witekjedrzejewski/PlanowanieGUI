#include <QDebug>
#include <QVector>
#include <iostream>
#include <algorithm>

#include "GraczZywy.h"
#include "DialogDeklaracja.h"

using namespace std;

GraczZywy::GraczZywy(int nr) : Gracz(nr) { }

int GraczZywy::wybierzDeklaracje() {

    DialogDeklaracja* dialog = new DialogDeklaracja(reka.size());
    dialog->exec();

    int d = dialog->deklaracja();
	return d;
}

Gracz::ItKarta GraczZywy::wczytajKarte() {

	string opis;
	
	cin >> opis;
	Karta k(opis);
	return reka.find(k);
}

void GraczZywy::wyroznijDozwoloneKarty() {
    QVector <bool> poprawne;
    for (ItKarta it = reka.begin(); it != reka.end(); ++it) {
        poprawne.push_back(kartaPoprawna(it));
    }
    plansza->wyroznijKarty(nr, poprawne);
}

void GraczZywy::wybierzKarte() {
    //qDebug() << "Gracz " << nr << " wybierz karte";
    wyroznijDozwoloneKarty();

    wybranaKarta = reka.begin();
    Gracz::wybierzKarte();
}
