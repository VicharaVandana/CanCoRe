#include "logmanager.h"


LogManager::LogManager()
{

}

/*****************************************************************
*   Function Name: openLogFile
*   Description	 : This API creates and opens the requested log file in current location in a directoryt called Logs.
*   Parameters   :
*      1) LogFile :index of log file
*           0x01: Transaction log file: where all the CAN transactions are recored
*           0x02: Error Log file: where all the errors occured during the execution are recoreded
*   Return Value : bool: Log file opening status:
*                   true if log file was opened successfully.
*                   false if log file failed to open
*   Comments     : NA
*****************************************************************/
bool openLogFile(unsigned int LogFile)
{
    bool l_ret = false;
    switch(LogFile)
    {
        case(TRANSACTION_LOG):
            transactionLogFile.open(QIODevice::WriteOnly | QIODevice::Text);
            isTransactionLogOpen = true;
            l_ret = true;
            break;
        case(ERROR_LOG):
            errorLogFile.open(QIODevice::WriteOnly | QIODevice::Text);
            isErrorLogOpen = true;
            l_ret = true;
            break;
        default:
            qDebug() << "Requested Log file to open [openLogFile] doesnt exist.";
            l_ret = false;
        break;
    }
    return(l_ret);
}

/*****************************************************************
*   Function Name: closeLogFile
*   Description	 : This API closes the requested log file.
*   Parameters   :
*      1) LogFile :index of log file
*           0x01: Transaction log file: where all the CAN transactions are recored
*           0x02: Error Log file: where all the errors occured during the execution are recoreded
*   Return Value : bool: Log file opening status:
*                   true if log file was closed successfully.
*                   false if log file failed to close. it may be either due to
*                       no such log file index exist or
*                       the file is not open.
*   Comments     : NA
*****************************************************************/
bool closeLogFile(unsigned int LogFile)
{
    bool l_ret = false;
    switch(LogFile)
    {
        case(TRANSACTION_LOG):
            if(isTransactionLogOpen)
            {
               transactionLogFile.close();
               l_ret = true;
            }
            break;
        case(ERROR_LOG):
            if(isErrorLogOpen)
            {
               errorLogFile.close();
               l_ret = true;
            }
            break;
        default:
            qDebug() << "Requested Log file to close [closeFile] doesnt exist.";
            l_ret = false;
            break;
    }
    return(l_ret);
}
