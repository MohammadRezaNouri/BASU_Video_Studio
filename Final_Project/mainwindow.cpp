#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectVideos.h"
#include "deletePartVideo.h"
#include "reduceVolume.h"
#include "convertFormat.h"
#include "changeResolution.h"
#include "addRemoveAudio.h"

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

}
