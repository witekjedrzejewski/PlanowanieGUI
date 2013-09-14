#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <QDebug>

#include "Talia.h"

using namespace std;

Talia::Talia() {
	srand(time(0));
	
	for (int i = 0; i < 52; i++) {
		karty.push_back(Karta(i));
	}
	random_shuffle(karty.begin(), karty.end(), Talia::mRand);
	
    /*
    for (int i = 0; i < 52; i++) {
        qDebug() << karty[i].toQString();
    }
    */

}

Karta Talia::getKarta() {
	Karta k = karty.back();
	karty.pop_back();
	return k;
}

std::vector<Karta> Talia::getKarty(int liczbaKart) {
	vector<Karta> k(karty.end() - liczbaKart, karty.end());
	assert((int)k.size() == liczbaKart);
	karty.resize(karty.size() - liczbaKart);
	return k;
}

int Talia::mRand(int i) {
	return rand() % i;
}
