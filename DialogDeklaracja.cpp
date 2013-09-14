#include "DialogDeklaracja.h"
#include <QPushButton>

DialogDeklaracja::DialogDeklaracja(int m, QWidget *parent) :
    QDialog(parent), maxLew(m)
{
    setModal(true);
    setWindowTitle(tr("deklaracja"));
    QHBoxLayout* layout = new QHBoxLayout;

    spinner = new QSpinBox();
    spinner->setRange(0, maxLew);
    spinner->setValue(0);

    QPushButton* okButton = new QPushButton(tr("OK"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

    layout->addWidget(spinner);
    layout->addWidget(okButton);

    setLayout(layout);
}

void DialogDeklaracja::accept() {
    _deklaracja = spinner->value();
    QDialog::accept();
}

int DialogDeklaracja::deklaracja() const {
    return _deklaracja;
}
