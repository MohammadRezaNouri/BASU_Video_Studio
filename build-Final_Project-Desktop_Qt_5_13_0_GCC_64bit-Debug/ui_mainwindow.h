/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *convertFormat;
    QPushButton *changeResolution;
    QPushButton *addRemoveAudio;
    QPushButton *connectVideos;
    QPushButton *play;
    QPushButton *reduceVolume;
    QPushButton *deletePartVideo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1500, 1100);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        convertFormat = new QPushButton(centralWidget);
        convertFormat->setObjectName(QString::fromUtf8("convertFormat"));
        convertFormat->setGeometry(QRect(40, 20, 321, 61));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        convertFormat->setFont(font);
        convertFormat->setIconSize(QSize(16, 16));
        changeResolution = new QPushButton(centralWidget);
        changeResolution->setObjectName(QString::fromUtf8("changeResolution"));
        changeResolution->setGeometry(QRect(40, 100, 321, 61));
        addRemoveAudio = new QPushButton(centralWidget);
        addRemoveAudio->setObjectName(QString::fromUtf8("addRemoveAudio"));
        addRemoveAudio->setGeometry(QRect(40, 180, 321, 61));
        connectVideos = new QPushButton(centralWidget);
        connectVideos->setObjectName(QString::fromUtf8("connectVideos"));
        connectVideos->setGeometry(QRect(40, 260, 321, 61));
        play = new QPushButton(centralWidget);
        play->setObjectName(QString::fromUtf8("play"));
        play->setGeometry(QRect(40, 500, 321, 61));
        reduceVolume = new QPushButton(centralWidget);
        reduceVolume->setObjectName(QString::fromUtf8("reduceVolume"));
        reduceVolume->setGeometry(QRect(40, 420, 321, 61));
        deletePartVideo = new QPushButton(centralWidget);
        deletePartVideo->setObjectName(QString::fromUtf8("deletePartVideo"));
        deletePartVideo->setGeometry(QRect(40, 340, 321, 61));
        MainWindow->setCentralWidget(centralWidget);
        changeResolution->raise();
        addRemoveAudio->raise();
        connectVideos->raise();
        play->raise();
        reduceVolume->raise();
        deletePartVideo->raise();
        convertFormat->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(tooltip)
        MainWindow->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        MainWindow->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        convertFormat->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        convertFormat->setText(QCoreApplication::translate("MainWindow", "Convert video and audio formats", nullptr));
        changeResolution->setText(QCoreApplication::translate("MainWindow", "Change video resolution", nullptr));
        addRemoveAudio->setText(QCoreApplication::translate("MainWindow", "Add audio to video or remove audio from it", nullptr));
        connectVideos->setText(QCoreApplication::translate("MainWindow", "Connect several video files to each other", nullptr));
        play->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        reduceVolume->setText(QCoreApplication::translate("MainWindow", "Reduce video volume", nullptr));
        deletePartVideo->setText(QCoreApplication::translate("MainWindow", "Delete parts of the video", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
