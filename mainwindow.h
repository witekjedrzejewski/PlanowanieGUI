#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "Gra.h"
#include "Plansza.h"

class QGraphicsView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void uruchomGre();

private:
    Gra* gra;
    Plansza* plansza;
    QVBoxLayout* layout;
    QGraphicsView* view;
    QWidget* widget;
};

#endif // MAINWINDOW_H
