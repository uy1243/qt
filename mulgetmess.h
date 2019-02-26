#ifndef MULGETMESS_H
#define MULGETMESS_H

#include"funccan.h"


#include <QMutex>
#include <QThread>
#include <QWaitCondition>

//! [0]
class mulGetMess : public QThread
{
    Q_OBJECT

public:
    explicit mulGetMess(QObject *parent = nullptr);
    ~mulGetMess();
    QString getMess();
    bool getMessage(TStruct &par);
private:
    void run() override;


    void stop();
    bool g_bThreadRun;
    XLstatus        xlStatus;
    unsigned int    msgsrx ;
    XLevent         xlEvent;
    char            tmp[110];
    QString         mess;
    TStruct *g_th;
signals:
    void sMes(QString mess);
};
//! [0]

#endif // MASTERTHREAD_H


