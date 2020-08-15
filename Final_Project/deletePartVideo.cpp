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
    QString sTime, eTime; // Start & end time and select video
    bool fOk;
    sTime = QInputDialog::getText(nullptr, "Start time to add", "Start time : ", QLineEdit::Normal, "Example : 00:00:00",  &fOk);
    if (!fOk)
    {
        return;
    }
    QMessageBox * temp = new QMessageBox();
    temp->setIcon(QMessageBox::Icon::Critical);
    temp->setWindowTitle("Delete parts of the video");
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
    try
    {
        int intVS = stoi(strVS.substr(0, 2)) * 3600 + stoi(strVS.substr(3, 2)) * 60 + stoi(strVS.substr(6, 2));
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
}
