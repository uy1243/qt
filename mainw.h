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
     void sne();
     void loadQML();
public slots:
     void showMess(QString mess);
signals:
     void sMess(QString mess);
};

#endif // MAINW_H
