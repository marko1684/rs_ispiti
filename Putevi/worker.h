#ifndef WORKER_H
#define WORKER_H

#include "city.h"

#include <QThread>

class Worker : public QThread
{
    Q_OBJECT

signals:
    void roadBuilt(unsigned, unsigned);


protected:
    void run() override;

private:
    QVector<City*> m_cities;
    unsigned m_i;

public:
    Worker(QVector<City*> cities, unsigned i);
};

#endif // WORKER_H
