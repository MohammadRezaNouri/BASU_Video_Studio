#include "reduceVolume.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include "qmessagebox.h"

reduceVolume::reduceVolume()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    bool fOk;
    int crf = QInputDialog::getInt(nullptr, "Change the volume", "Number close to 51 = less volume\nNumber close to 0 = more volume", QLineEdit::Normal, 0, 51, 5, &fOk);
    if (!fOk)
    {
        return;
    }
    QMessageBox * msg = new QMessageBox();
    msg->setWindowTitle("Reduce video volume");
    msg->setFont(font);
    msg->setIcon(QMessageBox::Icon::Information);
    msg->setText("Please select the video and its storage location.");
    QPushButton * input = new QPushButton(), * output = new QPushButton(), * ok = new QPushButton(), * Cancel = new QPushButton();
    input = msg->addButton("Input video", QMessageBox::ActionRole);
    input->setShortcut(Qt::CTRL + Qt::Key_O);
    input->setToolTip("Ctrl+O");
    output = msg->addButton("Output folder", QMessageBox::ActionRole);
    output->setShortcut(Qt::CTRL + Qt::Key_F);
    output->setToolTip("Ctrl+F");
    ok = msg->addButton("Ok", QMessageBox::ActionRole);
    ok->setShortcut(Qt::CTRL + Qt::Key_K);
    ok->setToolTip("Ctrl+K");
    Cancel = msg->addButton("Cancel", QMessageBox::ActionRole);
    Cancel->setShortcut(Qt::CTRL + Qt::Key_Q);
    Cancel->setToolTip("Ctrl+Q");

}
