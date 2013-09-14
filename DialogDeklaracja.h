#ifndef DIALOGDEKLARACJA_H
#define DIALOGDEKLARACJA_H

#include <QDialog>

#include <QHBoxLayout>
#include <QSpinBox>

class DialogDeklaracja : public QDialog
{
    Q_OBJECT
public:
    explicit DialogDeklaracja(int maxLew, QWidget *parent = 0);
    int deklaracja() const;

public slots:
    virtual void accept();

private:
    int maxLew;
    QSpinBox* spinner;
    int _deklaracja;
};

#endif // DIALOGDEKLARACJA_H
