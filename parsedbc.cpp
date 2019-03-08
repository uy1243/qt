#include "parsedbc.h"

#pragma comment(lib,"python36.lib")

ParseDBC::ParseDBC()
{



}

void ParseDBC::InitPy()
{
      Py_Initialize();
//    if (!Py_IsInitialized()) {
//            return;
//        }

//    PyRun_SimpleString("print('hello world')\n");

//     PyObject* pModule =PyImport_ImportModule("PyParDBC");
//     PyObject*    pFunc= PyObject_GetAttrString(pModule, "Hello");
//     PyEval_CallObject(pFunc, NULL);

//    Py_Finalize();
}

QString ParseDBC::parseMess(QString mess)
{

}
