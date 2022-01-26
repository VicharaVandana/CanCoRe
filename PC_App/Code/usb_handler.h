#ifndef USB_HANDLER_H
#define USB_HANDLER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <vector>

#define USB_CONNECTION_BAUDRATE QSerialPort::Baud115200



class usb_handler
{
public:
    usb_handler();
};

/* Variable Definition Section */
std::vector<QSerialPortInfo> serialComPortList;
QSerialPort usbDevice;
bool isSerialDeviceConnected;

/* Function Prototype Definition Section */
void usbhandler_getConnectedDevices(void);
bool usbhandler_connect2UsbDevice(QSerialPortInfo myComPort);

#endif // USB_HANDLER_H
