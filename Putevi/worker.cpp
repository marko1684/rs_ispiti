#include "worker.h"
#include <QMutex>
#include <QMutexLocker>


Worker::Worker(QVector<City*> cities, unsigned i) :
    m_i(i),
    m_cities(cities)
{}

void Worker::run()
{
    qDebug() << "uslo u nit: " << m_i;
    QMutexLocker lockOne(m_cities[m_i]->getMutex());

    double closesetDistance = 100000.0;
    unsigned index = 0;
    for(unsigned j = 0; j < m_cities.size(); j++){
        if(j != m_i && !m_cities[j]->Visited()){
            double distance = sqrt(pow((m_cities[m_i]->X() - m_cities[j]->X()),2) + pow((m_cities[m_i]->Y() - m_cities[j]->Y()), 2));
            if(distance < closesetDistance){
                closesetDistance = distance;
                index = j;
            }
        }
    }

    QMutexLocker lockTwo(m_cities[index]->getMutex());
    m_cities[index]->setVisited(true);
    emit roadBuilt(m_i, index);
}

