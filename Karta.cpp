#include <iostream>
#include <sstream>
#include <QString>
#include <QDebug>
#include "Karta.h"

using namespace std;

const int Karta::ATU = 1;

const char Karta::kolory[] = {'0', 'C', 'D', 'H', 'S'};
const char Karta::figury[] = {'T', 'J', 'Q', 'K', 'A'};

int Karta::wysokoscFromChar(char c) {
	int w = c - '0';
	if (w >= 2 && w <= 9)
		return w;
	for (int i = 0; i < 5; i++)
		if (figury[i] == c)
			return i + 10;
	return 0; // brak odpowiedniej wysokosci
}

int Karta::kolorFromChar(char c) {
	for (int i = 1; i < 5; i++)
		if (kolory[i] == c)
			return i;
	return 0; // brak odpowiedniego koloru
}

Karta::Karta() : _kolor(0), _wysokosc(0) {
}

Karta::Karta(int p) {
	_wysokosc = (p % 13) +2;
	_kolor = (p/13) + 1;
}

Karta::Karta(std::string s) {
	_wysokosc = wysokoscFromChar(s[0]);
	_kolor = kolorFromChar(s[1]);
}

Karta::Karta(const Karta& k) 
	: _kolor(k._kolor), _wysokosc(k._wysokosc) { }

Karta& Karta::operator=(const Karta& k)
{
    if (&k != this) {
        _wysokosc = k._wysokosc;
        _kolor = k._kolor;
    }
    return *this;
}

bool Karta::operator==(const Karta& k) const {
	return _kolor == k._kolor && _wysokosc == k._wysokosc;
}

int Karta::kolor() const {
	return _kolor;
}

int Karta::wysokosc() const {
	return _wysokosc;
}

bool Karta::lepszaNizWychodzaca(const Karta &k) {
	if (_kolor == k._kolor) {
		return _wysokosc > k._wysokosc;
	}
	return _kolor == ATU;
}

string Karta::toString() const {
    ostringstream oss;
    oss << *this;
    return oss.str();
}

QString Karta::toQString() const {
    return QString::fromStdString(toString());
}

ostream& operator<<(ostream& os, const Karta& k) {
	if (k._wysokosc <= 9) {
		os << k._wysokosc;
	} else {
		os << Karta::figury[k._wysokosc - 10];
	}
	
	os << Karta::kolory[k._kolor];
	return os;
}

char Karta::wysokoscToChar() const {
    return toString()[0];
}
