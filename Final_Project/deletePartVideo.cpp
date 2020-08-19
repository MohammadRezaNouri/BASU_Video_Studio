#include "deletePartVideo.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <QInputDialog>
#include <QFileDialog>
#include <string>

using namespace std;

deletePartVideo::deletePartVideo()
{
    sTime = QInputDialog::getText(nullptr, "Start time to remove", "Start time : ", QLineEdit::Normal, "Example : 00:00:00",  &fOk);
    if (!fOk) // Cancel button
    {
        return;
    }
    setWFIOk("Delete parts of the video"); // Call dad function
    if(!checkTime(sTime, 0)) // Check true start inputs
    {
        return;
    }
    eTime = QInputDialog::getText(nullptr, "End time to remove", "End time : ", QLineEdit::Normal, "Example : 00:00:00", &fOk);
    if (!fOk) // Cancel button
    {
        return;
    }
    if(!checkTime(eTime, 1)) // Check true end inputs
    {
        return;
    }
    if (!checkSecTime()) // Check start time < end time
    {
        return;
    }
    setMsgButtons(); // Call dad function
    msg->setText("Please select : ");
    click:
    msg->exec();
    if(msg->clickedButton() == input) // input Video
    {
        fileName = QFileDialog::getOpenFileName(nullptr, "Open Video", "", "Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)");
        goto click;
    }
    else if(msg->clickedButton() == output)
    {
        outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
        goto click;
    }
    else if(msg->clickedButton() == ok)
    {
        if(!fullInput()) // check inputs is not empty
        {
            return;
        }
        if(ffprobe())
        {
            ffmpeg();
        }
    }
}

void deletePartVideo::ffmpeg()
{
    msgTemp("Please click the OK button and wait for the result page to appear.");
    QString t1 = "ffmpeg -y -i " + fileName + " -filter_complex \"[0:v]trim=start=0:end=" + QString::number(intVS) + ",setpts=PTS-STARTPTS[a]; [0:v]trim=start=" + QString::number(intVE) + ":end=" + QString::number(stoi(data)) + ",setpts=PTS-STARTPTS[b]; [0:a]atrim=start=0:end=" + QString::number(intVS) + ",asetpts=PTS-STARTPTS[c]; [0:a]atrim=start=" + QString::number(intVE) + ":end=" + QString::number(stoi(data)) + ",asetpts=PTS-STARTPTS[d]; [a][c][b][d]concat=n=2:v=1:a=1[e][f]\" -map '[e]' -map '[f]' -strict -2 " + outputFolder + "/Delete_part_video_" + getName();
    if(!command(t1))
    {
        msgTemp("This is not possible!");
        return;
    }
    msgTemp("Done");
}
