#ifndef LOGMANAGER_EXTERNAL_H
#define LOGMANAGER_EXTERNAL_H


#include <QFile>
#include <QTextStream>

/* Macro Definition Section */
#define TRANSACTION_LOG 0x01
#define ERROR_LOG 0x02

/* Function Declaration Section */
extern bool openLogFile(unsigned int LogFile);
extern bool closeLogFile(unsigned int LogFile);



#endif // LOGMANAGER_EXTERNAL_H
