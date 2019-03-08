#include "mainw.h"
#include <QObject>
#include<qdebug.h>
#include<QQmlApplicationEngine>
#include <QQuickView>




MainW::MainW()

{
   // qb=new QPushButton("stop");
    qt=new QTextEdit();
    view= new QQuickView();

}

void MainW::sendMessages()
{
    emit sigMess(QString("hi"));
}

void MainW::loadQML()
{

    view->setSource(QStringLiteral("qrc:///vec.qml"));

}



void MainW::showMess(QString mess)
{
  // qt->append(mess);
    qDebug()<<mess;

}
void MainW::showMessInGUI(QString mess)
{
  //qt->append(mess);
    qDebug()<<mess;

}
