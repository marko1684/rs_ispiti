#include "worker.h"
#include <QRandomGenerator>

Worker::Worker(QVector<Robot*> robots, QMutex* mutex, unsigned first, unsigned second)
    : m_robots(robots)
    , m_mutex(mutex)
    , m_first(first)
    , m_second(second)
    {}

void Worker::run(){

    QMutexLocker lockOne(m_robots[m_first]->getMutex());
    QMutexLocker lockTwo(m_robots[m_second]->getMutex());

    m_robots[m_first]->setCurrentHealth(m_robots[m_first]->maximumHealth());
    m_robots[m_second]->setCurrentHealth(m_robots[m_second]->maximumHealth());


    while(true){
        unsigned attacker = QRandomGenerator::global()->bounded(0, 2);
        if(attacker == m_first){
            bool dead = m_robots[m_first]->attack(m_robots[m_second]);
            if(dead){
                qDebug() << "nesto1";
                emit battleFinished(m_first, m_second, true);
                break;
            }
        }else{
            bool dead = m_robots[m_second]->attack(m_robots[m_first]);
            if(dead){
                qDebug() << "nesto2";
                emit battleFinished(m_first, m_second, false);
                break;
            }

        }
    }

}


