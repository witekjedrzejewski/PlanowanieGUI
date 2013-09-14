#include "KartaSprite.h"

#include <QFont>
#include <QBrush>
#include <QDebug>

const QColor KartaSprite::kolory[] = {Qt::yellow, Qt::green, Qt::blue, Qt::red, Qt::black};

KartaSprite::KartaSprite(Karta k, QGraphicsItem *parent) :
    QGraphicsRectItem(parent), _karta(k)
{
    QString s = "";
    s += k.wysokoscToChar();
    tekst = new QGraphicsTextItem(s, this);
    QFont font;
    font.setBold(true);
    font.setPixelSize(25);
    font.setFamily("Verdana");
    font.setFixedPitch(true);
    font.setStyleHint(QFont::Monospace);
    tekst->setFont(font);

    tekst->setDefaultTextColor(kolory[k.kolor()]);

    setRect(0, 0, 30, 40);

    setBrush(Qt::white);

    _wyrozniona = false;
}

int KartaSprite::type() const {
    return Type;
}

Karta KartaSprite::karta() const {
    return _karta;
}

void KartaSprite::wyroznij() {
    //qDebug() << "wyrozniam " << karta.toQString();
    _wyrozniona = true;
    setBrush(Qt::yellow);
    //connect(this, SIGNAL(mo))
}

bool KartaSprite::wyrozniona() const {
    return _wyrozniona;
}

void KartaSprite::wylaczWyroznienie() {
    _wyrozniona = false;
    setBrush(Qt::white);
}
