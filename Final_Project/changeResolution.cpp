#include "changeResolution.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "qmessagebox.h"
#include <QInputDialog>

changeResolution::changeResolution()
{
    bool fOk;
    int width = QInputDialog::getInt(nullptr, "Output width", "Width : ", QLineEdit::Normal, 1, 2147483647, 50, &fOk);
    if (!fOk)
    {
        return;
    }
    int height = QInputDialog::getInt(nullptr, "Output height", "Height : ", QLineEdit::Normal, 1, 2147483647, 50, &fOk);
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
    ok = tempB->addButton("Ok", QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    QString fileName, outputFolder;
    msg->setIcon(QMessageBox::Icon::Information);
    input = msg->addButton("Input file", QMessageBox::ActionRole);
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
    msg->setText("Please select the file and its storage location.");
    click:
    msg->exec();
    if(msg->clickedButton() == input)
    {
        fileName = QFileDialog::getOpenFileName(nullptr, "Open Video | Open Music", "", "Video Files | Music Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)");
        goto click;
    }
    else if(msg->clickedButton() == output)
    {
        outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
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
