#include "addRemoveAudio.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "qmessagebox.h"
#include <QInputDialog>
#include <fstream>
#include <iostream>

addRemoveAudio::addRemoveAudio()
{
    setWFIOk("Add audio to video or remove audio from it");
    one->setText("Please select : ");
    one->exec();
    if (one->clickedButton() == addAudio)
    {
        sTime = QInputDialog::getText(nullptr, "Start time to add", "Start time : ", QLineEdit::Normal, "Example : 00:00:00",  &fOk);
        if (!fOk)
        {
            return;
        }
        if(!checkTime(sTime, 0))
        {
            return;
        }
        eTime = QInputDialog::getText(nullptr, "End time to add", "End time : ", QLineEdit::Normal, "Example : 00:00:00", &fOk);
        if (!fOk)
        {
            return;
        }
        if(!checkTime(eTime, 1))
        {
            return;
        }
        if(!checkSecTime())
        {
            return;
        }
        inputA = new QPushButton();
        inputA = msg->addButton("Input audio", QMessageBox::ActionRole);
        inputA->setShortcut(Qt::CTRL + Qt::Key_M);
        inputA->setToolTip("Ctrl+M");
        msg->setText("Please select the file and its storage location.");
        click1:
        msg->exec();
        if(msg->clickedButton() == input)
        {
            fileName = QFileDialog::getOpenFileName(nullptr, "Open Video", "", "Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)");
            goto click1;
        }
        else if(msg->clickedButton() == inputA)
        {
            audio = QFileDialog::getOpenFileName(nullptr, "Open Music", "", "Music Files(*.3gp *.mp4 *.m4a *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.m4b *.m4p *.ogg *.oga *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wav *.wma *.webm *.wv *.8svx *.cda)");
            goto click1;
        }
        else if(msg->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
            goto click1;
        }
        else if(msg->clickedButton() == ok)
        {
            if(fullInput())
            {
                if (ffprobe())
                {
                    addFfmpeg();
                }
            }
        }
    }
    else if (msg->clickedButton() == rmAudio)
    {
        sTime = QInputDialog::getText(nullptr, "Start time to remove", "Start time : ", QLineEdit::Normal, "Example : 00:00:00",  &fOk);
        if (!fOk)
        {
            return;
        }
        if(!checkTime(sTime, 0))
        {
            return;
        }
        eTime = QInputDialog::getText(nullptr, "End time to add", "End time : ", QLineEdit::Normal, "Example : 00:00:00", &fOk);
        if (!fOk)
        {
            return;
        }
        if(!checkTime(eTime, 1))
        {
            return;
        }
        if(!checkSecTime())
        {
            return;
        }
        click2:
        msg->exec();
        if(msg->clickedButton() == input)
        {
            fileName = QFileDialog::getOpenFileName(nullptr, "Open Video", "", "Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)");
            goto click2;
        }
        else if(msg->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
            goto click2;
        }
        else if(msg->clickedButton() == ok)
        {
            if(fullInput())
            {
                if (ffprobe())
                {
                    removeFfmpeg();
                }
            }
        }
    }
}

void addRemoveAudio::setWFIOk(QString title)
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    one = new QMessageBox();
    one->setFont(font);
    one->setIcon(QMessageBox::Icon::Information);
    one->setWindowTitle(title);
    addAudio = new QPushButton();
    addAudio = one->addButton("Add audio in video", QMessageBox::ActionRole);
    rmAudio = new QPushButton();
    rmAudio = one->addButton("Remove audio in video", QMessageBox::ActionRole);
    videoEditor::setWFIOk(title);
    videoEditor::setMsgButtons();
    Cancel = one->addButton("Cancel", QMessageBox::ActionRole);
    setShortcut();
    setToolTip();
}

void addRemoveAudio::setShortcut()
{
    addAudio->setShortcut(Qt::CTRL + Qt::Key_A);
    rmAudio->setShortcut(Qt::CTRL + Qt::Key_R);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
}

void addRemoveAudio::setToolTip()
{
    addAudio->setToolTip("Ctrl+A");
    rmAudio->setToolTip("Ctrl+R");
    Cancel->setToolTip("Ctrl+Q");
}

addRemoveAudio::~addRemoveAudio()
{
    if(addAudio != nullptr)
    {
        delete addAudio;
    }
    if(rmAudio != nullptr)
    {
        delete rmAudio;
    }
    if(inputA != nullptr)
    {
        delete inputA;
    }
    if(one != nullptr)
    {
        //delete one;
    }
}

