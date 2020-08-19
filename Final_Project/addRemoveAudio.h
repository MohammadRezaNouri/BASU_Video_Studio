#ifndef ADDREMOVEAUDIO_H
#define ADDREMOVEAUDIO_H

#include "videoEditor.h"
#include "QFileDialog"

class addRemoveAudio : public videoEditor
{
public:
    addRemoveAudio();
    virtual ~addRemoveAudio(); // Destructor for dynameic member
    virtual void setWFIOk(QString); // Set window title & icon & ok button for one message
    virtual void setShortcut(); // Set shortcut for 3 buttons this class
    virtual void setToolTip(); // Set tool tip for 3 buttons this class
    void addFfmpeg(); // Add audio to video from ffmpeg
    void removeFfmpeg(); // Remove audio from video with ffmpeg
    virtual bool fullInput(); // check input audio is not empty
private:
    QMessageBox * one = nullptr; // The first message is to select Delete sound or add sound
    QPushButton * addAudio = nullptr, * rmAudio = nullptr, * inputA = nullptr; // Buttons from one mwssage box
    QString audio; // Start & end time and select video and input audio
};

#endif // ADDREMOVEAUDIO_H
