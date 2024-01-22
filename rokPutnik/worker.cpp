#include "worker.h"
#include <QMutexLocker>
#include "QDebug"
Worker::Worker(QVector<City *> cities, QMutex *mutex)
    : m_cities(cities)
    , m_distancePassed(0)
    , m_mutex(mutex)
{
}

void Worker::run(){
    unsigned numOfIterrations = QRandomGenerator::global()->bounded(3, 8);
    qDebug() << numOfIterrations;
    unsigned i = QRandomGenerator::global()->bounded(0, m_cities.size());
    for(; numOfIterrations > 0; numOfIterrations--){
        qDebug() << numOfIterrations;
        msleep(QRandomGenerator::global()->bounded(250, 501));
        unsigned j = i;
        while(j == i){
            j = QRandomGenerator::global()->bounded(0, m_cities.size());
        }
        m_distancePassed += m_cities[i]->distance(m_cities[j]);
        QMutexLocker lock(m_mutex);
        QString article = m_cities[j]->getRandomArticle();
        if(!article.isEmpty()){
            emit takenArticle(j, article);
        }
        i = j;
    }
    emit done(m_distancePassed);
}
