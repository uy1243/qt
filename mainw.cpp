#include "mainw.h"
#include <QObject>
#include<qdebug.h>
#include<QQmlApplicationEngine>
#include <QQuickView>




MainW::MainW(QWidget *parent)
    : QMainWindow(parent, 0)

{
   // qb=new QPushButton("stop");
qt=new QTextEdit();
    setCentralWidget(qt);



}

void MainW::sne()
{
    emit sMess(QString("hi"));
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
