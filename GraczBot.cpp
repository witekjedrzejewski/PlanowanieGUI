#include "GraczBot.h"
using namespace std;

GraczBot::GraczBot(int nr) : Gracz(nr) { }

int GraczBot::wybierzDeklaracje() {
	int d = reka.size() / plansza->liczbaGraczy();
	cerr << "Gracz " << nr << " deklaruje " << d 
					<< " (" << wypiszReke() << ")" << endl;
	return d;
}

void GraczBot::wybierzKarte() {
	ItKarta iter = reka.begin();
	while(!kartaPoprawna(iter)) {
		iter++;
	}
    /* cerr << "Gracz " << nr << " wybiera " << *iter
					<< " ( z " << wypiszReke() << ")" << endl;
    */
    wybranaKarta = iter;
    Gracz::wybierzKarte();
}
