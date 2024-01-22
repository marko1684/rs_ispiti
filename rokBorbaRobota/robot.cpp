#include "robot.h"
#include <QVariantMap>
#include <QRandomGenerator>

Robot::Robot() {}

void Robot::fromQVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    m_name = map.value("name").toString();
    m_maximumHealth = map.value("hp").toUInt();
    m_currentHealth = m_maximumHealth;
    QList attackValues = map.value("atk").toList();
    m_minimumStrength = attackValues[0].toUInt();
    m_maximumStrength = attackValues[1].toUInt();
}

QString Robot::toQString()
{
    return m_name + " : hp=" + QString::number(m_maximumHealth) + ", atk=["+QString::number(m_minimumStrength) + "," + QString::number(m_maximumStrength) +"]";
}

bool Robot::attack(Robot *robot)
{
    // unsigned percentOfDeduction = (unsigned)(((double)m_currentHealth / m_maximumHealth) * 100);
    // unsigned attackStrength = (unsigned)((double)QRandomGenerator::global()->bounded(m_minimumStrength, m_maximumStrength + 1) * double(1 - (double)percentOfDeduction/100));
    unsigned attackStrength = QRandomGenerator::global()->bounded(m_minimumStrength, m_maximumStrength + 1);
    qDebug() << robot->currentHealth() - attackStrength;
    if((int)robot->currentHealth() - (int)attackStrength <= 0){
        robot->setCurrentHealth(0);
        return true;
    }
    else{
        robot->setCurrentHealth(robot->currentHealth() - attackStrength);
        return false;
    }
}

void Robot::setCurrentHealth(unsigned int health)
{
    m_currentHealth = health;
}
