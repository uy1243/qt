#ifndef PARSEDBC_H
#define PARSEDBC_H
#include<QObject>
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")

#pragma comment(lib,"python36.lib")

class ParseDBC
{
public:
    ParseDBC();
    QString parseMess(QString mess);
};

#endif // PARSEDBC_H
