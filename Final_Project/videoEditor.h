#ifndef VIDEOEDITOR_H
#define VIDEOEDITOR_H

#include "qmessagebox.h"

using namespace std;

class videoEditor
{
public:
    virtual ~videoEditor();
    virtual void setWFIOk(QString);//set window title & icon & ok button
    void setMsgButtons();
    virtual void setShortcut();
    virtual void setToolTip();
    void msgTemp(QString);
    virtual void ffmpeg();
    bool command(QString);
    QString getName();
    bool ffprobe();
    bool checkTime(QString, int);
    bool checkSecTime();
    virtual bool fullInput();
protected:
    QMessageBox * msg = nullptr, * temp = nullptr;
    QPushButton * input = nullptr, * output = nullptr, * ok = nullptr, * Cancel = nullptr;
    QString fileName, outputFolder;
    bool fOk;
    int intVS,intVE; // int video start & end (Seconds)
    string data; //data = get command data


};

#endif // VIDEOEDITOR_H
