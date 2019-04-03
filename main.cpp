#include <QApplication>
#include"funccan.h"
#include<qdebug.h>
#include<stdio.h>
#include "vxlapi.h"
#include"mulgetmess.h"
#include"mainw.h"
#include <QMessageBox>
#include<QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QTextCodec>
#include"parsedbc.h"
#include <QTranslator>
#include"parsedbc.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FuncCAN fc;
    fc.CANInit();
    TStruct gth=fc.getG_th();
    unsigned long baudrate=100000;
    fc.CANGoOnBus(baudrate);

    MainW *mw=new MainW();

    qDebug()<<"asdasdasd";

    QString qs="C:\迅雷下载\REC_20190109_180318_GEELY car__FCA_description.txt";

    //QFile qf(QString::fromUtf8(qs.toStdString().c_str()));
    qDebug()<<qs.toStdString().data();

    ParseDBC* pd=new ParseDBC();
    pd->InitPy();
    QObject::connect(mw, &MainW::sigMess,mw, &MainW::showMessInGUI);
    //mw->loadQML();
    mw->sendMessages();

    mulGetMess *mulM=new mulGetMess();
    mulM->getMessage(gth);
    //QString canMessage
    mulM->start();
    QObject::connect(mulM, &mulGetMess::sigCANMes,mw, &MainW::showMess);

    ParseDBC *pydbc=new ParseDBC();
    QObject::connect(mulM, &mulGetMess::sigCANMes,pydbc, &ParseDBC::parseMess);

    //qmlRegisterType<MainW>("MainW", 1,0, "MainW");

    //view.rootContext()->setContextProperty("applicationData", &data);

    QQmlApplicationEngine engine(QStringLiteral("qrc:///mwq.qml"));
    //QQmlContext *context = new QQmlContext(engine.rootContext());
    engine.rootContext()->setContextProperty("mw", mw);

    if (engine.rootObjects().isEmpty())return -1;

    //mw->view->show(); disable this window,not show

    return app.exec();
}
