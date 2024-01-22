#ifndef WIDGET_H
#define WIDGET_H
#include "robot.h"

#include <QWidget>
#include <QVector>
#include <QMutex>
#include <QMutexLocker>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_button_loadRobots_clicked();
    void on_button_beginBattle_clicked();
    void on_battleFinished(unsigned, unsigned, bool);

private:
    Ui::Widget *ui;
    QVector<Robot*> m_robots;
    QMutex m_mutex;
    unsigned m_numOfActiveThreads = 0;
};
#endif // WIDGET_H
