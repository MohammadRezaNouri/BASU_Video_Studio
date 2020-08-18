#ifndef ADDREMOVEAUDIO_H
#define ADDREMOVEAUDIO_H

#include "videoEditor.h"

class addRemoveAudio : public videoEditor
{
public:
    addRemoveAudio();
    virtual ~addRemoveAudio();
    virtual void setWFIOk(QString);//set window title & icon & ok button
    virtual void setShortcut();
    virtual void setToolTip();
    void addFfmpeg();
    void removeFfmpeg();
    virtual bool fullInput();
private:
    QMessageBox * one = nullptr;
    QPushButton * addAudio = nullptr, * rmAudio = nullptr, * inputA = nullptr;
    QString audio; // Start & end time and select video and input audio
};

#endif // ADDREMOVEAUDIO_H
