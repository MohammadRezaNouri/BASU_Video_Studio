#include "reduceVolume.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include "qmessagebox.h"
#include <QFileDialog>
#include <iostream>

using namespace std;

reduceVolume::reduceVolume()
{
    crf = QInputDialog::getInt(nullptr, "Change the volume", "Number close to 51 = less volume\nNumber close to 0 = more volume", QLineEdit::Normal, 0, 51, 5, &fOk);
    if (!fOk) // Cancel button
    {
        return;
    }
    setWFIOk("Reduce video volume"); // Call dad function
    setMsgButtons(); // Call dad function
    msg->setText("Please select the video and its storage location.");
    click:
    msg->exec();
    if(msg->clickedButton() == input) // input Video
    {
        fileName = QFileDialog::getOpenFileName(nullptr, "Open Video", "", "Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)");
        goto click;
    }
    if(msg->clickedButton() == output)
    {
        outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
        goto click;
    }
    else if(msg->clickedButton() == ok)
    {
        if(fullInput()) // check input is not empty
        {
            ffmpeg();
        }
    }
}

void reduceVolume::ffmpeg()
{
    msgTemp("Please click the OK button and wait for the result page to appear.");
    QString t1 = "ffmpeg -y -i " + fileName + " -crf " + QString::number(crf) + " \"" + outputFolder + "/Reduce_volume_" + getName() + "\"";
    if(command(t1))
    {
        msgTemp("Done");
        return;
    }
    msgTemp("This is not possible!");
}
