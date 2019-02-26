#include "FuncCAN.h"
#include"mulgetmess.h"
#include<qdebug.h>



#pragma comment(lib,"vxlapi.lib")

TStruct g_th;


bool    g_bThreadRun;

FuncCAN::FuncCAN()
{
}


FuncCAN::~FuncCAN()
{
}



XLstatus FuncCAN::CANInit()
{
    XLstatus        xlStatus = XL_ERROR;
    m_bInitDone = false;
    cm = g_th.cm;

    xlStatus = xlOpenDriver();

    if (xlStatus != XL_SUCCESS) {
       qDebug()<<("Error when opening driver!\n");
        return xlStatus;
    }

    // ---------------------------------------
    // Get/Set the application within VHWConf
    // ---------------------------------------
    xlStatus = canGetChannelMask();//xlgetapplconfig


    if ((xlStatus) || (m_xlChannelMask[CHAN01] == 0) || (m_xlChannelMask[CHAN02] == 0)) {
        qDebug()<<("Error when canGetChannelMask!");
        return XL_ERROR;
    }
    // ---------------------------------------
    // Open ONE port for both channels
    // ---------------------------------------

    xlStatus = canInit();
    if (xlStatus) {
        printf("caninit faild...\n");
        return xlStatus;


    }
    printf("out  caninit...\n");
    // ---------------------------------------
    // Create ONE thread for both channels
    // ---------------------------------------
    xlStatus = canCreateRxThread();
    if (xlStatus) return xlStatus;

    m_bInitDone = true;

    return xlStatus;
}

XLstatus FuncCAN::CANGoOnBus(unsigned long baudrate)
{
    XLstatus      xlStatus = XL_ERROR;
    char          tmp[100];

    xlStatus = xlCanSetChannelBitrate(m_xlPortHandle, m_xlChannelMask_both, baudrate);
    sprintf_s(tmp, sizeof(tmp), "SetBaudrate: %d, stat: %d", baudrate, xlStatus);

    xlStatus = xlActivateChannel(m_xlPortHandle, m_xlChannelMask_both, XL_BUS_TYPE_CAN, XL_ACTIVATE_RESET_CLOCK);
    sprintf_s(tmp, sizeof(tmp), "ActivateChannel, stat: %d", xlStatus);
    return xlStatus;
}

XLstatus FuncCAN::CANGoOffBus()
{
    XLstatus      xlStatus = XL_ERROR;
    char          tmp[100];

    xlStatus = xlDeactivateChannel(m_xlPortHandle, m_xlChannelMask_both);
    sprintf_s(tmp, sizeof(tmp), "DeactivateChannel, stat: %d", xlStatus);

    return xlStatus;
}

XLstatus FuncCAN::CANSend(XLevent xlEvent, int channel)
{
    XLstatus      xlStatus;
    char          tmp[100];
    unsigned int  messageCount = 1;

    xlStatus = xlCanTransmit(m_xlPortHandle, m_xlChannelMask[channel], &messageCount, &xlEvent);
    sprintf_s(tmp, sizeof(tmp), "Transmit, mc: %d, channel: %d, stat: %d", messageCount, channel, xlStatus);

    return xlStatus;
}

XLstatus FuncCAN::CANResetFilter()
{
    XLstatus      xlStatus;
    char          tmp[100];

    xlStatus = xlCanResetAcceptance(m_xlPortHandle, m_xlChannelMask_both, XL_CAN_STD);
    sprintf_s(tmp, sizeof(tmp), "CanResetAcceptance, stat: %d", xlStatus);

    return xlStatus;
}

XLstatus FuncCAN::CANSetFilter(unsigned long first_id, unsigned long last_id)
{
    XLstatus      xlStatus;
    char          tmp[100];

    // because there all filters open, we close all.
    xlStatus = xlCanSetChannelAcceptance(m_xlPortHandle, m_xlChannelMask_both, 0xFFF, 0xFFF, XL_CAN_STD);
    sprintf_s(tmp, sizeof(tmp), "CanSetChannelAcceptance, stat: %d", xlStatus);

    // and now we can set the acceptance filter range.
    xlStatus = xlCanAddAcceptanceRange(m_xlPortHandle, m_xlChannelMask_both, first_id, last_id);
    sprintf_s(tmp, sizeof(tmp), "CanAddAcceptanceRange, firstID: %d, lastID: %d, stat: %d", first_id, last_id, xlStatus);


    return xlStatus;
}

TStruct FuncCAN::getG_th()
{
    return g_th;
}

