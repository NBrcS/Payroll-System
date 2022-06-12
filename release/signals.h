#ifndef SIGNALS_H
#define SIGNALS_H

#include <QObject>
#include "data.h"

class Signals : public QObject
{
    Q_OBJECT
public:
    explicit Signals(QObject *parent = nullptr);

signals:
    void funcionario_selecionado( int );
    void passar_dados( Data& );
};

#endif // SIGNALS_H
