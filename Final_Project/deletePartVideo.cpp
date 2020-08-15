#include "deletePartVideo.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <QInputDialog>
//#include <iostream>
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
    QPushButton * video = new QPushButton(), * outFolder = new QPushButton(), * ok = new QPushButton(), * cancel = new QPushButton();
    video = msg->addButton("Input Video", QMessageBox::ActionRole);
    video->setShortcut(Qt::CTRL + Qt::Key_V);
    video->setToolTip("Ctrl+V");
    outFolder = msg->addButton("Output folder", QMessageBox::ActionRole);
    outFolder->setShortcut(Qt::CTRL + Qt::Key_F);
    outFolder->setToolTip("Ctrl+F");
    cancel = msg->addButton("Cancel", QMessageBox::ActionRole);
    cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    cancel->setToolTip("Ctrl+Q");
    ok = msg->addButton("Ok", QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
}
