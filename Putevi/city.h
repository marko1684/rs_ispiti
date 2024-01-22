#ifndef CITY_H
#define CITY_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QMutex>

class City
{
public:
    City();
    void fromQVariant(const QVariant& variant);
    QString toQString() const;
    void setVisited(bool visited);
    inline QMutex* getMutex(){return &m_cityMutex;};
    inline double X(){return m_x;};
    inline double Y(){return m_y;};
    inline bool Visited(){return m_visited;};
    inline QString Name(){return m_name;};

private:
    QString m_name;
    double m_x;
    double m_y;
    bool m_visited = false;
    QMutex m_cityMutex;
};

#endif // CITY_H
