#include <QApplication>
#include"funccan.h"
#include<qdebug.h>
#include<stdio.h>
#include "vxlapi.h"
#include"mulgetmess.h"
#include"mainw.h"
#include<QObject>
#include <QQmlApplicationEngine>
#include <QQuickView>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FuncCAN fc;
    fc.CANInit();
    TStruct gth=fc.getG_th();
    unsigned long baudrate=100000;
    fc.CANGoOnBus(baudrate);

    MainW *mw=new MainW();

    QObject::connect(mw, &MainW::sigMess,mw, &MainW::showMessInGUI);
    mw->loadQML();
    mw->sendMessages();

    mulGetMess *mulM=new mulGetMess();
    mulM->getMessage(gth);
    mulM->start();
    QObject::connect(mulM, &mulGetMess::sigCANMes,mw, &MainW::showMess);

    QQmlApplicationEngine engine(QStringLiteral("qrc:///mwq.qml"));

    mw->view->show();

    return app.exec();
}
