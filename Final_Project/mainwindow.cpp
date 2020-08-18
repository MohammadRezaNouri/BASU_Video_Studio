#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectVideos.h"
#include "deletePartVideo.h"
#include "reduceVolume.h"
#include "play.h"
#include "convertFormat.h"
#include "changeResolution.h"
#include "addRemoveAudio.h"
#include "videoEditor.h"

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
    convertFormat start;
}

void MainWindow::on_changeResolution_clicked()
{
    changeResolution start;
}

void MainWindow::on_addRemoveAudio_clicked()
{
    addRemoveAudio start;
}

void MainWindow::on_connectVideos_clicked()
{
    connectVideos start;
}

void MainWindow::on_deletePartVideo_clicked()
{
    deletePartVideo start;
}

void MainWindow::on_reduceVolume_clicked()
{
    reduceVolume start;
}

void MainWindow::on_play_clicked()
{
    play start;
}
