#include "city.h"

#include <QVariantMap>

City::City() {}

void City::fromQVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    m_x = map.value("x").toDouble();
    m_y = map.value("y").toDouble();
    m_name = map.value("name").toString();
}

QString City::toQString() const
{
    return m_name + "---> (" + QString::number(m_x) + ", " + QString::number(m_y) + ")";
}

void City::setVisited(bool visited)
{
    m_visited = visited;
}
