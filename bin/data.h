#ifndef DATA_H
#define DATA_H

#include "empresa.h"

class Data
{
public:
    Data();

    Empresa getEmpresa();

private:
    Empresa empresa;
};

#endif // DATA_H
