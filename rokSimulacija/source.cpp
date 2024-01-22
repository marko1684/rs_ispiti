#include "source.h"
#include "qvariant.h"

Source::Source() {}

void Source::fromQVariant(const QVariant &variant)
{
    const QVariantMap map = variant.toMap();
    m_sourceName = map.value("name").toString();
    m_volume = map.value("volume").toUInt();
}

bool Source::isEmpty(){
    if(m_volume == 0u){
        return true;
    }
    return false;
}

unsigned int Source::releasedFromSource(unsigned int volume){
    if(m_volume >= volume){
        m_volume -= volume;
    }else{
        volume = m_volume;
        m_volume = 0u;
    }
    return volume;
}

QString Source::toQString()
{
    return !this->isEmpty() ? m_sourceName + " - " + QString::number(m_volume) : m_sourceName + " - izvor je iscrpljen";
}
