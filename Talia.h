#ifndef TALIA_H
#define	TALIA_H

#include <vector>
#include "Karta.h"

class Talia {

public:
	Talia();
	Karta getKarta();

    std::vector<Karta> getKarty(int liczbaKart);
	
private:
	std::vector<Karta> karty;
	static int mRand(int i);
};

#endif	/* TALIA_H */

