#include "mainwindow.h"

#include <QGraphicsView>
#include <QVector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("Planowanie"));
    setFixedSize(800, 500);
    layout = new QVBoxLayout;
    view = new QGraphicsView;
    layout->addWidget(view);

    widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::uruchomGre() {

    QVector<bool> gracze (3, 1);
    QVector<int> rozdania (2, 3);

    gra = new Gra(gracze, rozdania);

    plansza = gra->getPlansza();
    view->setScene(plansza);
    show();
    gra->uruchom();
}
