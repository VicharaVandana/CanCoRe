#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include "usb_handler_external.h"
#include "logmanager_external.h"

/* Macro Definition Section */
#define TIMESTMP QTime::currentTime().toString() + ": "

/* Variable Definition Section */


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ResetMe(void);

private slots:
    void on_chkCAN1Sta_clicked();

    void on_chkCAN1Sta_clicked(bool checked);

    void on_chkCAN2Sta_clicked(bool checked);

    void on_btnDetect_clicked();

    void on_btnConnectUSB_clicked();

    void on_btnDisconnectUSB_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
