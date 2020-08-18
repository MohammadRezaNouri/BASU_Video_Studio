#ifndef CONVERTFORMAT_H
#define CONVERTFORMAT_H

#include "qmessagebox.h"
#include "videoEditor.h"

class convertFormat : public videoEditor
{
public:
    convertFormat();
    ~convertFormat();
    void setWFIOk();//set window title & icon & ok button
    void setMsgButtons();
    void setShortcut();
    void setToolTip();
    void ffmpeg();
private:
    QMessageBox * msg = nullptr, * temp = nullptr;
    QPushButton * input = nullptr, * output = nullptr, * ok = nullptr, * Cancel = nullptr;
    QString format, fileName, outputFolder;
};

#endif // CONVERTFORMAT_H
