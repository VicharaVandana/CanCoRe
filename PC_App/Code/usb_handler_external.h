#ifndef USB_HANDLER_EXTERNAL_H
#define USB_HANDLER_EXTERNAL_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <vector>

/* Variable Declaration Section */
extern std::vector<QSerialPortInfo> serialComPortList;
extern QSerialPort usbDevice;
extern bool isSerialDeviceConnected;


/* Function Declaration Section */
extern void usbhandler_getConnectedDevices(void);
extern bool usbhandler_connect2UsbDevice(QSerialPortInfo myComPort);
extern void usbhandler_disconnect4mUsbDevice();

#endif // USB_HANDLER_EXTERNAL_H
