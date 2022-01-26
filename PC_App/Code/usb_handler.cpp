#include "usb_handler.h"

usb_handler::usb_handler()
{

}

/*****************************************************************
*   Function Name: usbhandler_getConnectedDevices
*   Description	 : This API detects all trhe USB devices connected to the PC and
*                  updates the list serialComPortList
*   Parameters   : None
*   Return Value : None
*   Comments     : NA
*****************************************************************/
void usbhandler_getConnectedDevices()
{
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    serialComPortList.clear();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        QString dbgStr = "Vendor ID: ";

       if(serialPortInfo.hasVendorIdentifier())
       {
          dbgStr+= serialPortInfo.vendorIdentifier();
       }
       else
       {
          dbgStr+= " - ";
       }
       dbgStr+= "  Product ID: ";
       if(serialPortInfo.hasProductIdentifier())
       {
          dbgStr+= serialPortInfo.hasProductIdentifier();
       }
       else
       {
          dbgStr+= " - ";
       }
       dbgStr+= " Name: " + serialPortInfo.portName();
       dbgStr+= " Description: "+serialPortInfo.description();
      qDebug()<<dbgStr;
      serialComPortList.push_back(serialPortInfo);
    }
}


/*****************************************************************
*   Function Name: usbhandler_connect2UsbDevice
*   Description	 : This API connects the App to the Comport passed as the parameter using which future serial communication is possible.
*   Parameters   : myComPort[in] : The comPort to which the connection needs to be established
*   Return Value : bool : True if USB device is connected. False if USB device is not connected.
*   Comments     : 115200 bps baudrate is chosen for serial communication
*****************************************************************/
bool usbhandler_connect2UsbDevice(QSerialPortInfo myComPort)
{
    QString deviceDescription;
    if(isSerialDeviceConnected == false)    //If USB Device is already connected then skip as multiple USB connection feature is not available
        {
            usbDevice.setPortName(myComPort.portName());
            deviceDescription = myComPort.description();
            qDebug() << "connecting to: "<<usbDevice.portName();

            if(usbDevice.open(QIODevice::ReadWrite))
            {
                //Now the serial port is open try to set configuration
                if(!usbDevice.setBaudRate(USB_CONNECTION_BAUDRATE))        //Depends on your boud-rate on the Device
                    qDebug()<<usbDevice.errorString();

                if(!usbDevice.setDataBits(QSerialPort::Data8))
                    qDebug()<<usbDevice.errorString();

                if(!usbDevice.setParity(QSerialPort::NoParity))
                    qDebug()<<usbDevice.errorString();

                if(!usbDevice.setStopBits(QSerialPort::OneStop))
                    qDebug()<<usbDevice.errorString();

                if(!usbDevice.setFlowControl(QSerialPort::NoFlowControl))
                    qDebug()<<usbDevice.errorString();

                //If any error was returned the serial il corrctly configured

                qDebug() << "Connection to: "<< usbDevice.portName() << " " << deviceDescription << " connected";
                isSerialDeviceConnected = true;
            }
            else
            {
                qDebug() << "Connection to: "<< usbDevice.portName() << " " << deviceDescription << " not connected";
                qDebug() <<"         Error: "<<usbDevice.errorString();
                isSerialDeviceConnected = false;
            }
        }
        else
        {
            qDebug() << "Can't connect, another device is connected";

        }
    return (isSerialDeviceConnected);
}

/*****************************************************************
*   Function Name: usbhandler_disconnect4mUsbDevice
*   Description	 : This API disconnects the PC App from the USB device connected.
*                  After this API is invoked, no serial communication is possible.
*   Parameters   :None
*   Return Value :None
*   Comments     :NA
*****************************************************************/
void usbhandler_disconnect4mUsbDevice()
{
    if(isSerialDeviceConnected)
    {
        usbDevice.close();
        isSerialDeviceConnected = false;
        qDebug() << "Connection to: "<< usbDevice.portName() << " closed.";
    }
    else
    {
       qDebug() << "Can't disconnect, no device is connected";
    }
}
