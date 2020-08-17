#ifndef CONVERTFORMAT_H
#define CONVERTFORMAT_H

#include "qmessagebox.h"

class convertFormat
{
public:
    convertFormat();
    ~convertFormat();
private:
    QMessageBox * msg, * tempB;
    QPushButton * input, * output, * ok, * Cancel;
    QString format;
};

#endif // CONVERTFORMAT_H
