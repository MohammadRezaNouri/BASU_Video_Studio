#ifndef CONVERTFORMAT_H
#define CONVERTFORMAT_H

#include "qmessagebox.h"

class convertFormat
{
public:
    convertFormat();
    void setWFIOk();//set window title & icon & ok button
    void setMsgButtons();
private:
    QMessageBox * msg, * tempB;
    QPushButton * input, * output, * ok, * Cancel;
    QString format, fileName, outputFolder;
};

#endif // CONVERTFORMAT_H
