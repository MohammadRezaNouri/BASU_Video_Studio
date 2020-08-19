#include "videoEditor.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

void videoEditor::setWFIOk(QString title)//set window title & icon & ok button
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15); // Message size
    msg = new QMessageBox();
    msg->setWindowTitle(title);
    msg->setFont(font);
    msg->setIcon(QMessageBox::Icon::Information);
    temp = new QMessageBox();
    temp->setWindowTitle(title);
    temp->setIcon(QMessageBox::Icon::Critical);
    temp->setFont(font);
    ok = new QPushButton();
    ok = temp->addButton(("Ok"), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
}

void videoEditor::setMsgButtons() // Set Message buttond (input video & outpu Folder & ok)
{
    input = new QPushButton();
    output = new QPushButton();
    input = msg->addButton("Input file", QMessageBox::ActionRole);
    output = msg->addButton("Output folder", QMessageBox::ActionRole);
    ok = msg->addButton("Ok", QMessageBox::ActionRole);
    msg->setStandardButtons(QMessageBox::Button::Cancel);
    setShortcut();
    setToolTip();
}

void videoEditor::setShortcut() // set buttons shortcut
{
    input->setShortcut(Qt::CTRL + Qt::Key_O);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
}

void videoEditor::setToolTip() // set buttons Tool  Tip
{
    input->setToolTip("Ctrl+O");
    output->setToolTip("Ctrl+F");
    ok->setToolTip("Ctrl+K");
}

videoEditor::~videoEditor()
{
    if(input == nullptr)
    {
        delete input;
    }
    if(output != nullptr)
    {
        delete output;
    }
    if(ok != nullptr)
    {
        delete ok;
    }
    /*if(Cancel != nullptr)
    {
        delete Cancel;
    }*/
    if(msg != nullptr)
    {
        delete msg;
    }
    if(temp != nullptr)
    {
        delete temp;
    }
}

void videoEditor::msgTemp(QString msg) // Show errors
{
    temp->setText(msg);
    temp->exec();
}

void videoEditor::ffmpeg() // Blank written here due to a compiler error
{

}

bool videoEditor::command(QString cmd)
{
    cmd += " && echo OK || echo Failed"; // Result comman == OK or Failed
    QByteArray t1 = cmd.toLocal8Bit();
    const char * t2 = t1.data(); // Convert QString to const char * t2
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    stream = popen(t2, "r"); // Start command
    if (stream)
    {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != nullptr) data.append(buffer); // Pour in data
        pclose(stream);
    }
    if(data == "OK\n")
    {
        return true;
    }
    return false;
}

QString videoEditor::getName() // Get video name
{
    QFileInfo nameTemp(fileName);
    return nameTemp.fileName();
}

bool videoEditor::ffprobe() // Get Video total time & check Check with inputs
{
    QString t1 = "ffprobe -i ";
    t1 += fileName + " -show_entries format=duration -v quiet -of csv=""p=0""" + " 2>&1";
    QByteArray t2 = t1.toLocal8Bit();
    const char * t3 = t2.data();
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
        msgTemp("The initial time is longer than the total time.");
        return false;
    }
    if (intVE > stoi(data))
    {
        msgTemp("The end time is longer than the total time.");
        return false;
    }
    return true;
}

bool videoEditor::checkTime(QString check, int time) // Check Input incorrect
{
    if (check[0] == '-')
    {
        msgTemp("Time is not negative.");
        return false;
    }
    else if (check.size() > 8)
    {
        msgTemp("Input is incorrect.");
        return false;
    }
    string str = check.toStdString();
    try
    {
        if (time == 0)
        {
            intVS = stoi(str.substr(0, 2)) * 3600 + stoi(str.substr(3, 2)) * 60 + stoi(str.substr(6, 2));
        }
        else if(time == 1)
        {
            intVE = stoi(str.substr(0, 2)) * 3600 + stoi(str.substr(3, 2)) * 60 + stoi(str.substr(6, 2));
        }
    }
    catch(...)
    {
        msgTemp("You entered the time date incorrectly.");
        return false;
    }
    if (stoi(str.substr(3, 2)) > 59)
    {
        msgTemp("Wrong input format. (minute > 59)");
        return false;
    }
    else if (stoi(str.substr(6, 2)) > 59)
    {
        msgTemp("Wrong input format. (seconds > 59)");
        return false;
    }
    return true;
}

bool videoEditor::checkSecTime() // Check start time < end time
{
    if (intVS > intVE)
    {
        msgTemp("The end time must be greater than the start time.");
        return false;
    }
    return true;
}
bool videoEditor::fullInput() // Error for empty inputs
{
    if(fileName.size() == 0 && outputFolder.size() == 0)
    {
        msgTemp("File and path not selected.");
        return false;
    }
    else if(outputFolder.size() == 0)
    {
        msgTemp("No route selected.");
        return false;
    }
    else if(fileName.size() == 0)
    {
        msgTemp("No file selected.");
        return false;
    }
    return true;
}