XLstatus FuncCAN::canGetChannelMask()
{
    XLstatus        xlStatus = XL_ERROR;
    char            tmp[100];

    // default values
    unsigned int  hwType = 0;
    unsigned int  hwIndex = 0;
    unsigned int  hwChannel = 0;
    unsigned int  appChannel = 0;
    unsigned int  busType = XL_BUS_TYPE_CAN;
    unsigned int  i;
    unsigned int  chan1Found = 0;
    unsigned int  chan2Found = 0;

    XLdriverConfig  xlDrvConfig;
    //check for hardware:
    xlStatus = xlGetDriverConfig(&xlDrvConfig);
    printf( "xlGetDriverConfig: dllVersion: %d; channelCount: %d\n", xlDrvConfig.dllVersion, xlDrvConfig.channelCount);
    if (xlStatus) return xlStatus;

    // we check only if there is an application registered or not.
    xlStatus = xlGetApplConfig("xlCANcontrol", CHAN01, &hwType, &hwIndex, &hwChannel, busType);//config by hardconfig
    //AfxMessageBox(xlDrvConfig.channel[0].hwType);
    // Set the params into registry (default values...!)
    if (xlStatus) {

        for (i = 0; i < xlDrvConfig.channelCount; i++) {

            //AfxMessageBox(xlDrvConfig.channel[i].hwType);

            printf("hwType: %d, bustype: %d, hwChannel: %d, cap: 0x%x",
                xlDrvConfig.channel[i].hwType,
                xlDrvConfig.channel[i].connectedBusType,
                xlDrvConfig.channel[i].hwChannel,
                xlDrvConfig.channel[i].channelBusCapabilities);

            // we search not the first CAN cabs
            if ((xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN) && (appChannel < 2)) {

                hwType = xlDrvConfig.channel[i].hwType;
                hwIndex = xlDrvConfig.channel[i].hwIndex;
                hwChannel = xlDrvConfig.channel[i].hwChannel;

                xlStatus = xlSetApplConfig( // Registration of Application with default settings
                    "xlCANcontrol",             // Application Name
                    appChannel,                 // Application channel 0 or 1
                    hwType,                     // hwType  (CANcardXL...)
                    hwIndex,                    // Index of hardware (slot) (0,1,...)
                    hwChannel,                  // Index of channel (connector) (0,1,...)
                    busType);                   // the application is for CAN.

                m_xlChannelMask[appChannel] = xlGetChannelMask(hwType, hwIndex, hwChannel);

                appChannel++;
            }

        }
    }
    // application is registered, get two CAN channels which are assigned
    else {

        // get the first channel (check if channel is assigned)
        m_xlChannelMask[CHAN01] = xlGetChannelMask(hwType, hwIndex, hwChannel);
        sprintf_s(tmp, sizeof(tmp), "Found CAN in VHWConf, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN01]);

        for (i = 0; i < xlDrvConfig.channelCount; i++) {

            if ((xlDrvConfig.channel[i].channelMask == m_xlChannelMask[CHAN01]) &&
                (xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN)) {
                chan1Found = 1;
                break;
            }
        }

        if (!chan1Found) {
            sprintf_s(tmp, sizeof(tmp), "No assigned CAN in VHWConf for channel 0, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN01]);
            return XL_ERROR;
        }


        // get the second channel
        xlStatus = xlGetApplConfig("xlCANcontrol", CHAN02, &hwType, &hwIndex, &hwChannel, busType);
        if (xlStatus) return xlStatus;

        m_xlChannelMask[CHAN02] = xlGetChannelMask(hwType, hwIndex, hwChannel);
        sprintf_s(tmp, sizeof(tmp), "Found CAN in VHWConf, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN02]);

        for (i = 0; i < xlDrvConfig.channelCount; i++) {

            if ((xlDrvConfig.channel[i].channelMask == m_xlChannelMask[CHAN02]) &&
                (xlDrvConfig.channel[i].channelBusCapabilities & XL_BUS_ACTIVE_CAP_CAN)) {
                chan2Found = 1;
                break;
            }
        }

        if (!chan2Found) {
            sprintf_s(tmp, sizeof(tmp), "No assigned CAN in VHWConf for channel 1, hWType: %d, CM: 0x%I64x", hwType, m_xlChannelMask[CHAN01]);
            return XL_ERROR;
        }

    }

    return xlStatus;
}

XLstatus FuncCAN::canInit()
{
    XLstatus         xlStatus = XL_ERROR;
    XLaccess         xlPermissionMask;

    // ---------------------------------------
    // Open ONE port for both channels
    // ---------------------------------------

    // calculate the channelMask for both channel
    m_xlChannelMask_both = m_xlChannelMask[CHAN01] + m_xlChannelMask[CHAN02];
    xlPermissionMask = m_xlChannelMask_both;

    xlStatus = xlOpenPort(&m_xlPortHandle, "xlCANcontrol", m_xlChannelMask_both, &xlPermissionMask, 256, XL_INTERFACE_VERSION, XL_BUS_TYPE_CAN);
    printf( "xlOpenPort: PortHandle: %d\n", m_xlPortHandle);

    if (m_xlPortHandle == XL_INVALID_PORTHANDLE) return XL_ERROR;

    if (xlStatus == XL_ERR_INVALID_ACCESS) return xlStatus;


    return xlStatus;
}

XLstatus FuncCAN::canCreateRxThread()
{
    XLstatus      xlStatus = XL_ERROR;
    DWORD         ThreadId = 0;
    char          tmp[100];

    if (m_xlPortHandle != XL_INVALID_PORTHANDLE) {

        // Send a event for each Msg!!!
        xlStatus = xlSetNotification(m_xlPortHandle, &m_hMsgEvent, 1);
        sprintf_s(tmp, sizeof(tmp), "SetNotification '%d', xlStatus: %d", m_hMsgEvent, xlStatus);

        // for the RxThread
        g_th.xlPortHandle = m_xlPortHandle;
        g_th.hMsgEvent = m_hMsgEvent;


    }
    return xlStatus;
}
