#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>

/* Macro Definition Section */
#define TRANSACTION_LOG 0x01
#define ERROR_LOG 0x02


/* Variable Definition Section */
QString outputDir = QDir::currentPath() + "/Logs/";

QFile transactionLogFile(outputDir + "transactionlog.tlog");
QTextStream transactionlog(&transactionLogFile);

QFile errorLogFile(outputDir + "errorlog.err");
QTextStream errorlog(&errorLogFile);

bool isTransactionLogOpen;
bool isErrorLogOpen;


/* Function Prototype Definition Section */
bool openLogFile(unsigned int LogFile);
bool closeFile(unsigned int LogFile);

class LogManager
{
public:
    LogManager();
};

#endif // LOGMANAGER_H
