#include <QApplication>
#include"funccan.h"
#include<qdebug.h>
#include<stdio.h>
#include "vxlapi.h"
#include"mulgetmess.h"
#include"mainw.h"
#include<QObject>
#include <QQmlApplicationEngine>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   // qmlRegisterType<FuncCAN>("People", 1,0, "Person");






  //  QQmlApplicationEngine engine;
   // engine.load(QUrl(QStringLiteral("C:/vec.qml")));

   // qDebug()<<("init can!\n");
   FuncCAN fc;
  fc.CANInit();
    TStruct gth=fc.getG_th();
    unsigned long baudrate=100000;
    fc.CANGoOnBus(baudrate);

qDebug()<<gth.xlPortHandle;
  // ms->getMessage(gth);
   MainW *mw=new MainW();







        //QObject::connect(mw.qb, SIGNAL(released(int)),&ms,  SLOT(stopMess()));
 //QObject::connect(mw, &MainW::sMess,mw, &MainW::showMess);
 mw->loadQML();
  //mw->show();
mw->sne();

mulGetMess *mulM=new mulGetMess();
mulM->getMessage(gth);
mulM->start();
 QObject::connect(mulM, &mulGetMess::sMes,mw, &MainW::showMess);
   //QObject::connect(qb, SIGNAL (released()), fc, SLOT (canInit()));
    return app.exec();
}
