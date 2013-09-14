#include <QDebug>

#include "Gra.h"
#include "Talia.h"
#include "GraczZywy.h"
#include "GraczBot.h"

using namespace std;

Gra::Gra(const vector<bool>& g, const vector<int>& k, QObject *parent)
    : QObject(parent), zywiGracze(g), liczbyKart(k) {

    liczbaGraczy = zywiGracze.size();
    aktualnyIndeksLiczbyKart = 0;
    ktoWistuje = 0;

    plansza = new Plansza(liczbaGraczy);


    qDebug() << "Gracze:";

    for (int i = 0; i < liczbaGraczy; i++) {
        qDebug() << i << ": ";
        if (zywiGracze[i]) {
            qDebug() << "zywy";
            gracze.push_back(new GraczZywy(i));
        } else {
            qDebug() << "bot";
            gracze.push_back(new GraczBot(i));
        }
        gracze.back()->setPlansza(plansza);
        connect(gracze.back(), SIGNAL(kartaPolozona()), this, SLOT(grajKarte()));

    }
}

Plansza* Gra::getPlansza() const {
    return plansza;
}

int Gra::liczbaKart() {
    return liczbyKart[aktualnyIndeksLiczbyKart];
}

void Gra::uruchom() {
    qDebug() << "ROZPOCZYNAM GRE";

    grajRozdanie();
}

void Gra::grajRozdanie() {

    qDebug() << "Rozdanie (" << liczbaKart()
             << " kart, wist = " << ktoWistuje << ")";
	
    plansza->setLiczbaKart(liczbaKart());
    plansza->setKtoWistuje(ktoWistuje);
    rozdajKarty();
    poprosODeklaracje();

}

void Gra::rozdajKarty()
{
    qDebug() << "Gra.rozdajKarty";

    Talia talia;
    for (int i = 0; i < liczbaGraczy; ++i) {
        gracze[i]->setReka(talia.getKarty(liczbaKart()));
    }
}

void Gra::poprosODeklaracje()
{
    qDebug() << "Gra.poprosODeklaracje()";
    przyjeteDeklaracje = 0;
    for (int i = 0; i < liczbaGraczy; i++) {
        connect(gracze[i], SIGNAL(zadeklarowal()),
                this, SLOT(graczZadeklarowal()));
        gracze[i]->deklaruj();
    }
}

void Gra::graczZadeklarowal() {
    przyjeteDeklaracje++;
    if (przyjeteDeklaracje == liczbaGraczy) {
        qDebug() << "Gra: mam wszystkie deklaracje";
        for (int i = 0; i < liczbaGraczy; i++) {
            disconnect(gracze[i], SIGNAL(zadeklarowal()),
                        this, SLOT(graczZadeklarowal()));
        }
        plansza->ujawnijDeklaracje();
        grajKarte();
    }
}

void Gra::grajKarte()
{
    // qDebug() << "Gra.grajKarte()";
	
    if (plansza->koniecRozdania()) {
        zakonczRozdanie();
    } else {
        int ktoWyklada = plansza->ktoWyklada();
        // qDebug() << ktoWyklada;

        gracze[ktoWyklada]->grajKarte();
    }
}

void Gra::zakonczRozdanie() {
    aktualnyIndeksLiczbyKart++;
    if (aktualnyIndeksLiczbyKart >= (int)liczbyKart.size()) { // to bylo ostatnie rozdanie
        zakonczGre();
    } else {
        ktoWistuje = plansza->kolejnyGracz(ktoWistuje);
        grajRozdanie();
    }
}

void Gra::zakonczGre() {
    qDebug() << "KONIEC GRY!";
}








