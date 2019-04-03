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
    PyObject *pArgs = PyTuple_New(1);               //函数调用的参数传递均是以元组的形式打包的,2表示参数个数
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", "parse dbc"));
    PyEval_CallObject(pFunc, pArgs);

    Py_Finalize();
}

QString ParseDBC::parseMess(QString mess)
{


    Py_Initialize();
    if (!Py_IsInitialized()) {
        return NULL;
    }

    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("sys.path.append()");
//    PyObject *pNumpy = PyUnicode_FromString("cantools");
//    PyObject *pModuleA = PyImport_Import(pNumpy);
    PyRun_SimpleString("import cantools\n");
//    PyRun_SimpleString("from pprint import pprint\n");
//    PyRun_SimpleString("from struct import pack\n");
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

    PyObject*    pFunc= PyObject_GetAttrString(pModule, "Hello");

    PyObject* pArgsD = PyDict_New();

//    QString mid=mess.mid(32,4);
//    QString mdata=mess.mid(39,17);

//    int    nValude    =   0;
//    printf("mdata.toLatin1().data()=%s\n",mdata.toLatin1().data());
//     sscanf(mdata.toStdString().c_str(),"%017x",&nValude);
//     printf("nValude=%017x\n",nValude);

//     QString mid=mess.mid(32,4);
//     QString mdata=mess.mid(39,17);

//     int    nValude    =   0x0;
//     printf("mdata.toLatin1().data()=%s\n",mdata.toLatin1().data());
//      sscanf(mdata.toStdString().c_str(),"%017x",&nValude);
//      printf("nValude=%017x\n",nValude);
//      qDebug()<<nValude;
    //QString my_formatted_string = QString("%1/%2-%3.txt").arg("~", "Tom", "Jane");
    //qDebug()<<"hex="<<QString::number( mdata.toInt(), 16 ).toUpper();
    //qDebug()<<"mdata="<<mdata<<" mdata.toInt()="<<mdata.to<<"\n";

    QString mid="0x"+mess.mid(32,4);
    QString mdata="0x"+mess.mid(40,17);
    PyObject *pArgs = PyTuple_New(1);
    PyObject *pDict = PyDict_New(); //创建字典类型变量
    PyDict_SetItemString(pDict, "id", Py_BuildValue("s", mid.toLatin1().data())); //往字典类型变量中填充数据
    PyDict_SetItemString(pDict, "data", Py_BuildValue("s", mdata.toLatin1().data())); //往字典类型变量中填充数据
    PyTuple_SetItem(pArgs, 0, pDict);

    PyObject *pReturn =PyEval_CallObject(pFunc, pArgs);
    if (pReturn == NULL)
    {
        printf("PyEval_CallObject failed!\n");
      return NULL;
    }
    int size = PyDict_Size(pReturn);
    PyObject *pNewAge = PyDict_GetItemString(pReturn, "data");
    char* newAge;
    PyArg_Parse(pNewAge, "s", &newAge);


    if (newAge != NULL)
    {
      qDebug()<<"pReturn value!="<<newAge;
    }


    Py_Finalize();

}
