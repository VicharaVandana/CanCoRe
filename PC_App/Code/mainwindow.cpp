#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Initially reset all the status and fields */
    this->ResetMe();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*****************************************************************
*   Function Name: MainWindow->ResetMe
*   Description	 : Resets all the fields of the mainwindow (Settings) GUI.
*   Parameters   : None
*   Return Value : None
*   Comments     : NA
*****************************************************************/
void MainWindow::ResetMe(void)
{
    /* Reset the USB Settings */
    ui->btnDisconnectUSB->click();  //Disconnect the USB
    ui->lblUSBStatus->setText("<font color='red'>NOT CONNECTED</font>");   //Make the USB connection status as Not connected
    ui->btnDetect->click(); //Detect the current connected USB devices

    /* Reset the Log Settings */
    ui->txtLog->clear();    //Clear the log window

    /* Reset the CAN Settings */
    ui->chkCAN1Sta->setChecked(false);  //Clear the CAN1 enable checkbox
    ui->chkCAN2Sta->setChecked(false);  //Clear the CAN2 enable checkbox
    ui->cmbCAN1Baudrate->hide();        //Hide CAN1 controller baudrate as CAN1 is not enabled
    ui->cmbCAN2Baudrate->hide();        //Hide CAN2 controller baudrate as CAN2 is not enabled

    /* Populate the baudrate comboboxes */
    ui->cmbCAN1Baudrate->addItem("NOT SELECTED");
    ui->cmbCAN1Baudrate->addItem("125 KBPS");
    ui->cmbCAN1Baudrate->addItem("250 KBPS");
    ui->cmbCAN1Baudrate->addItem("500 KBPS");
    ui->cmbCAN1Baudrate->addItem("1000 KBPS");

    ui->cmbCAN2Baudrate->addItem("NOT SELECTED");
    ui->cmbCAN2Baudrate->addItem("125 KBPS");
    ui->cmbCAN2Baudrate->addItem("250 KBPS");
    ui->cmbCAN2Baudrate->addItem("500 KBPS");
    ui->cmbCAN2Baudrate->addItem("1000 KBPS");
}

void MainWindow::on_chkCAN1Sta_clicked()
{


}

void MainWindow::on_chkCAN1Sta_clicked(bool checked)
{
    /* When CAN1 Controller is enabled
       Show the Baudrate Option Else Hide it*/
    if (checked)
    {
        ui->cmbCAN1Baudrate->show();
    }
    else
    {
        ui->cmbCAN1Baudrate->hide();
    }
}

void MainWindow::on_chkCAN2Sta_clicked(bool checked)
{
    /* When CAN2 Controller is enabled
       Show the Baudrate Option Else Hide it*/
    if (checked)
    {
        ui->cmbCAN2Baudrate->show();
    }
    else
    {
        ui->cmbCAN2Baudrate->hide();
    }
}

void MainWindow::on_btnDetect_clicked()
{
    /* Gets the connected USB devices and populates the combobox with the device list */
    usbhandler_getConnectedDevices();
    ui->cmbSerialPort->clear();
    for (auto usb = serialComPortList.begin(); usb != serialComPortList.end(); ++usb)
    {
        ui->cmbSerialPort->addItem(usb->portName() +" "+usb->description());
    }
}

void MainWindow::on_btnConnectUSB_clicked()
{
    QString logMsg;
    bool isUsbConnected = isSerialDeviceConnected;

    if(usbhandler_connect2UsbDevice(serialComPortList[ui->cmbSerialPort->currentIndex()]))
    {
        if(!isUsbConnected)    //Only if there is no other USB connection present
        {
            ui->lblUSBStatus->setText("<font color='green'>CONNECTED</font>");  //Set the connection status
            logMsg = TIMESTMP + "Connected to " + usbDevice.portName() + ".";
            ui->txtLog->append(logMsg);

            //Create transaction log and error log files
            (void)openLogFile(TRANSACTION_LOG);
            (void)openLogFile(ERROR_LOG);
        }
        else
        {
            logMsg = TIMESTMP + "Already connected to " + usbDevice.portName() + ". Multiple connections not possible.";
            ui->txtLog->append(logMsg);
        }

    }
    else
    {
        ui->lblUSBStatus->setText("<font color='red'>NOT CONNECTED</font>");
        logMsg = TIMESTMP + "Error: " + usbDevice.errorString() + ".";
        ui->txtLog->append(logMsg);
    }
}

void MainWindow::on_btnDisconnectUSB_clicked()
{
    QString logMsg;

    if(isSerialDeviceConnected)    //Only if there is a USB connection present
    {
        usbhandler_disconnect4mUsbDevice(); //Terminate the USB connection.

        ui->lblUSBStatus->setText("<font color='red'>DISCONNECTED</font>");

        logMsg = TIMESTMP + "Disconnected from " + usbDevice.portName() + ".";
        ui->txtLog->append(logMsg);

        //Close the transaction and error log files as the usb connection is terminated now.
        (void)closeLogFile(TRANSACTION_LOG);
        (void)closeLogFile(ERROR_LOG);
    }

    else
    {
        logMsg = TIMESTMP + "No Device is connected. Connect a device before disconnect.";
        ui->txtLog->append(logMsg);
    }
}