void addRemoveAudio::addFfmpeg()
{
    QString t1;
    msgTemp("Please click the OK button and wait for the result page to appear.");
    if (sTime != "00:00:00")
    {
        t1 = "ffmpeg -y -itsoffset 00:00:00 -t " + sTime + " -i " + fileName + " -vn " + outputFolder + "/1.mp3";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3";
            command(t1);
            return;
        }
        t1 = "ffmpeg -y -ss 00:00:00 -t " + QString::number((intVE - intVS) / 3600) + ":" + QString::number(((intVE - intVS) % 3600) / 60) + ":" +QString::number(((intVE - intVS) % 3600) % 60) + " -i \"" + audio + "\" " + outputFolder + "/2.mp3";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3";
            command(t1);
            return;
        }
        t1 = "ffmpeg -y -ss " + eTime + " -i " + fileName + " -vn " + outputFolder + "/3.mp3";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3";
            command(t1);
            return;
        }
        t1 = "touch " + outputFolder + "/file.txt";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            return;
        }
        t1 = outputFolder + "/file.txt";
        ofstream file(t1.toStdString(), ios::out);
        if(!file)
        {
            msgTemp("There was a problem executing this and we were unable to generate the file needed to do so.");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/file.txt";
            command(t1);
            return;
        }
        file << "file '1.mp3'\nfile '2.mp3'\nfile '3.mp3'";
        file.close();
        t1 = "ffmpeg -y -f concat -safe 0 -i " + outputFolder + "/file.txt -c copy " + outputFolder + "/4.mp3";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/4.mp3 " + outputFolder + "/file.txt";
            command(t1);
            return;
        }
        t1 = "ffmpeg -y -i " + fileName + " -i " + outputFolder + "/4.mp3 -map 0:0 -map 1:0 -c:v copy -preset ultrafast -async 1 " + outputFolder + "/Add_audio_" + getName();
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/4.mp3 " + outputFolder + "/file.txt";
            command(t1);
            return;
        }
        t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/4.mp3 " + outputFolder + "/file.txt";
        command(t1);
    }
    else
    {
        t1 = "ffmpeg -y -ss 00:00:00 -t " + eTime + " -i \"" + audio + "\" " + outputFolder + "/1.mp3";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3";
            command(t1);
            return;
        }
        t1 = "ffmpeg -y -ss " + eTime + " -i " + fileName + " -vn " + outputFolder + "/2.mp3";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3";
            command(t1);
            return;
        }
        t1 = "touch " + outputFolder + "/file.txt";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/file.txt";
            command(t1);
            return;
        }
        t1 = outputFolder + "/file.txt";
        ofstream file(t1.toStdString(), ios::out);
        if(!file)
        {
            msgTemp("There was a problem executing this and we were unable to generate the file needed to do so.");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/file.txt";
            command(t1);
            return;
        }
        file << "file '1.mp3'\nfile '2.mp3'";
        file.close();
        t1 = "ffmpeg -y -f concat -safe 0 -i " + outputFolder + "/file.txt -c copy " + outputFolder + "/3.mp3";
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/file.txt";
            command(t1);
            return;
        }
        t1 = "ffmpeg -y -i " + fileName + " -i " + outputFolder + "/3.mp3 -map 0:0 -map 1:0 -c:v copy -preset ultrafast -async 1 " + outputFolder + "/Add_audio_" + getName();
        if(!command(t1))
        {
            msgTemp("This is not possible!");
            t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/file.txt";
            command(t1);
            return;
        }
        t1 = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/file.txt";
        msgTemp("This is not possible!");
        msgTemp("Done");
    }
}

void addRemoveAudio::removeFfmpeg()
{
    QString t1 = "ffmpeg -y -i " + fileName + " -af \"volume=enable='between(t," + QString::number(intVS) + "," + QString::number(intVE) + ")':volume=0\" -c:v copy " + outputFolder;
    t1 += "/remove_audio_" + getName();
    msgTemp("Please click the OK button and wait for the result page to appear.");
    if(command(t1))
    {
        msgTemp("Done");
    }
    else
    {
        msgTemp("This is not possible!");
    }
}

bool addRemoveAudio::fullInput()
{
    if(fileName.size() == 0 && outputFolder.size() == 0 && audio.size() == 0)
    {
        msgTemp("Files and path not selected.");
        return false;
    }
    return videoEditor::fullInput();
}
