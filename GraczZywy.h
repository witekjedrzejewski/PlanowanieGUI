#ifndef GRACZZYWY_H
#define	GRACZZYWY_H

#include "Gracz.h"

class GraczZywy : public Gracz {
public:
	GraczZywy(int);
protected:		
	virtual int wybierzDeklaracje();
    virtual void wybierzKarte();
private slots:
    void kartaKliknieta(Karta);
private:
	ItKarta wczytajKarte();
    void wyroznijDozwoloneKarty();

};

#endif	/* GRACZZYWY_H */

