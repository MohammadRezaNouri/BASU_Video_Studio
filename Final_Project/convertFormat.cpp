#include "convertFormat.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QInputDialog>

convertFormat::convertFormat()
{
    bool fOk;
    format = QInputDialog::getText(nullptr, "Output format", "Format : ", QLineEdit::Normal, "Example: mp3", &fOk);
    if (!fOk)
    {
        return;
    }
    QString formats = "*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)";
    setWFIOk();
    if (formats.contains(format) == true) // Search input format to all formats
    {
        setMsgButtons();
        msg->setText("Please select the file and its storage location.");
        click:
        msg->exec();
        if(msg->clickedButton() == input)
        {
            fileName = QFileDialog::getOpenFileName(nullptr, "Open Video | Open Music", "", "Video Files | Music Files(*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)");
            goto click;
        }
        else if(msg->clickedButton() == output)
        {
            outputFolder = QFileDialog::getExistingDirectory(nullptr, "Select Output Folder", QDir::currentPath());
            goto click;
        }
        else if(msg->clickedButton() == ok)
        {
            if(fileName.size() == 0 && outputFolder.size() == 0)
            {
                temp->setText("File and path not selected.");
                temp->exec();
            }
            else if(outputFolder.size() == 0)
            {
                temp->setText("No route selected.");
                temp->exec();
            }
            else if(fileName.size() == 0)
            {
                temp->setText("No file selected.");
                temp->exec();
            }
            else
            {
                ffmpeg();
            }
        }
    }
    else
    {
        ok = msg->addButton("Ok", QMessageBox::ActionRole);
        ok->setShortcut(Qt::CTRL + Qt::Key_K);
        ok->setToolTip("Ctrl+K");
        msg->setText("The format entered is incorrect.");
        msg->setIcon(QMessageBox::Icon::Critical);
        msg->exec();
    }
}

void convertFormat::ffmpeg()
{
    QString temp = "ffmpeg -i ", name;
    if(format == "gif")
    {
        QFileInfo nameTemp(fileName);
        name = nameTemp.fileName();
        temp += fileName + " -y -vf scale=500:-1 -t 10 -r 10 " + outputFolder + "/" + name +"_Convert_format_is_Basu_Video_Studio." + format;
        QByteArray temp2 = temp.toLocal8Bit();
        const char * t2 = temp2.data();
        system(t2);
    }
    else
    {
        QFileInfo nameTemp(fileName);
        name = nameTemp.fileName();
        temp += fileName + " -y -c:v libx264 -preset ultrafast " + outputFolder + "/" + name +"_Convert_format_is_Basu_Video_Studio." + format;
        QByteArray temp2 = temp.toLocal8Bit();
        const char * t2 = temp2.data();
        system(t2);
    }
}
