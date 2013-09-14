#include <cassert>
#include <QGraphicsTextItem>
#include <QDebug>

#include "Plansza.h"
#include "KartaSprite.h"

using namespace std;

Plansza::Plansza(int liczbaGraczy, QObject *parent)
    : QGraphicsScene(parent), _liczbaGraczy(liczbaGraczy)
{
    _stol = vector<Karta>(liczbaGraczy);
	_deklaracje = vector<int>(liczbaGraczy);
	_wziete = vector<int>(liczbaGraczy);
	_punkty = vector<int>(liczbaGraczy, 0);

    karty = QVector<QVector<KartaSprite*> >(liczbaGraczy);

    _nrLewy = 1;

    // deklaracje Items

    QFont font;
    font.setBold(true);
    font.setPixelSize(25);
    QGraphicsTextItem *item;
    for (int i = 0; i < liczbaGraczy; i++) {
        item = new QGraphicsTextItem;
        item->setPlainText(tr("?"));
        item->setFont(font);
        item->setPos(0, i*50);
        addItem(item);
        deklaracjeItems.push_back(item);
    }

    setBackgroundBrush(Qt::green);
    //setSceneRect(0, 0, 1000, 1000);
}

void Plansza::setLiczbaKart(int l) {
    _liczbaKart = l;
}

void Plansza::setKtoWistuje(int w) {
	_ktoWistuje = _ktoWychodzi = _ktoWyklada = w;
}

int Plansza::liczbaGraczy() const {
	return _liczbaGraczy;
}

int Plansza::ktoWychodzi() const {
	return _ktoWychodzi;
}

int Plansza::kolorWyjscia() const {
	return _kolorWyjscia;
}

vector<Karta> Plansza::stol() const {
	return _stol;
}

vector<int> Plansza::wziete() const {
	return _wziete;
}

pair<int, vector<Karta> > Plansza::ostatniaLewa() const {
	return make_pair(_wychodzilOstatnio, _ostatniaLewa);
}

int Plansza::ktoWyklada() const {
	return _ktoWyklada;
}

bool Plansza::koniecRozdania() const {
    return _nrLewy > _liczbaKart;
}

int Plansza::punktyZa(int wziete, int deklarowane) {
	return wziete + ((wziete == deklarowane) ? _liczbaKart : 0);
}

void Plansza::zeruj(vector<int>& v) {
	fill(v.begin(), v.end(), 0);
}

void Plansza::podsumujRozdanie() {
	cout << "Wyniki (wziete/deklarowane): ";
	for (int i = 0; i < _liczbaGraczy; i++) {
		int punkty = punktyZa(_wziete[i], _deklaracje[i]);
		cout << i << ": " << punkty << "(" << _wziete[i] 
						<< "/" << _deklaracje[i] << ") ";
		_punkty[i] += punkty;
	}
	cout << endl;
	
	zeruj(_wziete); 
}

void Plansza::wypiszWynikiGry() {
	cout << "WYNIKI GRY: " << endl;
	for (int i = 0; i < _liczbaGraczy; i++) {
		cout << i << ": " << _punkty[i] << " ";
	}
	cout << endl;
}

void Plansza::dolozKarteOdGracza(Karta k, int nr) {
	assert(nr == _ktoWyklada);
    qDebug() << "-> " << k.toQString() << " od gracza " << nr << ")";
	_stol[nr] = k;
	if (nr == _ktoWychodzi) {
		_kolorWyjscia=k.kolor();
	}
	_ktoWyklada = kolejnyGracz(_ktoWyklada);
	
	if (_ktoWyklada == _ktoWychodzi) {
		zakonczLewe();
	}
}

void Plansza::zakonczLewe() {
	// cerr << "Plansza.zakonczLewe" << endl;
	
	// zapisanie historii
	_ostatniaLewa = _stol;
	_wychodzilOstatnio = _ktoWychodzi;
	
	// wylonienie zwyciezcy
	int wygrany = _ktoWychodzi;
	int i = _ktoWychodzi;
	do {
		i = kolejnyGracz(i);
		if (_stol[i].lepszaNizWychodzaca(_stol[wygrany])) {
			wygrany = i;
		}
	} while (i != _ktoWychodzi);
	
    qDebug() << "Lewe wygrywa " << wygrany;
    qDebug() << "------------------";

	_ktoWychodzi = _ktoWyklada = wygrany;
	_wziete[wygrany]++;

    _nrLewy++;
	
	czyscStol();
}

void Plansza::czyscStol() {
	//cerr << "Plansza.czyscStol" << endl;
	
	for (unsigned i = 0; i < _stol.size(); i++) {
		_stol[i] = Karta(); /* TODO pusta karta */
	}
}

int Plansza::kolejnyGracz(int aktualnyGracz) {
	return (aktualnyGracz + 1) % _liczbaGraczy;
}

void Plansza::przyjmijDeklaracje(int d, int nr) {
	_deklaracje[nr] = d;
}

void Plansza::dajKarteGraczowi(Karta k, int nr) {
    KartaSprite* ks = new KartaSprite(k);
    karty[nr].push_back(ks);
    QPointF pos(35*karty[nr].size(), nr*50);
    ks->setPos(pos);

    addItem(ks);
}

void Plansza::ujawnijDeklaracje() {
    for (int i = 0; i < _liczbaGraczy; i++) {
        ujawnijDeklaracjeGracza(i);
    }
}

void Plansza::ujawnijDeklaracjeGracza(int nr) {
    qDebug() << "ujawniam " << nr;
    QString s = QString::number(_deklaracje[nr]);
    deklaracjeItems[nr]->setPlainText(s);
}

void Plansza::wyroznijKarty(int nrGracza, const QVector<bool> &doWyroznienia) {
    for (unsigned i = 0; i < doWyroznienia.size(); ++i) {
        if (doWyroznienia[i]) {
            karty[nrGracza][i]->wyroznij();
        }
    }
}
