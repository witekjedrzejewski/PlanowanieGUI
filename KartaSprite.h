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

    void wyroznij();

public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    Karta karta;
    static const QColor kolory[5];
    QGraphicsTextItem* tekst;
};

#endif // KARTASPRITE_H
