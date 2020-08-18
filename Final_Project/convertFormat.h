#ifndef CONVERTFORMAT_H
#define CONVERTFORMAT_H

#include "qmessagebox.h"

class convertFormat
{
public:
    convertFormat();
    ~convertFormat();
private:
    QMessageBox * msg = nullptr, * temp = nullptr;
    QPushButton * input = nullptr, * output = nullptr, * ok = nullptr, * Cancel = nullptr;
    QString format, fileName, outputFolder;
};

#endif // CONVERTFORMAT_H
