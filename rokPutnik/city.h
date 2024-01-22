#ifndef CITY_H
#define CITY_H

#include <QString>
#include <QVector>

class City
{
public:
    City();
    void fromQVariant(QVariant& variant);
    QString toQString();
    QString getRandomArticle();
    unsigned distance(City* city);
    inline QString getName() const{return m_name;};
    inline unsigned getX() const{return m_x;};
    inline unsigned getY() const{return m_y;};
    QVector<QString> getArticleArray() const{return m_articleArr;};

private:
    QString m_name;
    unsigned m_x;
    unsigned m_y;
    QVector<QString> m_articleArr;
};

#endif // CITY_H
