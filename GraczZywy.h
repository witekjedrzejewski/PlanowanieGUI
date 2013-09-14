#ifndef GRACZZYWY_H
#define	GRACZZYWY_H

#include "Gracz.h"

class GraczZywy : public Gracz {
    Q_OBJECT

public:
	GraczZywy(int);
protected:		
	virtual int wybierzDeklaracje();
    virtual void wybierzKarte();
protected slots:
    void kartaKliknieta(int);
private:
    void wyroznijDozwoloneKarty();

};

#endif	/* GRACZZYWY_H */

