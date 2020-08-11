#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "qmessagebox.h"
#include <QInputDialog>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BASU Video Studio");
    QResizeEvent * evt;
    resizeEvent(evt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd("../background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QMainWindow::resizeEvent(evt);
}

void MainWindow::on_convertFormat_clicked()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QString formats = "*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)";
    QMessageBox * msg = new QMessageBox();
    msg->setWindowTitle("Convert video and audio formats");
    QMessageBox * tempB = new QMessageBox();
    tempB->setWindowTitle("Convert video and audio formats");
    msg->setFont(font);
    tempB->setIcon(QMessageBox::Icon::Critical);
    tempB->setFont(font);
    bool fOk;
    QString format = QInputDialog::getText(this, tr("Output format"), tr("Format : "), QLineEdit::Normal, "Example: mp3", &fOk);
    if (!fOk)
    {
        delete msg;
        delete tempB;
        return;
    }
    QPushButton * input = new QPushButton(), * output = new QPushButton(), * ok = new QPushButton(), * Cancel = new QPushButton();
    ok = tempB->addButton((tr("Ok")), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    QString fileName, outputFolder;
    if (formats.contains(format) == true)
    {
        msg->setIcon(QMessageBox::Icon::Information);
        input = msg->addButton((tr("Input file")), QMessageBox::ActionRole);
        input->setShortcut(Qt::CTRL + Qt::Key_O);
        input->setToolTip("Ctrl+O");
        output = msg->addButton((tr("Output folder")), QMessageBox::ActionRole);
        output->setShortcut(Qt::CTRL + Qt::Key_F);
        output->setToolTip("Ctrl+F");
        ok = msg->addButton((tr("Ok")), QMessageBox::ActionRole);
        ok->setShortcut(Qt::CTRL + Qt::Key_K);
        ok->setToolTip("Ctrl+K");
        Cancel = msg->addButton((tr("Cancel")), QMessageBox::ActionRole);
        Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
        Cancel->setToolTip("Ctrl+Q");
        msg->setText("Please select the file and its storage location.");
        click:
        msg->exec();
        if(msg->clickedButton() == input)
        {
            fileName = QFileDialog::getOpenFileName(this, tr("Open Video | Open Music"), "", tr("Video Files | Music Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)"));
            goto click;
        }
        else if(msg->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());
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
                if(format == "gif")
                {
                    QFileInfo nameTemp(fileName);
                    name = nameTemp.fileName();
                    temp += fileName + " -y -vf scale=500:-1 -t 10 -r 10 " + outputFolder + "/" + name +"_Convert_format_is_Basu_Video_Studio." + format;
                    QByteArray temp2 = temp.toLocal8Bit();
                    const char * t2 = temp2.data();
                    system(t2);
                    tempB->setText("Done.");
                    tempB->exec();
                }
                else
                {
                    QFileInfo nameTemp(fileName);
                    name = nameTemp.fileName();
                    temp += fileName + " -y -c:v libx264 -preset ultrafast " + outputFolder + "/" + name +"_Convert_format_is_Basu_Video_Studio." + format;
                    QByteArray temp2 = temp.toLocal8Bit();
                    const char * t2 = temp2.data();
                    system(t2);
                }
            }
        }
    }
    else
    {
        ok = msg->addButton((tr("Ok")), QMessageBox::ActionRole);
        ok->setShortcut(Qt::CTRL + Qt::Key_K);
        ok->setToolTip("Ctrl+K");
        msg->setText("The format entered is incorrect.");
        msg->setIcon(QMessageBox::Icon::Critical);
        msg->exec();
    }
    delete tempB;
    delete input;
    delete output;
    delete ok;
    delete Cancel;
}

void MainWindow::on_changeResolution_clicked()
{
    bool fOk;
    int width = QInputDialog::getInt(this, tr("Output width"), tr("Width : "), QLineEdit::Normal, 1, 2147483647, 50, &fOk);
    if (!fOk)
    {
        return;
    }
    int height = QInputDialog::getInt(this, tr("Output height"), tr("Height : "), QLineEdit::Normal, 1, 2147483647, 50, &fOk);
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
    ok = tempB->addButton((tr("Ok")), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    QString fileName, outputFolder;
    msg->setIcon(QMessageBox::Icon::Information);
    input = msg->addButton((tr("Input file")), QMessageBox::ActionRole);
    input->setShortcut(Qt::CTRL + Qt::Key_O);
    input->setToolTip("Ctrl+O");
    output = msg->addButton((tr("Output folder")), QMessageBox::ActionRole);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    output->setToolTip("Ctrl+F");
    ok = msg->addButton((tr("Ok")), QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    Cancel = msg->addButton((tr("Cancel")), QMessageBox::ActionRole);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    Cancel->setToolTip("Ctrl+Q");
    msg->setText("Please select the file and its storage location.");
    click:
    msg->exec();
    if(msg->clickedButton() == input)
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open Video | Open Music"), "", tr("Video Files | Music Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)"));
        goto click;
    }
    else if(msg->clickedButton() == output)
    {
        outputFolder = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());
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

void MainWindow::on_addRemoveAudio_clicked()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QMessageBox * one = new QMessageBox(), * temp = new QMessageBox();
    one->setWindowTitle("Add audio to video or remove audio from it");
    QPushButton * addAudio = new QPushButton(), * rmAudio = new QPushButton(), * ok = new QPushButton(), * Cancel = new QPushButton();
    addAudio = one->addButton((tr("Add audio in video")), QMessageBox::ActionRole);
    addAudio->setShortcut(Qt::CTRL + Qt::Key_A);
    addAudio->setToolTip("Ctrl+A");
    rmAudio = one->addButton((tr("Remove audio in video")), QMessageBox::ActionRole);
    rmAudio->setShortcut(Qt::CTRL + Qt::Key_R);
    rmAudio->setToolTip("Ctrl+R");
    Cancel = one->addButton((tr("Cancel")), QMessageBox::ActionRole);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    Cancel->setToolTip("Ctrl+Q");
    one->setFont(font);
    one->setIcon(QMessageBox::Icon::Information);
    one->setText("Please select : ");
    temp->setFont(font);
    one->exec();
    if (one->clickedButton() == addAudio)
    {
        bool fOk;
        QString sTime = QInputDialog::getText(this, tr("Start time to add"), tr("Start time : "), QLineEdit::Normal, "Example : 00:00:00",  &fOk);
        if (!fOk)
        {
            return;
        }
        if (sTime[0] == '-')
        {
            temp->setText("Start time is not negative.");
            temp->setIcon(QMessageBox::Icon::Critical);
            ok = temp->addButton((tr("Ok")), QMessageBox::ActionRole);
            ok->setShortcut(Qt::CTRL + Qt::Key_K);
            ok->setToolTip("Ctrl+K");
            temp->exec();
            return;
        }
        QString eTime = QInputDialog::getText(this, tr("End time to add"), tr("End time : "), QLineEdit::Normal, "Example : 00:00:00", &fOk);
        if (!fOk)
        {
            return;
        }
        if (eTime[0] == '-')
        {
            temp->setText("End time is not negative.");
            temp->setIcon(QMessageBox::Icon::Critical);
            ok = temp->addButton((tr("Ok")), QMessageBox::ActionRole);
            ok->setShortcut(Qt::CTRL + Qt::Key_K);
            ok->setToolTip("Ctrl+K");
            temp->exec();
            return;
        }
    }

}
