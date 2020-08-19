#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectVideos.h"
#include "deletePartVideo.h"
#include "reduceVolume.h"
#include "convertFormat.h"
#include "changeResolution.h"
#include "addRemoveAudio.h" // Add audio to video or remove audio from it

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BASU Video Studio");
    QResizeEvent * evt;
    resizeEvent(evt); // Call resize main window
}

MainWindow::~MainWindow() // Destructor
{
    if(start != nullptr)
    {
        delete start; // videoEditor member
    }
    if(player != nullptr)
    {
        delete player; // Music player member
    }
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* evt) // Resize main window function
{
    QPixmap bkgnd("../background.jpg"); // Set Background image
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QMainWindow::resizeEvent(evt);
}

void MainWindow::on_convertFormat_clicked()
{
    start = new convertFormat();
}

void MainWindow::on_changeResolution_clicked()
{
    start = new changeResolution();
}

void MainWindow::on_addRemoveAudio_clicked() // Add audio to video or remove audio from it
{
    start = new addRemoveAudio();
}

void MainWindow::on_connectVideos_clicked()
{
    start = new connectVideos();
}

void MainWindow::on_deletePartVideo_clicked()
{
    start = new deletePartVideo();
}

void MainWindow::on_reduceVolume_clicked()
{
    start = new reduceVolume();
}

void MainWindow::on_exit_clicked() // Bye Bye
{
    MainWindow::close();
}

void MainWindow::on_horizontalProgress_sliderMoved(int position) // Slider change music player position
{
    if(player != nullptr)
    {
        player->setPosition(position);
    }
}

void MainWindow::on_horizontalVolume_sliderMoved(int position) // Slider change music player volume
{
    if(player != nullptr)
    {
        player->setVolume(position);
    }
}

void MainWindow::on_open_clicked() // Select music for music player
{
    if(player != nullptr)
    {
        player->stop();//Stop the previous video
    }
    player = new QMediaPlayer(this);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);//Change the position of the music by the user
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);//Changing the current position
    fileName = QFileDialog::getOpenFileName(nullptr, "Open Music", "", "Music Files(*.m4a *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.m4b *.m4p *.ogg *.oga *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wav *.wma *.webm *.wv *.8svx *.cda)"); //select music
    if (fileName.size() == 0)//Cancel button
    {
        return;
    }
    player->setMedia(QUrl::fromLocalFile(fileName));
    player->play();
}

void MainWindow::on_play_clicked()
{
    if(player != nullptr)
    {
        player->play();
    }
}

void MainWindow::on_pause_clicked()
{
    if(player != nullptr)
    {
        player->pause();
    }
}

void MainWindow::on_stop_clicked()
{
    if(player != nullptr)
    {
        player->stop();
    }
}

void MainWindow::on_positionChanged(int position)//Change the position of the music by the user
{
    ui->horizontalProgress->setValue(position);
}

void MainWindow::on_durationChanged(int position)//Changing the current position
{
    ui->horizontalProgress->setMaximum(position);
}
