#pragma once

#include "vxlapi.h"


#define CHAN01 0
#define CHAN02 1





class FuncCAN
{
public:
    FuncCAN();
    ~FuncCAN();

    XLstatus CANInit();
    XLstatus CANGoOnBus(unsigned long baudrate);
    XLstatus CANGoOffBus();
    XLstatus CANSend(XLevent xlEvent, int channel);
    XLstatus CANResetFilter();
    XLstatus CANSetFilter(unsigned long first_id, unsigned long last_id);
    TStruct getG_th();

    char* cm;


private:
  XLstatus         canGetChannelMask();
  XLstatus         canInit();
  XLstatus         canCreateRxThread();

  XLaccess         m_xlChannelMask[2];        //!< we support only two channels
  XLportHandle     m_xlPortHandle;            //!< and one port
  XLaccess         m_xlChannelMask_both;

  HANDLE           m_hThread;
  XLhandle         m_hMsgEvent;
  int              m_bInitDone;
};

