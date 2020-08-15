#include "deletePartVideo.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <QInputDialog>
#include <QFileDialog>
#include <string>

using namespace std;

deletePartVideo::deletePartVideo()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    bool fOk;
    QString sTime = QInputDialog::getText(nullptr, "Start time to add", "Start time : ", QLineEdit::Normal, "Example : 00:00:00",  &fOk);
    if (!fOk)
    {
        return;
    }
    QMessageBox * temp = new QMessageBox();
    temp->setIcon(QMessageBox::Icon::Critical);
    temp->setWindowTitle("Delete parts of the video");
    temp->setFont(font);
    if (sTime[0] == '-')
    {
        temp->setText("Start time is not negative.");
        temp->exec();
        delete temp;
        return;
    }
    if (sTime.size() > 8)
    {
        temp->setText("Input is incorrect.");
        temp->exec();
        delete temp;
        return;
    }
    string strVS = sTime.toStdString();
    int intVS;
    try
    {
        intVS = stoi(strVS.substr(0, 2)) * 3600 + stoi(strVS.substr(3, 2)) * 60 + stoi(strVS.substr(6, 2));
    }
    catch(...)
    {
        temp->setText("You entered the start date incorrectly.");
        temp->exec();
        delete temp;
        return;
    }
    if (stoi(strVS.substr(3, 2)) > 59)
    {
        temp->setText("Wrong input format. (minute > 59)");
        temp->exec();
        delete temp;
        return;
    }
    if (stoi(strVS.substr(6, 2)) > 59)
    {
        temp->setText("Wrong input format. (seconds > 59)");
        temp->exec();
        delete temp;
        return;
    }
    QString eTime = QInputDialog::getText(nullptr, "End time to add", "End time : ", QLineEdit::Normal, "Example : 00:00:00", &fOk);
    if (!fOk)
    {
        delete temp;
        return;
    }
    if (eTime[0] == '-')
    {
        temp->setText("End time is not negative.");
        temp->exec();
        delete temp;
        return;
    }
    if (eTime.size() > 8)
    {
        temp->setText("Input is incorrect.");
        temp->exec();
        delete temp;
        return;
    }
    string strVE = eTime.toStdString();
    int intVE;
    try
    {
        intVE = stoi(strVE.substr(0, 2)) * 3600 + stoi(strVE.substr(3, 2)) * 60 + stoi(strVE.substr(6, 2));
    }
    catch(...)
    {
        temp->setText("You entered the end date incorrectly.");
        temp->exec();
        delete temp;
        return;
    }
    if (stoi(strVE.substr(3, 2)) > 59)
    {
        temp->setText("Wrong input format. (minute > 59)");
        temp->exec();
        delete temp;
        return;
    }
    if (stoi(strVE.substr(6, 2)) > 59)
    {
        temp->setText("Wrong input format. (seconds > 59)");
        temp->exec();
        delete temp;
        return;
    }
    if (intVS > intVE)
    {
        temp->setText("The end time must be greater than the start time.");
        temp->exec();
        delete temp;
        return;
    }
    QMessageBox * msg = new QMessageBox();
    msg->setIcon(QMessageBox::Icon::Information);
    msg->setFont(font);
    msg->setWindowTitle("Delete parts of the video");
    msg->setText("Please select : ");
    QPushButton * inputV = new QPushButton(), * output = new QPushButton(), * ok = new QPushButton(), * cancel = new QPushButton();
    inputV = msg->addButton("Input Video", QMessageBox::ActionRole);
    inputV->setShortcut(Qt::CTRL + Qt::Key_V);
    inputV->setToolTip("Ctrl+V");
    output = msg->addButton("Output folder", QMessageBox::ActionRole);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    output->setToolTip("Ctrl+F");
    cancel = msg->addButton("Cancel", QMessageBox::ActionRole);
    cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    cancel->setToolTip("Ctrl+Q");
    ok = msg->addButton("Ok", QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    QString video, outputFolder;
    click:
    msg->exec();
    if(msg->clickedButton() == inputV)
    {
        video = QFileDialog::getOpenFileName(nullptr, "Open Video", "", "Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)");
        goto click;
    }
    else if(msg->clickedButton() == output)
    {
        outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
        goto click;
    }
    else if(msg->clickedButton() == ok)
    {
        if(video.size() == 0 && outputFolder.size() == 0)
        {
            temp->setText("Files and path not selected.");
            temp->exec();
            delete msg;
            delete temp;
            delete ok;
            delete cancel;
            delete inputV;
            delete output;
            return;
        }
        else if(outputFolder.size() == 0)
        {
            temp->setText("No route selected.");
            temp->exec();
            delete msg;
            delete temp;
            delete ok;
            delete cancel;
            delete inputV;
            delete output;
            return;
        }
        else if(video.size() == 0)
        {
            temp->setText("No video selected.");
            temp->exec();
            delete msg;
            delete temp;
            delete ok;
            delete cancel;
            delete inputV;
            delete output;
            return;
        }
        QString t1 = "ffprobe -i ";
        t1 += video + " -show_entries format=duration -v quiet -of csv=p=0 2>&1";
        QByteArray t2 = t1.toLocal8Bit();
        const char * t3 = t2.data();
        string data;
        FILE * stream;
        const int max_buffer = 256;
        char buffer[max_buffer];
        stream = popen(t3, "r");
        if (stream)
        {
            while (!feof(stream))
                if (fgets(buffer, max_buffer, stream) != nullptr) data.append(buffer);
            pclose(stream);
        }

        if (intVS > stoi(data))
        {
            temp->setText("The initial time is longer than the total time.");
            temp->exec();
            delete msg;
            delete temp;
            delete ok;
            delete cancel;
            delete inputV;
            delete output;
            return;
        }
        if (intVE > stoi(data))
        {
            temp->setText("The end time is longer than the total time.");
            temp->exec();
            delete msg;
            delete temp;
            delete ok;
            delete cancel;
            delete inputV;
            delete output;
            return;
        }
        QFileInfo nameTemp(video);
        t1 = "ffmpeg -y -i " + video + " -filter_complex \"[0:v]trim=start=0:end=" + QString::number(intVS) + ",setpts=PTS-STARTPTS[a]; [0:v]trim=start=" + QString::number(intVE) + ":end=" + QString::number(stoi(data)) + ",setpts=PTS-STARTPTS[b]; [0:a]atrim=start=0:end=" + QString::number(intVS) + ",asetpts=PTS-STARTPTS[c]; [0:a]atrim=start=" + QString::number(intVE) + ":end=" + QString::number(stoi(data)) + ",asetpts=PTS-STARTPTS[d]; [a][c][b][d]concat=n=2:v=1:a=1[e][f]\" -map '[e]' -map '[f]' -strict -2 " +outputFolder + "/Deletr_part_video_" + nameTemp.fileName();
        t2 = t1.toLocal8Bit();
        t3 = t2.data();
        system(t3);
        delete msg;
        delete temp;
        delete ok;
        delete cancel;
        delete inputV;
        delete output;
        return;
    }
}
