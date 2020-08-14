#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "qmessagebox.h"
#include <QInputDialog>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BASU Video Studio");
    QResizeEvent * evt;
    resizeEvent(evt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd("../background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QMainWindow::resizeEvent(evt);
}

void MainWindow::on_convertFormat_clicked()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QString formats = "*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)";
    QMessageBox * msg = new QMessageBox();
    msg->setWindowTitle("Convert video and audio formats");
    QMessageBox * tempB = new QMessageBox();
    tempB->setWindowTitle("Convert video and audio formats");
    msg->setFont(font);
    tempB->setIcon(QMessageBox::Icon::Critical);
    tempB->setFont(font);
    bool fOk;
    QString format = QInputDialog::getText(this, tr("Output format"), tr("Format : "), QLineEdit::Normal, "Example: mp3", &fOk);
    if (!fOk)
    {
        delete msg;
        delete tempB;
        return;
    }
    QPushButton * input = new QPushButton(), * output = new QPushButton(), * ok = new QPushButton(), * Cancel = new QPushButton();
    ok = tempB->addButton((tr("Ok")), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    QString fileName, outputFolder;
    if (formats.contains(format) == true)
    {
        msg->setIcon(QMessageBox::Icon::Information);
        input = msg->addButton((tr("Input file")), QMessageBox::ActionRole);
        input->setShortcut(Qt::CTRL + Qt::Key_O);
        input->setToolTip("Ctrl+O");
        output = msg->addButton((tr("Output folder")), QMessageBox::ActionRole);
        output->setShortcut(Qt::CTRL + Qt::Key_F);
        output->setToolTip("Ctrl+F");
        ok = msg->addButton((tr("Ok")), QMessageBox::ActionRole);
        ok->setShortcut(Qt::CTRL + Qt::Key_K);
        ok->setToolTip("Ctrl+K");
        Cancel = msg->addButton((tr("Cancel")), QMessageBox::ActionRole);
        Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
        Cancel->setToolTip("Ctrl+Q");
        msg->setText("Please select the file and its storage location.");
        click:
        msg->exec();
        if(msg->clickedButton() == input)
        {
            fileName = QFileDialog::getOpenFileName(this, tr("Open Video | Open Music"), "", tr("Video Files | Music Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)"));
            goto click;
        }
        else if(msg->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());
            goto click;
        }
        else if(msg->clickedButton() == ok)
        {
            if(fileName.size() == 0 && outputFolder.size() == 0)
            {
                tempB->setText("File and path not selected.");
                tempB->exec();
            }
            else if(outputFolder.size() == 0)
            {
                tempB->setText("No route selected.");
                tempB->exec();
            }
            else if(fileName.size() == 0)
            {
                tempB->setText("No file selected.");
                tempB->exec();
            }
            else
            {
                QString temp = "ffmpeg -i ", name;
                if(format == "gif")
                {
                    QFileInfo nameTemp(fileName);
                    name = nameTemp.fileName();
                    temp += fileName + " -y -vf scale=500:-1 -t 10 -r 10 " + outputFolder + "/" + name +"_Convert_format_is_Basu_Video_Studio." + format;
                    QByteArray temp2 = temp.toLocal8Bit();
                    const char * t2 = temp2.data();
                    system(t2);
                    tempB->setText("Done.");
                    tempB->exec();
                }
                else
                {
                    QFileInfo nameTemp(fileName);
                    name = nameTemp.fileName();
                    temp += fileName + " -y -c:v libx264 -preset ultrafast " + outputFolder + "/" + name +"_Convert_format_is_Basu_Video_Studio." + format;
                    QByteArray temp2 = temp.toLocal8Bit();
                    const char * t2 = temp2.data();
                    system(t2);
                }
            }
        }
    }
    else
    {
        ok = msg->addButton((tr("Ok")), QMessageBox::ActionRole);
        ok->setShortcut(Qt::CTRL + Qt::Key_K);
        ok->setToolTip("Ctrl+K");
        msg->setText("The format entered is incorrect.");
        msg->setIcon(QMessageBox::Icon::Critical);
        msg->exec();
    }
    delete tempB;
    delete input;
    delete output;
    delete ok;
    delete Cancel;
}

