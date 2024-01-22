#ifndef WORKER_H
#define WORKER_H

#include "source.h"
#include <QThread>
#include <QVector>
#include <QMutex>

class Worker : public QThread
{
    Q_OBJECT

public:
    Worker(QVector<Source*>& sources, QMutex* mutex);
protected:
    void run() override;

private:
    QVector<Source*> m_sources;
    QMutex* m_mutex;

signals:
    void done(unsigned index, unsigned volume);
};

#endif // WORKER_H
