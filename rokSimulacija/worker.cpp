#include "worker.h"
#include "qdebug.h"

#include <QRandomGenerator>
#include <QMutex>

Worker::Worker(QVector<Source*>& sources, QMutex *mutex)
    : m_sources(sources),
    m_mutex(mutex)
{}

void Worker::run(){
    while(true){
        msleep((QRandomGenerator::global()->generate() % 6 + 5) * 100u);
        qDebug() << "naspavao se";
        QMutexLocker lock(m_mutex);

        auto index = QRandomGenerator::global()->generate() % m_sources.size();
        auto source = m_sources[index];

        if(!source->isEmpty()){
            auto released_volume = QRandomGenerator::global()->generate() % 101 + 100;
            auto real_released = source->releasedFromSource(released_volume);
            emit done(index, real_released);
        }
    }
}
