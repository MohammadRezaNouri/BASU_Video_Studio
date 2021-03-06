#include "changeResolution.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "qmessagebox.h"
#include <QInputDialog>
#include <iostream>
changeResolution::changeResolution()
{
    width = QInputDialog::getInt(nullptr, "Output width", "Width : ", QLineEdit::Normal, 1, 2147483647, 50, &fOk);
    if (!fOk) // Cancel button
    {
        return;
    }
    height = QInputDialog::getInt(nullptr, "Output height", "Height : ", QLineEdit::Normal, 1, 2147483647, 50, &fOk);
    if (!fOk) // Cancel button
    {
        return;
    }
    setWFIOk("Change video resolution"); // Call dad function
    setMsgButtons(); // Call dad function
    msg->setText("Please select the file and its storage location.");
    click:
    msg->exec();
    if(msg->clickedButton() == input) // Input Video
    {
        fileName = QFileDialog::getOpenFileName(nullptr, "Open Video | Open Music", "", "Video Files | Music Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)");
        goto click;
    }
    else if(msg->clickedButton() == output)
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

void changeResolution::ffmpeg()
{
    QString temp = "ffmpeg -i ";
    temp += fileName + " -y -s " + QString::number(width) + "x" + QString::number(height) + " -c:a copy " + outputFolder + "/Change_resolution_is_Basu_Video_Studio_" + getName(); // Do the work
    msgTemp("Please click the OK button and wait for the result page to appear.");
    if(command(temp))
    {
        msgTemp("Done");
    }
    else
    {
        command("rm " + outputFolder + "/Change_resolution_is_Basu_Video_Studio_" + getName()); // Delete the decorative file
        msgTemp("This is not possible!");
    }
}
