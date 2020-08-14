#include "connectVideos.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <iostream>
#include <string>
#include <QFileDialog>

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

    }
}
