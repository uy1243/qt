#include "parsedbc.h"
#include<qdebug.h>

#pragma comment(lib,"python36.lib")

ParseDBC::ParseDBC()
{



}

void ParseDBC::InitPy()
{
    Py_Initialize();
    if (!Py_IsInitialized()) {
            return;
        }

//    PyRun_SimpleString("print('hello world')\n");
//    //运行脚本导入环境变量
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("import os");
//    PyRun_SimpleString("import string");
    //QString m_strPyLocation="C:\\Users\\naiyu.ru\\OneDrive - Veoneer\\Documents\\MyQt\\PVC";
    //py文件的存放位
    //QString strPyPath = QString("sys.path.append('") + m_strPyLocation + QString("')");

    //const char* c = strPyPath.toStdString().c_str();
    //PyRun_SimpleString("sys.path.append('.\')");
    //PyRun_SimpleString(c);

//    qDebug()<<strPyPath.toStdString().c_str()<<endl;
//    PyObject *sys_path = PySys_GetObject("path");
//    PyList_Append(sys_path, PyUnicode_FromString("C:/Users/naiyu.ru/OneDrive\ -\ Veoneer/Documents/MyQt/PVC"));
//    qDebug()<<&sys_path<<endl;
    /* 1st: Import the module */
    /* This is to add the path in the code */
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));
       PyObject* ModuleString = PyUnicode_FromString((char*) "PyParDBC");
       if (!ModuleString) {
           PyErr_Print();
           printf("Error formating python script\n");
       }

       PyObject* pModule = PyImport_Import(ModuleString);
       if (!pModule) {
           PyErr_Print();
           printf("Error importing python script\n");
       }
//    PyObject *sys = PyImport_ImportModule("sys");
//      PyObject *path = PyObject_GetAttrString(sys, "path");
//      PyList_Append(path, PyUnicode_FromString("."));
//     PyObject *pName,*pModule;
//     pName = PyUnicode_FromString((char*)"PyParDBC");
//     pModule =PyImport_Import(pName);

     PyObject*    pFunc= PyObject_GetAttrString(pModule, "Hello");
     PyEval_CallObject(pFunc, NULL);

    Py_Finalize();
}

QString ParseDBC::parseMess(QString mess)
{

}
