#include "mainw.h"
#include <QObject>
#include<qdebug.h>





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



void MainW::showMess(QString mess)
{
  // qt->append(mess);
    qDebug()<<mess;

}
