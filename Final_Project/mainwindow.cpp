#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "qmessagebox.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BASU Video Studio");
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
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    QString formats = "*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)";
    QMessageBox * msg = new QMessageBox();
    msg->setWindowTitle("Convert video and audio formats");
    QMessageBox * not_found = new QMessageBox();
    not_found->setWindowTitle("Convert video and audio formats");
    msg->setFont(font);
    not_found->setIcon(QMessageBox::Icon::Critical);
    not_found->setFont(font);
    bool fOk;
    QString format = QInputDialog::getText(this, tr("Output format"), tr("Format : "), QLineEdit::Normal, "Example: mp3", &fOk);
    if (!fOk)
    {
        return;
    }
    QPushButton * input = new QPushButton(), * output = new QPushButton(), * ok = new QPushButton(), * Cancel = new QPushButton();
    ok = not_found->addButton((tr("Ok")), QMessageBox::ActionRole);
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
            outputFolder = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
            goto click;
        }
        else if(msg->clickedButton() == ok)
        {
            if(fileName.size() == 0 && outputFolder.size() == 0)
            {
                not_found->setText("File and path not selected.");
                not_found->exec();
            }
            else if(outputFolder.size() == 0)
            {
                not_found->setText("No route selected.");
                not_found->exec();
            }
            else if(fileName.size() == 0)
            {
                not_found->setText("No file selected.");
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
                system(t2);
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
}

