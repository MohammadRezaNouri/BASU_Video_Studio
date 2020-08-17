#include "addRemoveAudio.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "qmessagebox.h"
#include <QInputDialog>
#include <fstream>

using namespace std;

addRemoveAudio::addRemoveAudio()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QMessageBox * one = new QMessageBox(),  * temp = new QMessageBox(), * two = new QMessageBox();
    one->setWindowTitle("Add audio to video or remove audio from it");
    QPushButton * addAudio = new QPushButton(), * rmAudio, * ok = new QPushButton(), * Cancel = new QPushButton(),  * inputV = new QPushButton(), * output = new QPushButton();
    addAudio = one->addButton("Add audio in video", QMessageBox::ActionRole);
    addAudio->setShortcut(Qt::CTRL + Qt::Key_A);
    addAudio->setToolTip("Ctrl+A");
    rmAudio = new QPushButton();
    rmAudio = one->addButton("Remove audio in video", QMessageBox::ActionRole);
    rmAudio->setShortcut(Qt::CTRL + Qt::Key_R);
    rmAudio->setToolTip("Ctrl+R");
    Cancel = one->addButton("Cancel", QMessageBox::ActionRole);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    Cancel->setToolTip("Ctrl+Q");
    one->setFont(font);
    one->setIcon(QMessageBox::Icon::Information);
    one->setText("Please select : ");
    one->exec();
    QString sTime, eTime, video, outputFolder; // Start & end time and select video
    two->setFont(font);
    two->setIcon(QMessageBox::Icon::Information);
    two->setWindowTitle("Add audio to video or remove audio from it");
    string strVS, strVE; //string video start & end
    int intVS,intVE; // int video start & end (Seconds)
    temp->setFont(font);
    temp->setWindowTitle("Add audio to video or remove audio from it");
    temp->setIcon(QMessageBox::Icon::Critical);
    ok = temp->addButton("Ok", QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    bool fOk;
    inputV = two->addButton("Input video", QMessageBox::ActionRole);
    inputV->setShortcut(Qt::CTRL + Qt::Key_V);
    inputV->setToolTip("Ctrl+V");
    output = two->addButton("Output folder", QMessageBox::ActionRole);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    output->setToolTip("Ctrl+F");
    Cancel = two->addButton("Cancel", QMessageBox::ActionRole);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    Cancel->setToolTip("Ctrl+Q");
    ok = two->addButton("Ok", QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    two->setText("Please select the file and its storage location.");
    if (one->clickedButton() == addAudio)
    {
        sTime = QInputDialog::getText(nullptr, "Start time to add", "Start time : ", QLineEdit::Normal, "Example : 00:00:00",  &fOk);
        if (!fOk)
        {
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (sTime[0] == '-')
        {
            temp->setText("Start time is not negative.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (sTime.size() > 8)
        {
            temp->setText("Input is incorrect.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        strVS = sTime.toStdString();
        try
        {
            intVS = stoi(strVS.substr(0, 2)) * 3600 + stoi(strVS.substr(3, 2)) * 60 + stoi(strVS.substr(6, 2));
        }
        catch(...)
        {
            temp->setText("You entered the start date incorrectly.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (stoi(strVS.substr(3, 2)) > 59)
        {
            temp->setText("Wrong input format. (minute > 59)");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (stoi(strVS.substr(6, 2)) > 59)
        {
            temp->setText("Wrong input format. (seconds > 59)");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        eTime = QInputDialog::getText(nullptr, "End time to add", "End time : ", QLineEdit::Normal, "Example : 00:00:00", &fOk);
        if (!fOk)
        {
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (eTime[0] == '-')
        {
            temp->setText("End time is not negative.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (eTime.size() > 8)
        {
            temp->setText("Input is incorrect.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        strVE = eTime.toStdString();
        try
        {
            intVE = stoi(strVE.substr(0, 2)) * 3600 + stoi(strVE.substr(3, 2)) * 60 + stoi(strVE.substr(6, 2));
        }
        catch(...)
        {
            temp->setText("You entered the end date incorrectly.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (stoi(strVE.substr(3, 2)) > 59)
        {
            temp->setText("Wrong input format. (minute > 59)");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (stoi(strVE.substr(6, 2)) > 59)
        {
            temp->setText("Wrong input format. (seconds > 59)");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (intVS > intVE)
        {
            temp->setText("The end time must be greater than the start time.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        QPushButton * inputA = new QPushButton();
        inputA = two->addButton("Input audio", QMessageBox::ActionRole);
        inputA->setShortcut(Qt::CTRL + Qt::Key_M);
        inputA->setToolTip("Ctrl+M");
        QString audio;
        click1:
        two->exec();
        if(two->clickedButton() == inputV)
        {
            video = QFileDialog::getOpenFileName(nullptr, "Open Video", "", "Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)");
            goto click1;
        }
        else if(two->clickedButton() == inputA)
        {
            audio = QFileDialog::getOpenFileName(nullptr, "Open Music", "", "Music Files(*.3gp *.mp4 *.m4a *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.m4b *.m4p *.ogg *.oga *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wav *.wma *.webm *.wv *.8svx *.cda)");
            goto click1;
        }
        else if(two->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
            goto click1;
        }
        else if(two->clickedButton() == ok)
        {
            if(video.size() == 0 && outputFolder.size() == 0 && audio.size() == 0)
            {
                temp->setText("Files and path not selected.");
                temp->exec();
                delete temp;
                delete addAudio;
                delete rmAudio;
                delete ok;
                delete Cancel;
                delete inputV;
                delete output;
                delete inputA;
                return;
            }
            else if(outputFolder.size() == 0)
            {
                temp->setText("No route selected.");
                temp->exec();
                delete temp;
                delete addAudio;
                delete rmAudio;
                delete ok;
                delete Cancel;
                delete inputV;
                delete output;
                delete inputA;
                return;
            }
            else if(video.size() == 0)
            {
                temp->setText("No video selected.");
                temp->exec();
                delete temp;
                delete addAudio;
                delete rmAudio;
                delete ok;
                delete Cancel;
                delete inputV;
                delete output;
                delete inputA;
                return;
            }
            else if(audio.size() == 0)
            {
                temp->setText("No audio selected.");
                temp->exec();
                delete temp;
                delete addAudio;
                delete rmAudio;
                delete ok;
                delete Cancel;
                delete inputV;
                delete output;
                delete inputA;
                return;
            }
            else
            {
                QString tem = "ffprobe -i ", name;
                QFileInfo nameTemp(video);
                name = nameTemp.fileName();
                tem += video + " -show_entries format=duration -v quiet -of csv=""p=0""" + " 2>&1";
                QByteArray temp2 = tem.toLocal8Bit();
                const char * t2 = temp2.data();
                string data;
                FILE * stream;
                const int max_buffer = 256;
                char buffer[max_buffer];
                stream = popen(t2, "r");
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
                    delete temp;
                    delete addAudio;
                    delete rmAudio;
                    delete ok;
                    delete Cancel;
                    delete inputV;
                    delete output;
                    delete inputA;
                    return;
                }
                if (intVE > stoi(data))
                {
                    temp->setText("The end time is longer than the total time.");
                    temp->exec();
                    delete temp;
                    delete addAudio;
                    delete rmAudio;
                    delete ok;
                    delete Cancel;
                    delete inputV;
                    delete output;
                    delete inputA;
                    return;
                }
                if (strVS != "00:00:00")
                {
                    tem = "ffmpeg -y -itsoffset 00:00:00 -t " + sTime + " -i " + video + " -vn " + outputFolder + "/1.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "ffmpeg -y -ss 00:00:00 -t " + QString::number((intVE - intVS) / 3600) + ":" + QString::number(((intVE - intVS) % 3600) / 60) + ":" +QString::number(((intVE - intVS) % 3600) % 60) + " -i \"" + audio + "\" " + outputFolder + "/2.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "ffmpeg -y -ss " + eTime + " -i " + video + " -vn " + outputFolder + "/3.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "touch " + outputFolder + "/file.txt";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = outputFolder + "/file.txt";
                    ofstream file(tem.toStdString(), ios::out);
                    if(!file)
                    {
                        temp->setText("There was a problem executing this and we were unable to generate the file needed to do so.");
                        temp->exec();
                        delete temp;
                        delete addAudio;
                        delete rmAudio;
                        delete ok;
                        delete Cancel;
                        delete inputV;
                        delete output;
                        delete inputA;
                        return;
                    }
                    file << "file '1.mp3'\nfile '2.mp3'\nfile '3.mp3'";
                    file.close();
                    tem = "ffmpeg -y -f concat -safe 0 -i " + outputFolder + "/file.txt -c copy " + outputFolder + "/4.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    QFileInfo nameTemp(video);
                    name = nameTemp.fileName();
                    tem = "ffmpeg -y -i " + video + " -i " + outputFolder + "/4.mp3 -map 0:0 -map 1:0 -c:v copy -preset ultrafast -async 1 " + outputFolder + "/Add_audio_" + name;
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/4.mp3 " + outputFolder + "/file.txt";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    delete temp;
                    delete addAudio;
                    delete rmAudio;
                    delete ok;
                    delete Cancel;
                    delete inputV;
                    delete output;
                    delete inputA;
                    return;
                }
                else
                {
                    tem = "ffmpeg -y -ss 00:00:00 -t " + eTime + " -i \"" + audio + "\" " + outputFolder + "/1.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "ffmpeg -y -ss " + eTime + " -i " + video + " -vn " + outputFolder + "/2.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "touch " + outputFolder + "/file.txt";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = outputFolder + "/file.txt";
                    ofstream file(tem.toStdString(), ios::out);
                    if(!file)
                    {
                        temp->setText("There was a problem executing this and we were unable to generate the file needed to do so.");
                        temp->exec();
                        delete temp;
                        delete addAudio;
                        delete rmAudio;
                        delete ok;
                        delete Cancel;
                        delete inputV;
                        delete output;
                        delete inputA;
                        return;
                    }
                    file << "file '1.mp3'\nfile '2.mp3'";
                    file.close();
                    tem = "ffmpeg -y -f concat -safe 0 -i " + outputFolder + "/file.txt -c copy " + outputFolder + "/3.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    QFileInfo nameTemp(video);
                    name = nameTemp.fileName();
                    tem = "ffmpeg -y -i " + video + " -i " + outputFolder + "/3.mp3 -map 0:0 -map 1:0 -c:v copy -preset ultrafast -async 1 " + outputFolder + "/Add_audio_" + name;
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "rm " + outputFolder + "/1.mp3 " + outputFolder + "/2.mp3 " + outputFolder + "/3.mp3 " + outputFolder + "/file.txt";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    delete temp;
                    delete addAudio;
                    delete rmAudio;
                    delete ok;
                    delete Cancel;
                    delete inputV;
                    delete output;
                    delete inputA;
                    return;
                }
            }
        }
        else
        {
            delete temp;
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            delete inputV;
            delete output;
            delete inputA;
            return;
        }
    }
    else if (one->clickedButton() == rmAudio)
    {
        sTime = QInputDialog::getText(nullptr, "Start time to remove", "Start time : ", QLineEdit::Normal, "Example : 00:00:00",  &fOk);
        if (!fOk)
        {
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (sTime[0] == '-')
        {
            temp->setText("Start time is not negative.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (sTime.size() > 8)
        {
            temp->setText("Input is incorrect.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        strVS = sTime.toStdString();
        try
        {
            intVS = stoi(strVS.substr(0, 2)) * 3600 + stoi(strVS.substr(3, 2)) * 60 + stoi(strVS.substr(6, 2));
        }
        catch(...)
        {
            temp->setText("You entered the start date incorrectly.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (stoi(strVS.substr(3, 2)) > 59)
        {
            temp->setText("Wrong input format. (minute > 59)");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (stoi(strVS.substr(6, 2)) > 59)
        {
            temp->setText("Wrong input format. (seconds > 59)");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        eTime = QInputDialog::getText(nullptr, "End time to add", "End time : ", QLineEdit::Normal, "Example : 00:00:00", &fOk);
        if (!fOk)
        {
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (eTime[0] == '-')
        {
            temp->setText("End time is not negative.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (eTime.size() > 8)
        {
            temp->setText("Input is incorrect.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        strVE = eTime.toStdString();
        try
        {
            intVE = stoi(strVE.substr(0, 2)) * 3600 + stoi(strVE.substr(3, 2)) * 60 + stoi(strVE.substr(6, 2));
        }
        catch(...)
        {
            temp->setText("You entered the end date incorrectly.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (stoi(strVE.substr(3, 2)) > 59)
        {
            temp->setText("Wrong input format. (minute > 59)");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (stoi(strVE.substr(6, 2)) > 59)
        {
            temp->setText("Wrong input format. (seconds > 59)");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        if (intVS > intVE)
        {
            temp->setText("The end time must be greater than the start time.");
            temp->exec();
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            return;
        }
        click2:
        two->exec();
        if(two->clickedButton() == inputV)
        {
            video = QFileDialog::getOpenFileName(nullptr, "Open Video", "", "Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)");
            goto click2;
        }
        else if(two->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
            goto click2;
        }
        else if(two->clickedButton() == ok)
        {
            if(video.size() == 0 && outputFolder.size() == 0)
            {
                temp->setText("File and path not selected.");
                temp->exec();
                delete temp;
                delete addAudio;
                delete rmAudio;
                delete ok;
                delete Cancel;
                delete inputV;
                delete output;
                return;
            }
            else if(outputFolder.size() == 0)
            {
                temp->setText("No route selected.");
                temp->exec();
                delete temp;
                delete addAudio;
                delete rmAudio;
                delete ok;
                delete Cancel;
                delete inputV;
                delete output;
                return;
            }
            else if(video.size() == 0)
            {
                temp->setText("No video selected.");
                temp->exec();
                delete temp;
                delete addAudio;
                delete rmAudio;
                delete ok;
                delete Cancel;
                delete inputV;
                delete output;
                return;
            }
            else
            {
                QString tem = "ffprobe -i ", name;
                QFileInfo nameTemp(video);
                name = nameTemp.fileName();
                tem += video + " -show_entries format=duration -v quiet -of csv=""p=0""" + " 2>&1";
                QByteArray temp2 = tem.toLocal8Bit();
                const char * t2 = temp2.data();
                string data;
                FILE * stream;
                const int max_buffer = 256;
                char buffer[max_buffer];
                stream = popen(t2, "r");
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
                    delete temp;
                    delete addAudio;
                    delete rmAudio;
                    delete ok;
                    delete Cancel;
                    delete inputV;
                    delete output;
                    return;
                }
                if (intVE > stoi(data))
                {
                    temp->setText("The end time is longer than the total time.");
                    temp->exec();
                    delete temp;
                    delete addAudio;
                    delete rmAudio;
                    delete ok;
                    delete Cancel;
                    delete inputV;
                    delete output;
                    return;
                }
                tem = "ffmpeg -y -i " + video + " -af \"volume=enable='between(t," + QString::number(intVS) + "," + QString::number(intVE) + ")':volume=0\" -c:v copy " + outputFolder;
                nameTemp = video;
                name = nameTemp.fileName();
                tem += "/remove_audio_" + name;
                temp2 = tem.toLocal8Bit();
                t2 = temp2.data();
                system(t2);
                delete temp;
                delete addAudio;
                delete rmAudio;
                delete ok;
                delete Cancel;
                delete inputV;
                delete output;
                return;
            }
        }
        else
        {
            delete temp;
            delete addAudio;
            delete rmAudio;
            delete ok;
            delete Cancel;
            delete inputV;
            delete output;
            return;
        }
    }
}
