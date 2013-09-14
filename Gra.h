#ifndef gra_H_
#define gra_H_

#include <QObject>
#include <QVector>

#include "Gracz.h"
#include "Plansza.h"

class Gra : public QObject {

    Q_OBJECT

public:
    Gra(const QVector<bool>& gracze,
        const QVector<int>& liczbyKart,
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
    QVector<Gracz*> gracze;
	
    QVector<bool> zywiGracze;
    QVector<int> liczbyKart;

};
#endif
