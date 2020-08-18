#ifndef VIDEOEDITOR_H
#define VIDEOEDITOR_H

#include "qmessagebox.h"

class videoEditor
{
public:
    virtual ~videoEditor();
    void setWFIOk();//set window title & icon & ok button
    void setMsgButtons();
    void setShortcut();
    void setToolTip();
    virtual void ffmpeg(){};
protected:
    QMessageBox * msg = nullptr, * temp = nullptr;
    QPushButton * input = nullptr, * output = nullptr, * ok = nullptr, * Cancel = nullptr;
    QString fileName, outputFolder;
};

#endif // VIDEOEDITOR_H