void MainWindow::on_changeResolution_clicked()
{
    bool fOk;
    int width = QInputDialog::getInt(this, tr("Output width"), tr("Width : "), QLineEdit::Normal, 1, 2147483647, 50, &fOk);
    if (!fOk)
    {
        return;
    }
    int height = QInputDialog::getInt(this, tr("Output height"), tr("Height : "), QLineEdit::Normal, 1, 2147483647, 50, &fOk);
    if (!fOk)
    {
        return;
    }
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QMessageBox * msg = new QMessageBox();
    msg->setWindowTitle("Change video resolution");
    QMessageBox * tempB = new QMessageBox();
    tempB->setWindowTitle("Change video resolution");
    msg->setFont(font);
    tempB->setIcon(QMessageBox::Icon::Critical);
    tempB->setFont(font);
    QPushButton * input = new QPushButton(), * output = new QPushButton(), * ok = new QPushButton(), * Cancel = new QPushButton();
    ok = tempB->addButton((tr("Ok")), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    QString fileName, outputFolder;
    msg->setIcon(QMessageBox::Icon::Information);
    input = msg->addButton((tr("Input file")), QMessageBox::ActionRole);
    input->setShortcut(Qt::CTRL + Qt::Key_O);
    input->setToolTip("Ctrl+O");
    output = msg->addButton((tr("Output folder")), QMessageBox::ActionRole);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    output->setToolTip("Ctrl+F");
    ok = msg->addButton((tr("Ok")), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    Cancel = msg->addButton((tr("Cancel")), QMessageBox::ActionRole);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    Cancel->setToolTip("Ctrl+Q");
    msg->setText("Please select the file and its storage location.");
    click:
    msg->exec();
    if(msg->clickedButton() == input)
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open Video | Open Music"), "", tr("Video Files | Music Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)"));
        goto click;
    }
    else if(msg->clickedButton() == output)
    {
        outputFolder = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());
        goto click;
    }
    else if(msg->clickedButton() == ok)
    {
        if(fileName.size() == 0 && outputFolder.size() == 0)
        {
            tempB->setText("File and path not selected.");
            tempB->exec();
        }
        else if(outputFolder.size() == 0)
        {
            tempB->setText("No route selected.");
            tempB->exec();
        }
        else if(fileName.size() == 0)
        {
            tempB->setText("No file selected.");
            tempB->exec();
        }
        else
        {
            QString temp = "ffmpeg -i ", name;
            QFileInfo nameTemp(fileName);
            name = nameTemp.fileName();
            temp += fileName + " -y -s " + QString::number(width) + "x" + QString::number(height) + " -c:a copy " + outputFolder + "/Change_resolution_is_Basu_Video_Studio_" + name;
            QByteArray temp2 = temp.toLocal8Bit();
            const char * t2 = temp2.data();
            system(t2);
        }
    }
    delete tempB;
    delete input;
    delete output;
    delete ok;
    delete Cancel;
}

