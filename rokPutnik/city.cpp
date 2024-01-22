#include "city.h"
#include <QRandomGenerator>
#include <QVariantMap>
#include <QVariant>

City::City()
{

}

void City::fromQVariant(QVariant &variant)
{
    QVariantMap map = variant.toMap();
    m_name = map.value("name").toString();
    const auto coordinates = map.value("coordinates").toList();
    m_x = coordinates[0].toUInt();
    m_y = coordinates[1].toUInt();
    const auto articles = map.value("articles").toList();
    for(auto& article : articles){
        m_articleArr.push_back(article.toString());
    }
}

QString City::toQString()
{
    return m_name + "(" + QString::number(m_x) + ", " + QString::number(m_y) + "): Broj artikala = " + QString::number(m_articleArr.size());
}

QString City::getRandomArticle()
{
    if(m_articleArr.isEmpty()){
        return "";
    }else{
        auto i = QRandomGenerator::global()->generate() % m_articleArr.size();
        const auto tmpArticle = m_articleArr[i];
        m_articleArr.removeAt(i);
        return tmpArticle;
    }
}

unsigned int City::distance(City* city)
{
    // |x1 - x2| + |y1 - y2|
    return qAbs((int)city->getX() - (int)m_x) + qAbs((int)city->getY() - (int)m_y);
}
