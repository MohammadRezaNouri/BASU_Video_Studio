#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoEditor.h"
#include <QMediaPlayer>

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
    void resizeEvent(QResizeEvent* evt) override;// Resize main window function

private slots://Main window buttons
    void on_convertFormat_clicked();

    void on_changeResolution_clicked();

    void on_addRemoveAudio_clicked();

    void on_connectVideos_clicked();

    void on_deletePartVideo_clicked();

    void on_changeVolume_clicked();

    void on_exit_clicked();

    void on_horizontalProgress_sliderMoved(int position);

    void on_horizontalVolume_sliderMoved(int position);

    void on_open_clicked();

    void on_play_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_positionChanged(int);

    void on_durationChanged(int);

private:
    Ui::MainWindow * ui;
    videoEditor * start = nullptr;
    QMediaPlayer * player = nullptr;
    QString fileName;//music file for music player
};

#endif // MAINWINDOW_H