void MainWindow::on_addRemoveAudio_clicked()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QMessageBox * one = new QMessageBox(),  * temp = new QMessageBox(), * two = new QMessageBox();
    one->setWindowTitle("Add audio to video or remove audio from it");
    QPushButton * addAudio = new QPushButton(), * rmAudio, * ok = new QPushButton(), * Cancel = new QPushButton(),  * inputV = new QPushButton(), * output = new QPushButton();
    addAudio = one->addButton((tr("Add audio in video")), QMessageBox::ActionRole);
    addAudio->setShortcut(Qt::CTRL + Qt::Key_A);
    addAudio->setToolTip("Ctrl+A");
    rmAudio = new QPushButton();
    rmAudio = one->addButton((tr("Remove audio in video")), QMessageBox::ActionRole);
    rmAudio->setShortcut(Qt::CTRL + Qt::Key_R);
    rmAudio->setToolTip("Ctrl+R");
    Cancel = one->addButton((tr("Cancel")), QMessageBox::ActionRole);
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
    ok = temp->addButton((tr("Ok")), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    bool fOk;
    inputV = two->addButton((tr("Input video")), QMessageBox::ActionRole);
    inputV->setShortcut(Qt::CTRL + Qt::Key_V);
    inputV->setToolTip("Ctrl+V");
    output = two->addButton((tr("Output folder")), QMessageBox::ActionRole);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    output->setToolTip("Ctrl+F");
    Cancel = two->addButton((tr("Cancel")), QMessageBox::ActionRole);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    Cancel->setToolTip("Ctrl+Q");
    ok = two->addButton((tr("Ok")), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    two->setText("Please select the file and its storage location.");
    if (one->clickedButton() == addAudio)
    {
        sTime = QInputDialog::getText(this, tr("Start time to add"), tr("Start time : "), QLineEdit::Normal, "Example : 00:00:00",  &fOk);
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
        eTime = QInputDialog::getText(this, tr("End time to add"), tr("End time : "), QLineEdit::Normal, "Example : 00:00:00", &fOk);
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
        inputA = two->addButton((tr("Input audio")), QMessageBox::ActionRole);
        inputA->setShortcut(Qt::CTRL + Qt::Key_M);
        inputA->setToolTip("Ctrl+M");
        QString audio;
        click1:
        two->exec();
        if(two->clickedButton() == inputV)
        {
            video = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)"));
            goto click1;
        }
        else if(two->clickedButton() == inputA)
        {
            audio = QFileDialog::getOpenFileName(this, tr("Open Music"), "", tr("Music Files(*.3gp *.mp4 *.m4a *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.m4b *.m4p *.ogg *.oga *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wav *.wma *.webm *.wv *.8svx *.cda)"));
            goto click1;
        }
        else if(two->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());
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
                    tem = "ffmpeg -itsoffset 00:00:00 -t " + sTime + " -i " + video + " -vn " + outputFolder + "/1.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    int rSTimeH = stoi(strVS.substr(0, 2)); // Reduce start time hour
                    int rSTimeM = stoi(strVS.substr(3, 2)); // Reduce start time minute
                    int rSTimeS = stoi(strVS.substr(6, 2)); // Reduce start time Seconds
                    int rETimeH = stoi(strVE.substr(0, 2)); // Reduce end time hour
                    int rETimeM = stoi(strVE.substr(3, 2)); // Reduce end time minute
                    int rETimeS = stoi(strVE.substr(6, 2)); // Reduce end time Seconds
                    tem = "ffmpeg -ss 00:00:00 -t " + QString::number(rETimeH - rSTimeH) + ":" + QString::number(rETimeM - rSTimeM) + ":" +QString::number(rETimeS - rSTimeS) + " -i " + audio + outputFolder + "/2.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "ffmpeg -ss " + eTime + " -i " + video + " -vn " + outputFolder + "/3.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "touch " + outputFolder + "/file.txt";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    ofstream file("file.txt", ios::out);
                    if(!file)
                    {
                        temp->setText("There was a problem executing this and we were unable to generate the file needed to do so.");
                        temp->exec();
                    }
                    file << "file '1.mp3'\nfile '2.mp3'\nfile '3.mp3'";
                    file.close();
                    tem = "ffmpeg -f concat -safe 0 -i file.txt -c copy " + outputFolder + "/4.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    QFileInfo nameTemp(video);
                    name = nameTemp.fileName();
                    tem = "ffmpeg -i " + video + " -i 4.mp3 -map 0:0 -map 1:0 -c:v copy -preset ultrafast -async 1 " + outputFolder + "/Add_audio_" + name;
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
                    tem = "ffmpeg -ss 00:00:00 -t " + eTime + " -i " + audio + outputFolder + "/1.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);

                    tem = "ffmpeg -ss " + eTime + " -i " + video + " -vn " + outputFolder + "/2.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    tem = "touch " + outputFolder + "/file.txt";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    ofstream file("file.txt", ios::out);
                    if(!file)
                    {
                        temp->setText("There was a problem executing this and we were unable to generate the file needed to do so.");
                        temp->exec();
                    }
                    file << "file '1.mp3'\nfile '2.mp3'";
                    file.close();
                    tem = "ffmpeg -f concat -safe 0 -i file.txt -c copy " + outputFolder + "/3.mp3";
                    temp2 = tem.toLocal8Bit();
                    t2 = temp2.data();
                    system(t2);
                    QFileInfo nameTemp(video);
                    name = nameTemp.fileName();
                    tem = "ffmpeg -i " + video + " -i 3.mp3 -map 0:0 -map 1:0 -c:v copy -preset ultrafast -async 1 " + outputFolder + "/Add_audio_" + name;
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
        sTime = QInputDialog::getText(this, tr("Start time to remove"), tr("Start time : "), QLineEdit::Normal, "Example : 00:00:00",  &fOk);
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
        eTime = QInputDialog::getText(this, tr("End time to add"), tr("End time : "), QLineEdit::Normal, "Example : 00:00:00", &fOk);
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
            intVE = stoi(strVS.substr(0, 2)) * 3600 + stoi(strVS.substr(3, 2)) * 60 + stoi(strVS.substr(6, 2));
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
            temp->setText("The end time must be greater than the end time.");
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
            video = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)"));
            goto click2;
        }
        else if(two->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());
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
                tem = "ffmpeg -i " + video + " -af ""volume=enable='between(t," + QString::number(intVS) + "," + QString::number(intVE) + ")':volume=0"" -c:v copy " + outputFolder;
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
