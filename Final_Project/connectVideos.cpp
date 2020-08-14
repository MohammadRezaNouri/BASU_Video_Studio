#include "connectVideos.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <iostream>
#include <string>

using namespace std;

connectVideos::connectVideos()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QMessageBox * msg = new QMessageBox();
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
    msg->exec();
}
