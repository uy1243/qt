#ifndef MAINW_H
#define MAINW_H
#include<QtWidgets/QFrame>
#include<QtWidgets/QLabel>
#include<QtWidgets/qlayout.h>
#include<QtWidgets/qpushbutton.h>
#include"funccan.h"
#include<QMainWindow>
#include <QPlainTextEdit>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include"parsedbc.h"


class MainW: public QObject
{

    Q_OBJECT
public:
     MainW();
     QPushButton *qb;
     QTextEdit *qt;
     void sendMessages();
     void loadQML();
     QQuickView *view;
     QString CANMess;
     ParseDBC* pyDBC;
private:

public slots:
     void showMess(QString mess);
     void showMessInGUI(QString mess);
signals:
     void sigMess(QString mess);
};

#endif // MAINW_H
