#ifndef gra_H_
#define gra_H_

#include <QObject>
#include <vector>

#include "Gracz.h"
#include "Plansza.h"

class Gra : public QObject {

    Q_OBJECT

public:
    Gra(const std::vector<bool>& gracze,
        const std::vector<int>& liczbyKart,
        QObject *parent = 0);
    virtual ~Gra() {}
    Plansza* getPlansza() const;
    void uruchom();

private slots:
    void graczZadeklarowal();
    void grajKarte();

private:
    void grajRozdanie();
    void poprosODeklaracje();
    void rozdajKarty();
    void zakonczRozdanie();
    void zakonczGre();
    int liczbaKart();

    int ktoWistuje;
    int liczbaGraczy;
    int przyjeteDeklaracje;
    int aktualnyIndeksLiczbyKart;

	Plansza* plansza;
	std::vector<Gracz*> gracze;
	
	std::vector<bool> zywiGracze;
	std::vector<int> liczbyKart;

};
#endif
