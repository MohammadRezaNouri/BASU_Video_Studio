#include "videoEditor.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

void videoEditor::setWFIOk(QString title)
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    msg = new QMessageBox();
    msg->setWindowTitle(title);
    msg->setFont(font);
    temp = new QMessageBox();
    temp->setWindowTitle(title);
    temp->setIcon(QMessageBox::Icon::Critical);
    temp->setFont(font);
    ok = new QPushButton();
    ok = temp->addButton(("Ok"), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
}

void videoEditor::setMsgButtons()
{
    input = new QPushButton();
    output = new QPushButton();
    Cancel = new QPushButton();
    msg->setIcon(QMessageBox::Icon::Information);
    input = msg->addButton(("Input file"), QMessageBox::ActionRole);
    output = msg->addButton("Output folder", QMessageBox::ActionRole);
    ok = msg->addButton("Ok", QMessageBox::ActionRole);
    Cancel = msg->addButton("Cancel", QMessageBox::ActionRole);
    setShortcut();
    setToolTip();
}

void videoEditor::setShortcut()
{
    input->setShortcut(Qt::CTRL + Qt::Key_O);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
}

void videoEditor::setToolTip()
{
    input->setToolTip("Ctrl+O");
    output->setToolTip("Ctrl+F");
    ok->setToolTip("Ctrl+K");
    Cancel->setToolTip("Ctrl+Q");
}

videoEditor::~videoEditor()
{
    if(temp != nullptr)
    {
        delete temp;
    }
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
    if(Cancel != nullptr)
    {
        delete Cancel;
    }
    if(msg != nullptr)
    {
        delete msg;
    }
}

void videoEditor::msgNotFilePath()
{
    temp->setText("File and path not selected.");
    temp->exec();
}

void videoEditor::msgNotPath()
{
    temp->setText("No route selected.");
    temp->exec();
}
void videoEditor::msgNotFile()
{
    temp->setText("No file selected.");
    temp->exec();
}

void videoEditor::ffmpeg()
{

}

void videoEditor::command(QString cmd)
{
    QByteArray t1 = cmd.toLocal8Bit();
    const char * t2 = t1.data();
    system(t2);
}

QString videoEditor::getName()
{
    QFileInfo nameTemp(fileName);
    return nameTemp.fileName();
}
