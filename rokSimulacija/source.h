#ifndef SOURCE_H
#define SOURCE_H

#include <QString>

class Source
{
public:
    Source();
    inline unsigned Volume(){
        return m_volume;
    }
    void fromQVariant(const QVariant& variant);
    QString toQString();
    bool isEmpty();
    unsigned releasedFromSource(unsigned volume);

private:
    QString m_sourceName;
    unsigned m_volume;

};

#endif // SOURCE_H
