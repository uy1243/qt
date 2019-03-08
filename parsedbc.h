#pragma once
#ifndef PARSEDBC_H
#define PARSEDBC_H
#include<QObject>
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")
//#include "Python.h"

class ParseDBC
{
public:
    ParseDBC();
    void InitPy();
    QString parseMess(QString mess);
};

#endif // PARSEDBC_H
