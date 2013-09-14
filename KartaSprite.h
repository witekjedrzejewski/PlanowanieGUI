#ifndef KARTASPRITE_H
#define KARTASPRITE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

#include "Karta.h"

class KartaSprite : public QGraphicsRectItem
{

public:
    KartaSprite(Karta k, QGraphicsItem *parent = 0);
    ~KartaSprite() {}

    enum { Type = UserType + 1 };
    virtual int type() const;

    Karta karta() const;
    void wyroznij();
    void wylaczWyroznienie();
    bool wyrozniona() const;

public slots:

private:
    Karta _karta;
    bool _wyrozniona;
    static const QColor kolory[5];
    QGraphicsTextItem* tekst;
};

#endif // KARTASPRITE_H
