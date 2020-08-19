#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoEditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
protected:
    void resizeEvent(QResizeEvent* evt) override;
private slots:
    void on_convertFormat_clicked();

    void on_changeResolution_clicked();

    void on_addRemoveAudio_clicked();

    void on_connectVideos_clicked();

    void on_deletePartVideo_clicked();

    void on_reduceVolume_clicked();

    void on_play_clicked();

    void on_exit_clicked();

private:
    Ui::MainWindow * ui;
    videoEditor * start = nullptr;
};

#endif // MAINWINDOW_H
