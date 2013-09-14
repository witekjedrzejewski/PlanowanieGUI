#include <cassert>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "Plansza.h"
#include "KartaSprite.h"

using namespace std;

Plansza::Plansza(int liczbaGraczy, QObject *parent)
    : QGraphicsScene(parent), _liczbaGraczy(liczbaGraczy)
{
    _stol = QVector<KartaSprite* >(liczbaGraczy);
    _deklaracje = QVector<int>(liczbaGraczy);
    _wziete = QVector<int>(liczbaGraczy);
    _punkty = QVector<int>(liczbaGraczy, 0);

    karty = QVector<QList<KartaSprite*> >(liczbaGraczy);

    _nrLewy = 1;
    _klikalna = false;

    // deklaracje i wziete Items

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

        item = new QGraphicsTextItem;
        item->setPlainText(tr("0"));
        item->setFont(font);
        item->setPos(-50, i*50);
        addItem(item);
        wzieteItems.push_back(item);
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

QVector<Karta> Plansza::stol() const {
    QVector<Karta> v;
    foreach(KartaSprite* ks, _stol) {
        v.push_back(ks->karta());
    }
    return v;
}

QVector<int> Plansza::wziete() const {
	return _wziete;
}

std::pair<int, QVector<Karta> > Plansza::ostatniaLewa() const {
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

void Plansza::zerujWziete() {
    _wziete.fill(0);
    foreach (QGraphicsTextItem* item, wzieteItems) {
        item->setPlainText(tr("0"));
    }
}

void Plansza::podsumujRozdanie() {
    qDebug() << "Wyniki (wziete/deklarowane): ";
	for (int i = 0; i < _liczbaGraczy; i++) {
		int punkty = punktyZa(_wziete[i], _deklaracje[i]);
        qDebug() << i << ": " << punkty << "(" << _wziete[i]
						<< "/" << _deklaracje[i] << ") ";
		_punkty[i] += punkty;
    }
    zerujWziete();
    _nrLewy = 1;
}

void Plansza::wypiszWynikiGry() {
	cout << "WYNIKI GRY: " << endl;
	for (int i = 0; i < _liczbaGraczy; i++) {
		cout << i << ": " << _punkty[i] << " ";
	}
	cout << endl;
}

void Plansza::dolozKarteOdGracza(int nrKarty) {
    przelozKarteNaStol(nrKarty);
	_ktoWyklada = kolejnyGracz(_ktoWyklada);
	
	if (_ktoWyklada == _ktoWychodzi) {
		zakonczLewe();
	}
}

void Plansza::przelozKarteNaStol(int nrKarty) {
    int nr = _ktoWyklada;
    KartaSprite* ks = karty[nr].at(nrKarty);
    Karta k = ks->karta();
    qDebug() << "-> " << k.toQString() << " od gracza " << nr << ")";

    _stol[nr] = ks;
    if (nr == _ktoWychodzi) {
        _kolorWyjscia = k.kolor();
    }

    ks->setPos(40 * _ktoWyklada, 50 * _liczbaGraczy);
    for (int i = nrKarty + 1; i < karty[nr].size(); ++i) {
        karty[nr].at(i)->przesonWLewo(35);
    }
    karty[nr].removeAt(nrKarty);
}

void Plansza::zakonczLewe() {
	// cerr << "Plansza.zakonczLewe" << endl;
	
	// zapisanie historii
    _ostatniaLewa = stol();
	_wychodzilOstatnio = _ktoWychodzi;
	
	// wylonienie zwyciezcy
	int wygrany = _ktoWychodzi;
	int i = _ktoWychodzi;
	do {
		i = kolejnyGracz(i);
        if (_stol[i]->karta().lepszaNizWychodzaca(_stol[wygrany]->karta())) {
			wygrany = i;
		}
	} while (i != _ktoWychodzi);
	
    qDebug() << "Lewe wygrywa " << wygrany;
    qDebug() << "------------------";

	_ktoWychodzi = _ktoWyklada = wygrany;

    _wziete[wygrany]++;
    wzieteItems[wygrany]->setPlainText(QString::number(_wziete[wygrany]));

    _nrLewy++;

	czyscStol();
}

void Plansza::czyscStol() {
	//cerr << "Plansza.czyscStol" << endl;
	
    for (int i = 0; i < _stol.size(); i++) {
        removeItem(_stol[i]);
        delete _stol[i];
	}
}

int Plansza::kolejnyGracz(int aktualnyGracz) {
	return (aktualnyGracz + 1) % _liczbaGraczy;
}

void Plansza::przyjmijDeklaracje(int d, int nr) {
	_deklaracje[nr] = d;
}

void Plansza::dajKartyGraczowi(QVector<Karta> v, int nr) {
    qSort(v);
    for (int i = 0; i < v.size(); ++i) {
        dajKarteGraczowi(v[i], nr);
    }
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

void Plansza::wyroznijDozwoloneKarty() {
    _klikalna = true;
    for (int i = 0; i < karty[_ktoWyklada].size(); ++i) {
        if (kartaONumerzePoprawna(i, _ktoWyklada)) {
            karty[_ktoWyklada][i]->wyroznij();
        }
    }
}

void Plansza::wylaczWyroznienie() {
    qDebug() << "wylaczWyroznienie()";
    _klikalna = false;
    foreach(KartaSprite* ks, karty[_ktoWyklada]) {
        ks->wylaczWyroznienie();
    }
}

bool Plansza::graczPosiadaKartyWKolorze(int kolor, int nrGracza) const {
    foreach (KartaSprite* ks, karty[nrGracza]) {
        if (ks->karta().kolor() == kolor) {
            return true;
        }
    }
    return false;
}

bool Plansza::kartaONumerzePoprawna(int nrKarty, int nrGracza) const {

    assert(nrKarty >= 0 && nrKarty < karty[nrGracza].size());

    int kolor = karty[nrGracza].at(nrKarty)->karta().kolor();

    if (nrGracza == _ktoWychodzi)
        return true; // my wykladamy, wiec dowolna karta

    if (kolor == _kolorWyjscia)
        return true; // dolozone do koloru

    return !graczPosiadaKartyWKolorze(_kolorWyjscia, nrGracza);
}

int Plansza::numerKarty(Karta k) {
    for (int i = 0; i < karty[_ktoWyklada].size(); ++i) {
        if (karty[_ktoWyklada].at(i)->karta() == k) {
            return i;
        }
    }
    assert(false);
    return -1;
}

void Plansza::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!_klikalna) {
        return;
    }
    // qDebug() << "pressed" << event->scenePos();
    QList<QGraphicsItem *> itemy = items(event->scenePos());
    foreach (QGraphicsItem *item, itemy) {
        if (item->type() == KartaSprite::Type) {
            KartaSprite* ks = qgraphicsitem_cast<KartaSprite* >(item);
            if (ks->wyrozniona()) {
                // qDebug() << "kliknieta" << ks->karta().toQString();
                int idx = numerKarty(ks->karta());
                // qDebug() << "index" << idx;
                emit kartaKliknieta(idx);
            }
        }
    }
}
