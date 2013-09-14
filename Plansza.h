#ifndef PLANSZA_H_
#define PLANSZA_H_

#include <QObject>
#include <QGraphicsScene>
#include <QVector>
#include <QList>

#include <algorithm>

#include "Karta.h"
#include "KartaSprite.h"

class Plansza : public QGraphicsScene {
	
    Q_OBJECT

public:	
    Plansza(int liczbaGraczy, QObject* parent = 0);
	
	/* karty aktualnie lezace na stole */
    QVector<Karta> stol() const;
	
	/* deklaracje poszczegolnych graczy */
    QVector<int> deklaracje() const;
	
	/* wyniki punktowe */
    QVector<int> wyniki() const;
	
	/* ile ugrali w tym rozdaniu poszczegolnie gracze */
    QVector<int> wziete() const;
	
	/* kto wyszedl, dolozone karty */
    std::pair<int, QVector<Karta> > ostatniaLewa() const;
	
	/* nr gracza ktory powinien wylozyc pierwszy w aktualnej lewie */
	int ktoWychodzi() const;
	
	/* nr gracza ktory powinien teraz wylozyc karte */
	int ktoWyklada() const;
	
	int liczbaGraczy() const;
	
	/* kolor w ktorym jest wylozona karta */
	int kolorWyjscia() const;
	
    /* przyjmuje karte o danym nr od gracza ktory powinien dac karte */
    void dolozKarteOdGracza(int nrKarty);
	
	/* przyjmuje deklaracje d lew od gracza nr */
	void przyjmijDeklaracje(int d, int nr);
	
    void ujawnijDeklaracje();

	void podsumujRozdanie();
	
	void wypiszWynikiGry();
	
	void setLiczbaKart(int l);
	
	void setKtoWistuje(int w);
	
    void dajKartyGraczowi(QVector<Karta> v, int nr);

    void wyroznijDozwoloneKarty();

    void wylaczWyroznienie();

	/* nr gracza po lewej od aktualnego */
	int kolejnyGracz(int aktualnyGracz);
	
    /* czy rozdanie zostalo zakonczone */
    bool koniecRozdania() const;

    bool kartaONumerzePoprawna(int nrKarty, int nrGracza) const;
    bool graczPosiadaKartyWKolorze(int kolor, int nrGracza) const;

    /* dla danej karty wykladajacego gracza zwraca jej numer */
    int numerKarty(Karta k);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void kartaKliknieta(int);

private:
    void zakonczLewe();
	void czyscStol();
    void ujawnijDeklaracjeGracza(int nr);
    void przelozKarteNaStol(int nrKarty);
    int punktyZa(int wziete, int deklarowane);
	
    void zerujWziete();
	
    /* rysuje karte na planszy */
    void dajKarteGraczowi(Karta k, int nr);

	int _liczbaGraczy;
	char _kolorWyjscia;
	int _ktoWyklada;
	int _nrLewy;
	int _liczbaKart;
	int _ktoWistuje;
	int _ktoWychodzi;
	
    bool _klikalna;

    QVector<int> _deklaracje;
    QVector<KartaSprite* > _stol;
    QVector<int> _wziete;
    QVector<int> _punkty;
	
	int _wychodzilOstatnio;
    QVector<Karta> _ostatniaLewa;

    QVector<QList<KartaSprite* > >karty;

    QVector<QGraphicsTextItem* > deklaracjeItems;
    QVector<QGraphicsTextItem* > wzieteItems;
};

#endif
