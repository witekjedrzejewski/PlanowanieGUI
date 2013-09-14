#include <QDebug>
#include <QVector>
#include <iostream>
#include <algorithm>

#include "GraczZywy.h"
#include "DialogDeklaracja.h"

using namespace std;

GraczZywy::GraczZywy(int nr) : Gracz(nr) { }

int GraczZywy::wybierzDeklaracje() {

    DialogDeklaracja* dialog = new DialogDeklaracja(liczbaKart);
    dialog->exec();

    int d = dialog->deklaracja();
	return d;
}

void GraczZywy::wybierzKarte() {
    //qDebug() << "Gracz " << nr << " wybierz karte";
    plansza->wyroznijDozwoloneKarty();
    connect(plansza, SIGNAL(kartaKliknieta(int)), this, SLOT(kartaKliknieta(int)));
}

void GraczZywy::kartaKliknieta(int nrKarty) {
    disconnect(plansza, SIGNAL(kartaKliknieta(int)), this, SLOT(kartaKliknieta(int)));
    plansza->wylaczWyroznienie();
    emit(kartaWybrana(nrKarty));
}
