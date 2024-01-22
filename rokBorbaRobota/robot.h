#ifndef ROBOT_H
#define ROBOT_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QMutex>

class Robot
{
public:
    Robot();
    void fromQVariant(const QVariant& variant);
    QString toQString();
    bool attack(Robot* robot);
    inline unsigned minimumStrength(){return m_minimumStrength;};
    inline unsigned maximumStrength(){return m_maximumStrength;};
    inline unsigned maximumHealth(){return m_maximumHealth;};
    inline unsigned currentHealth(){return m_currentHealth;};
    inline QString Name(){return m_name;};
    void setCurrentHealth(unsigned health);
    inline QMutex* getMutex(){return &m_robotMutex;};
private:
    QString m_name;
    unsigned m_minimumStrength;
    unsigned m_maximumStrength;
    unsigned m_maximumHealth;
    unsigned m_currentHealth;
    QMutex m_robotMutex;
};

#endif // ROBOT_H
