#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "city.h"

#include <QMutex>
#include <QWidget>
#include <QMap>

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
    void on_buttonBeginVisit_clicked();
public slots:
    void on_takenArticle(unsigned i, QString article);
    void on_threadFinished(unsigned distance);

private:
    Ui::MainWindow *ui;
    QVector<City*> m_cities;
    QMutex m_mutex;
    QMap<QString, unsigned> m_collectedArticles;
    unsigned m_totalDistancePassed = 0;
    unsigned m_activeThreads = 0;
};
#endif // MAINWINDOW_H
