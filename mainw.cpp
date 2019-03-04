#include "mainw.h"
#include <QObject>
#include<qdebug.h>
#include<QQmlApplicationEngine>
#include <QQuickView>




MainW::MainW()

{
   // qb=new QPushButton("stop");
qt=new QTextEdit();

}

void MainW::sendMessages()
{
    emit sigMess(QString("hi"));
}

void MainW::loadQML()
{
    // qmlRegisterType<FuncCAN>("People", 1,0, "Person");


    QQuickView *view = new QQuickView;
        view->setSource(QStringLiteral("qrc:///vec.qml"));
        view->show();

    //QQmlApplicationEngine engine;
    //engine.addImportPath(QStringLiteral(":/imports"));
   // engine.load(QUrl(QStringLiteral("qrc:///vec.qml")));
}



void MainW::showMess(QString mess)
{
  // qt->append(mess);
    qDebug()<<mess;

}
void MainW::showMessInGUI(QString mess)
{
  qt->append(mess);

}
