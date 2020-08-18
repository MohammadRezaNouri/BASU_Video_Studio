#include "changeResolution.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "qmessagebox.h"
#include <QInputDialog>

changeResolution::changeResolution()
{
    width = QInputDialog::getInt(nullptr, "Output width", "Width : ", QLineEdit::Normal, 1, 2147483647, 50, &fOk);
    if (!fOk)
    {
        return;
    }
    height = QInputDialog::getInt(nullptr, "Output height", "Height : ", QLineEdit::Normal, 1, 2147483647, 50, &fOk);
    if (!fOk)
    {
        return;
    }
    setWFIOk();
    setMsgButtons();
    msg->setText("Please select the file and its storage location.");
    click:
    msg->exec();
    if(msg->clickedButton() == input)
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
        if(fileName.size() == 0 && outputFolder.size() == 0)
        {
            msgNotFilePath();
        }
        else if(outputFolder.size() == 0)
        {
            msgNotPath();
        }
        else if(fileName.size() == 0)
        {
            msgNotFile();
        }
        else
        {
            ffmpeg();
        }
    }
}

void changeResolution::ffmpeg()
{
    QString temp = "ffmpeg -i ";
    temp += fileName + " -y -s " + QString::number(width) + "x" + QString::number(height) + " -c:a copy " + outputFolder + "/Change_resolution_is_Basu_Video_Studio_" + getName();
    command(temp);
}
