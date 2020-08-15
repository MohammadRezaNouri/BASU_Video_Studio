#include "reduceVolume.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include "qmessagebox.h"
#include <QFileDialog>
#include <iostream>

using namespace std;

reduceVolume::reduceVolume()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    bool fOk;
    int crf = QInputDialog::getInt(nullptr, "Change the volume", "Number close to 51 = less volume\nNumber close to 0 = more volume", QLineEdit::Normal, 0, 51, 5, &fOk);
    if (!fOk)
    {
        return;
    }
    QMessageBox * msg = new QMessageBox(), * temp = new QMessageBox();
    msg->setWindowTitle("Reduce video volume");
    msg->setFont(font);
    msg->setIcon(QMessageBox::Icon::Information);
    msg->setText("Please select the video and its storage location.");
    temp->setWindowTitle("Reduce video volume");
    temp->setFont(font);
    temp->setIcon(QMessageBox::Icon::Critical);
    QPushButton * input = new QPushButton(), * output = new QPushButton(), * ok = new QPushButton(), * Cancel = new QPushButton();
    ok = temp->addButton("Ok", QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    input = msg->addButton("Input video", QMessageBox::ActionRole);
    input->setShortcut(Qt::CTRL + Qt::Key_O);
    input->setToolTip("Ctrl+O");
    output = msg->addButton("Output folder", QMessageBox::ActionRole);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    output->setToolTip("Ctrl+F");
    ok = msg->addButton("Ok", QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    Cancel = msg->addButton("Cancel", QMessageBox::ActionRole);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    Cancel->setToolTip("Ctrl+Q");
    QString fileName, outputFolder;
    click:
    msg->exec();
    if(msg->clickedButton() == input)
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
        if(fileName.size() == 0 && outputFolder.size() == 0)
        {
            temp->setText("Video and path not selected.");
            temp->exec();
            delete temp;
            delete input;
            delete output;
            delete ok;
            delete Cancel;
            delete msg;
            return;
        }
        else if(outputFolder.size() == 0)
        {
            temp->setText("No route selected.");
            temp->exec();
            delete temp;
            delete input;
            delete output;
            delete ok;
            delete Cancel;
            delete msg;
            return;
        }
        else if(fileName.size() == 0)
        {
            temp->setText("No video selected.");
            temp->exec();
            delete temp;
            delete input;
            delete output;
            delete ok;
            delete Cancel;
            delete msg;
            return;
        }
        QString t1 = "ffmpeg -y -i ";
        QFileInfo nameTemp(fileName);
        t1 += fileName + " -crf " + QString::number(crf) + " " + outputFolder + "/Reduce_volume_" + nameTemp.fileName();
        QByteArray t2 = t1.toLocal8Bit();
        const char * t3 = t2.data();
        system(t3);
        delete temp;
        delete input;
        delete output;
        delete ok;
        delete Cancel;
        delete msg;
        return;
    }
    else
    {
        delete temp;
        delete input;
        delete output;
        delete ok;
        delete Cancel;
        delete msg;
        return;
    }
}
