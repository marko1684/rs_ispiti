#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "city.h"

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonLoadCities_clicked();
    void on_buttonBuildRoads_clicked();
    void on_roadBuilt(unsigned i, unsigned j);

private:
    Ui::MainWindow *ui;
    QVector<City*> m_cities;
    int m_numberOfActiveThreads = 0;
};
#endif // MAINWINDOW_H
