#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectVideos.h"
#include "deletePartVideo.h"
#include "reduceVolume.h"
#include "convertFormat.h"
#include "changeResolution.h"
#include "addRemoveAudio.h"
#include <QDebug>
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
    if(start != nullptr)
    {
        delete start;
    }
    if(player != nullptr)
    {
        delete player;
    }
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
    start = new convertFormat();
}

void MainWindow::on_changeResolution_clicked()
{
    start = new changeResolution();
}

void MainWindow::on_addRemoveAudio_clicked()
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

void MainWindow::on_exit_clicked()
{
    MainWindow::close();
}

void MainWindow::on_horizontalProgress_sliderMoved(int position)
{
    if(player != nullptr)
    {
        player->setPosition(position);
    }
}

void MainWindow::on_horizontalVolume_sliderMoved(int position)
{
    if(player != nullptr)
    {
        player->setVolume(position);
    }
}

void MainWindow::on_open_clicked()
{
    if(player != nullptr)
    {
        player->stop();
    }
    player = new QMediaPlayer(this);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);
    fileName = QFileDialog::getOpenFileName(nullptr, "Open Music", "", "Music Files(*.m4a *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.m4b *.m4p *.ogg *.oga *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wav *.wma *.webm *.wv *.8svx *.cda)");
    if (fileName.size() == 0)
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

void MainWindow::on_positionChanged(int position)
{
    ui->horizontalProgress->setValue(position);
}

void MainWindow::on_durationChanged(int position)
{
    ui->horizontalProgress->setMaximum(position);
}
