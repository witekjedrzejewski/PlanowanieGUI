#include "mainwindow.h"

#include <QGraphicsView>
#include <vector>

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
    vector<bool> g (2, 0);
    g[0] = 1;

    vector<int> r (1, 10);

    gra = new Gra(g, r);
    plansza = gra->getPlansza();
    view->setScene(plansza);
    show();
    gra->uruchom();
}
