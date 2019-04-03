#include "mulgetmess.h"
#include<qdebug.h>

mulGetMess::mulGetMess(QObject *parent) :
    QThread(parent)
{
}

//! [0]
mulGetMess::~mulGetMess()
{
    wait();
}
//! [0]
bool mulGetMess::getMessage(TStruct &par)
{
    msgsrx = 1;
    g_bThreadRun=true;
    *g_th = par;
    //printf("thread: SetNotification '%d'\n", g_th->hMsgEvent);
    return true;
}


void mulGetMess::stop()
{
    quit();
    wait();
}

void mulGetMess::run()
{
    printf("g_th->xlPortHandle=%d\n",g_th->xlPortHandle);
    while (g_bThreadRun) {
        //WaitForSingleObject(g_th->hMsgEvent, 10);
        sleep(1);
        xlStatus = XL_SUCCESS;
        while (!xlStatus) {
            msgsrx = 1;
            xlStatus = xlReceive(g_th->xlPortHandle, &msgsrx, &xlEvent);//receive data into xlEvent
            //printf("xlstatus=%d\n",xlStatus);
            //printf( "xlReceive function:\n xlReceive:msgsrx-eventcount:%d\n",
            //   msgsrx);
            //AfxMessageBox(CString (xlGetEventString(&xlEvent)));
            if (xlStatus != XL_ERR_QUEUE_IS_EMPTY) {
                QString me(xlGetEventString(&xlEvent));
                if(xlEvent.tagData.msg.data!=NULL){
                    qDebug()<<"string="<< xlEvent.tagData.msg.data<<"end of this"<<""
                              ;
                }
                else {
                    printf("msg que null!\n");
                }

                // sleep(1);
                if(me!=NULL) emit sigCANMes(me);
                //g_th->cm = xlGetEventString(&xlEvent);

            }
        }

    }
}
