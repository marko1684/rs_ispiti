#ifndef THREADTRY_H
#define THREADTRY_H

#include <QThread>

class Threadtry : public QThread
{
    Q_OBJECT
public:
    explicit Threadtry(QObject *parent = nullptr);
};

#endif // THREADTRY_H
