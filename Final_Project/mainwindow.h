#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent* evt) override;
private slots:
    void on_convertFormat_clicked();

    void on_changeResolution_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
