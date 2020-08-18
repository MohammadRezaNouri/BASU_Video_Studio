#ifndef VIDEOEDITOR_H
#define VIDEOEDITOR_H

#include "qmessagebox.h"

class videoEditor
{
public:
    videoEditor();
protected:
    QMessageBox * msg = nullptr, * temp = nullptr;
    QPushButton * input = nullptr, * output = nullptr, * ok = nullptr, * Cancel = nullptr;
    QString fileName, outputFolder;
};

#endif // VIDEOEDITOR_H
