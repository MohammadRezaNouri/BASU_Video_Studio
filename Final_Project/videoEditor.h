#ifndef VIDEOEDITOR_H
#define VIDEOEDITOR_H

#include "qmessagebox.h"

using namespace std;

class videoEditor
{
public:
    virtual ~videoEditor();
    virtual void setWFIOk(QString);//set window title & icon & ok button
    void setMsgButtons(); // Set Message buttond (input video & outpu Folder & ok)
    virtual void setShortcut(); // set buttons shortcut
    virtual void setToolTip(); // set buttons Tool  Tip
    void msgTemp(QString); // Show errors
    virtual void ffmpeg();//Main tool :)
    bool command(QString); //Send to command line and get results
    QString getName(); // Get video name
    bool ffprobe(); // Get Video total time & check Check with inputs
    bool checkTime(QString, int); // Check Input incorrect
    bool checkSecTime(); // Check start time < end time
    virtual bool fullInput(); // Error for empty inputs
protected:
    QMessageBox * msg = nullptr, * temp = nullptr; // msg = main message cox, temp = temp message box
    QPushButton * input = nullptr, * output = nullptr, * ok = nullptr; // input = input file & output = output Folder
    QString fileName, outputFolder, sTime, eTime;// start & end time
    bool fOk; // For cancel
    int intVS,intVE; // int video start & end (Seconds)
    string data; //data = get command data


};

#endif // VIDEOEDITOR_H
