#ifndef PARSEDBC_H
#define PARSEDBC_H
#include<QObject>
#include"Python.h"

class ParseDBC
{
public:
    ParseDBC();
    QString parseMess(QString mess);
};

#endif // PARSEDBC_H
