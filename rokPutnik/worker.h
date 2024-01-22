#ifndef WORKER_H
#define WORKER_H

#include "city.h"

#include <QMutex>
#include <QThread>
#include <QRandomGenerator>
#include <QVector>

class Worker : public QThread
{
Q_OBJECT
public:
    Worker(QVector<City*> cities, QMutex* mutex);
private:
    unsigned m_distancePassed;
    QVector<City*> m_cities;
    QMutex* m_mutex;

protected:
    void run() override;
signals:
    void done(unsigned);
    void takenArticle(unsigned, QString);
};

#endif // WORKER_H
