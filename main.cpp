#include <QApplication>
#include"funccan.h"
#include<qdebug.h>
#include<stdio.h>
#include "vxlapi.h"
#include"mulgetmess.h"
#include"mainw.h"
#include<QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
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

    ParseDBC* pd=new ParseDBC();
    pd->InitPy();
    QObject::connect(mw, &MainW::sigMess,mw, &MainW::showMessInGUI);
    //mw->loadQML();
    mw->sendMessages();

    mulGetMess *mulM=new mulGetMess();
    mulM->getMessage(gth);
    mulM->start();
    QObject::connect(mulM, &mulGetMess::sigCANMes,mw, &MainW::showMess);

    //qmlRegisterType<MainW>("MainW", 1,0, "MainW");

    //view.rootContext()->setContextProperty("applicationData", &data);

    QQmlApplicationEngine engine(QStringLiteral("qrc:///mwq.qml"));
    //QQmlContext *context = new QQmlContext(engine.rootContext());
    engine.rootContext()->setContextProperty("mw", mw);

    if (engine.rootObjects().isEmpty())return -1;

    //mw->view->show(); disable this window,not show

    return app.exec();
}
