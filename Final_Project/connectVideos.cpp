#include "connectVideos.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <iostream>
#include <string>
#include <QFileDialog>
#include <fstream>

using namespace std;

connectVideos::connectVideos()
{
    setWFIOk("Connect several video files to each other");
    setMsgButtons();
    msg->setText("Please select videos in order of connection type.");
    click:
    msg->exec();
    if (msg->clickedButton() == input)
    {
        ls = QFileDialog::getOpenFileNames(nullptr, "Select videos", QDir::currentPath(), ("Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)"));
        goto click;
    }
    else if (msg->clickedButton() == output)
    {
        outputFolder = QFileDialog::getExistingDirectory(nullptr, ("Select Output Folder"), QDir::currentPath());
        goto click;
    }
    else if (msg->clickedButton() == ok)
    {
        if(fullInput())
        {
            ffmpeg();
        }
    }
}

void connectVideos::ffmpeg()
{
    msgTemp("Please click the OK button and wait for the result page to appear.");
    QString t1 = outputFolder + "/file.txt";
    ofstream file(t1.toStdString(), ios::out);
    if(!file)
    {
        msgTemp("There was a problem executing this and we were unable to generate the file needed to do so.");
        t1 = "rm " + outputFolder + "/file.txt";
        return;
    }
    QFileInfo nameTemp;
    for (int i = 0; i < ls.size(); i++)
    {
        nameTemp = ls[i];
        t1 = "file 'cp_" + nameTemp.fileName() + "'\n";
        file << t1.toStdString();
        t1 = "cp \"" + ls[i] + "\" " + outputFolder + "/\"cp_" + nameTemp.fileName() + "\"";
        if(!command(t1))
        {
            for(int j = 0; j < i; j++)
            {
                nameTemp = ls[j];
                t1 = "rm " + outputFolder + "/cp_" + nameTemp.fileName();
                command(t1);
            }
            t1 = "rm " + outputFolder + "/file.txt";
            command(t1);
            msgTemp("This is not possible!");
            return;
        }
    }
    file.close();
    t1 = "ffmpeg -y -f concat -i " + outputFolder + "/file.txt " + outputFolder + "/Connect_videos.mp4";
    if(!command(t1))
    {
        t1 = "rm " + outputFolder + "/file.txt";
        command(t1);
        for (int i = 0; i < ls.size(); i++)
        {
            nameTemp = ls[i];
            t1 = "rm " + outputFolder + "/cp_" + nameTemp.fileName();
            command(t1);
        }
        msgTemp("This is not possible!");
        return;
    }
    for (int i = 0; i < ls.size(); i++)
    {
        nameTemp = ls[i];
        t1 = "rm " + outputFolder + "/cp_" + nameTemp.fileName();
        command(t1);
    }
    t1 = "rm " + outputFolder + "/file.txt";
    command(t1);
    msgTemp("Done");
}

 bool connectVideos::fullInput()
 {
     if(ls.size() == 0 && outputFolder.size() == 0)
     {
         msgTemp("Videos and path not selected.");
         return false;
     }
     else if(outputFolder.size() == 0)
     {
         msgTemp("No route selected.");
         return false;
     }
     else if(ls.size() == 0)
     {
         msgTemp("No videos selected.");
         return false;
     }
     return true;
 }
