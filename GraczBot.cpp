#include "GraczBot.h"
using namespace std;

GraczBot::GraczBot(int nr) : Gracz(nr) { }

int GraczBot::wybierzDeklaracje() {
    int d = liczbaKart / plansza->liczbaGraczy();
    return d;
}

void GraczBot::wybierzKarte() {
    int idx = 0;
    while(!plansza->kartaONumerzePoprawna(idx, nr)) {
        idx++;
    }
    emit kartaWybrana(idx);
}
