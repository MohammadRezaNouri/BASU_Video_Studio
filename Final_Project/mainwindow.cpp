#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"

#include "qmessagebox.h"
#include  <QLineEdit>
#include  <QLayout>
#include <QInputDialog>
#include <iostream>
#include <string>
#include "qstring.h"
using namespace  std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QResizeEvent* evt;
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
    QMainWindow::resizeEvent(evt); // call inherited implementation
}

void MainWindow::on_convertFormat_clicked()
{
    QString formats = "*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)";
    QMessageBox * msg = new QMessageBox();
    QMessageBox * not_found = new QMessageBox();
    bool fOk;
    QString format = QInputDialog::getText(this, tr("Output format"), tr("Format : "), QLineEdit::Normal, "Example: mp3", &fOk);
    if (!fOk)
    {
        return;
    }
    QPushButton * input, * output, * ok;
    QString fileName, outputFolder;
    if (formats.contains(format) == true)
    {
        input = msg->addButton((tr("Input file")), QMessageBox::ActionRole);
        output = msg->addButton((tr("Output folder")), QMessageBox::ActionRole);
        ok = msg->addButton((tr("Ok")), QMessageBox::ActionRole);
        msg->setStandardButtons(QMessageBox::Cancel);
        msg->setInformativeText("Please select the file and its storage location.");
        msg->setStyleSheet("QLabel{min-width:500 px; font-size: 24px;} QPushButton{ width:250px; font-size: 18px; }");
        click:
        msg->exec();
        if(msg->clickedButton() == input)
        {
            fileName = QFileDialog::getOpenFileName(this, tr("Open Video | Open Music"), "", tr("Video Files | Music Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)"));
            goto click;
        }
        else if(msg->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
            goto click;
        }
        else if(msg->clickedButton() == ok)
        {
            if(fileName.size() == 0 && outputFolder.size() == 0)
            {
                not_found->setText("File and path not selected.");
                not_found->setStyleSheet("QLabel{min-width:500 px; font-size: 24px;} QPushButton{ width:250px; font-size: 18px; }");
                not_found->exec();
            }
            else if(outputFolder.size() == 0)
            {
                not_found->setText("No route selected.");
                not_found->setStyleSheet("QLabel{min-width:500 px; font-size: 24px;} QPushButton{ width:250px; font-size: 18px; }");
                not_found->exec();
            }
            else if(fileName.size() == 0)
            {
                not_found->setText("No file selected.");
                not_found->setStyleSheet("QLabel{min-width:500 px; font-size: 24px;} QPushButton{ width:250px; font-size: 18px; }");
                not_found->exec();
            }
            else
            {
                QString temp = "ffmpeg -i ", name;
                QFileInfo nameTemp(fileName);
                name = nameTemp.fileName();
                temp += fileName + " -c:v libx264 -preset ultrafast " + outputFolder + "/" + name +"_Convert_format_is_Basu_Video_Studio." + format;
                QByteArray temp2 = temp.toLocal8Bit();
                const char * t2 = temp2.data();
                cout << t2 << endl;
                system(t2);
            }
        }
    }
    else
    {
        msg->setText("The format entered is incorrect.");
        msg->setStyleSheet("QLabel{min-width:500 px; font-size: 24px;} QPushButton{ width:250px; font-size: 18px; }");
        msg->exec();
    }
}

