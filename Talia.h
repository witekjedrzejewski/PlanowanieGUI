#ifndef TALIA_H
#define	TALIA_H

#include <QVector>
#include <vector>
#include "Karta.h"

class Talia {

public:
	Talia();
	Karta getKarta();

    QVector<Karta> getKarty(int liczbaKart);
	
private:
    std::vector<Karta> karty;
	static int mRand(int i);
};

#endif	/* TALIA_H */

