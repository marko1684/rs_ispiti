#ifndef WORKER_H
#define WORKER_H

#include "robot.h"
#include <QThread>
#include <QVector>
#include <QMutex>

class Worker : public QThread
{
    Q_OBJECT

public:
    Worker(QVector<Robot*> m_robots, QMutex* mutex, unsigned first, unsigned second);
protected:
    void run() override;
signals:
    void battleFinished(unsigned, unsigned, bool);
private:
    QVector<Robot*> m_robots;
    QMutex* m_mutex;
    unsigned m_first;
    unsigned m_second;

};

#endif // WORKER_H
