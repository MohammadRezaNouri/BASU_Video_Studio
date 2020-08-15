#include "reduceVolume.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

reduceVolume::reduceVolume()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    bool fOk;
    int crf = QInputDialog::getInt(nullptr, "Change the volume", "Number : ", QLineEdit::Normal, 0, 51, 5, &fOk);
    if (!fOk)
    {
        return;
    }
}
