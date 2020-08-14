#include "connectVideos.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <iostream>
#include <string>
#include <QInputDialog>
#include "QFileDialog"

using namespace std;

connectVideos::connectVideos()
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
}
