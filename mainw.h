#ifndef MAINW_H
#define MAINW_H
#include<QtWidgets/QFrame>
#include<QtWidgets/QLabel>
#include<QtWidgets/qlayout.h>
#include<QtWidgets/qpushbutton.h>
#include"funccan.h"
#include<QMainWindow>
#include <QPlainTextEdit>


class MainW: public QMainWindow
{

Q_OBJECT
public:
     explicit MainW(QWidget *parent = nullptr);
     QPushButton *qb;
     QTextEdit *qt;
     void sendMessages();
     void loadQML();
public slots:
     void showMess(QString mess);
     void showMessInGUI(QString mess);
signals:
     void sigMess(QString mess);
};

#endif // MAINW_H
