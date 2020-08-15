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
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QMessageBox * msg = new QMessageBox(), * temp = new QMessageBox();
    msg->setFont(font);
    msg->setIcon(QMessageBox::Icon::Information);
    msg->setText("Please select videos in order of connection type.");
    msg->setWindowTitle("Connect several video files to each other");
    QPushButton * inputV = new QPushButton(), * output = new QPushButton(), * cancel = new QPushButton(), * ok = new QPushButton();
    inputV = msg->addButton("Select videos", QMessageBox::ActionRole);
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
    QString outputFolder;
    QStringList ls;
    temp->setFont(font);
    temp->setWindowTitle("Connect several video files to each other");
    temp->setIcon(QMessageBox::Icon::Critical);
    ok = temp->addButton(("Ok"), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    click:
    msg->exec();
    if (msg->clickedButton() == inputV)
    {
        ls = QFileDialog::getOpenFileNames(nullptr, "Select videos", "/", ("Video Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p)"));
        goto click;
    }
    else if (msg->clickedButton() == output)
    {
        outputFolder = QFileDialog::getExistingDirectory(nullptr, ("Select Output Folder"), QDir::currentPath());
        goto click;
    }
    else if (msg->clickedButton() == cancel)
    {
        delete inputV;
        delete output;
        delete cancel;
        delete ok;
    }
    else
    {
        if(ls.size() == 0 && outputFolder.size() == 0)
        {
            temp->setText("Videos and path not selected.");
            temp->exec();
            delete ok;
            delete inputV;
            delete output;
            return;
        }
        if(ls.size() == 0)
        {
            temp->setText("Videos not selected.");
            temp->exec();
            delete ok;
            delete inputV;
            delete output;
            return;
        }
        if(outputFolder.size() == 0)
        {
            temp->setText("No route selected.");
            temp->exec();
            delete ok;
            delete inputV;
            delete output;
            return;
        }

        QString t1 = outputFolder + "/file.txt";
        ofstream file(t1.toStdString(), ios::out);
        if(!file)
        {
            temp->setText("There was a problem executing this and we were unable to generate the file needed to do so.");
            temp->exec();
            delete ok;
            delete inputV;
            delete output;
            return;
        }
        QFileInfo nameTemp;
        QByteArray t2;
        const char * t3;
        for (int i = 0; i < ls.size(); i++)
        {
            nameTemp = ls[i];
            t1 = "file 'cp_" + nameTemp.fileName() + "'\n";
            file << t1.toStdString();
            t1 = "cp " + ls[i] + " " + outputFolder + "/\"cp_" + nameTemp.fileName() + "\"";
            t2 = t1.toLocal8Bit();
            t3 = t2.data();
            system(t3);
        }
        file.close();
        t1 = "ffmpeg -y -f concat -i " + outputFolder + "/file.txt " + outputFolder + "/Connect_videos.mp4";
        t2 = t1.toLocal8Bit();
        t3 = t2.data();
        system(t3);
        for (int i = 0; i < ls.size(); i++)
        {
            nameTemp = ls[i];
            t1 = "rm " + outputFolder + "/cp_" + nameTemp.fileName();
            t2 = t1.toLocal8Bit();
            t3 = t2.data();
            system(t3);
        }
        t1 = "rm " + outputFolder + "/file.txt";
        t2 = t1.toLocal8Bit();
        t3 = t2.data();
        system(t3);
        delete ok;
        delete inputV;
        delete output;
        return;
    }
}
