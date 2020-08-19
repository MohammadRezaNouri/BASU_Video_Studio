#include "convertFormat.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QInputDialog>

convertFormat::convertFormat()
{
    format = QInputDialog::getText(nullptr, "Output format", "Format : ", QLineEdit::Normal, "Example: mp3", &fOk);
    if (!fOk) // Cancel button
    {
        return;
    }
    QString formats = "*.mp4 *.m4a *.f4v *.f4a *.m4b *.m4r *.f4b *.mov *.3gp *.3gp2 *.3g2 *.3gpp *.3gpp2 *.ogg *.oga *.ogv *.ogx *.wmv *.wma *.asf *.webm *.flv *.mkv *.vob *.drc *.gif *.gifv *.mng *.avi *.MTS *.M2TS *.TS *.qt *.yuv *.tm *.rmvb *.viv *.amv *.m4p *.m4v *.mpg *.mpeg *.mp2 *.mpe *.mpv *.m2v *.svi *.mxf *.roq *.nsv *.f4p *.flac *.mp3 *.wav *.aac *.aa *.aax *.act *.aiff *.alac *.amr *.ape *.au *.awb *.dct *.dss *.dvf *.gsm *.iklax *.ivs *.mmf *.mpc *.msv *.nmf *.mogg *.opus *.ra *.rm *.raw *.rf64 *.sln *.tta *.voc *.vox *.wv *.8svx *.cda)"; // True formats
    setWFIOk("Convert video and audio formats"); // Call dad function
    if (formats.contains(format) == true) // Search input format to all formats
    {
        setMsgButtons(); // Call dad function
        msg->setText("Please select the file and its storage location.");
        click:
        msg->exec();
        if(msg->clickedButton() == input) // Input Video
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
            if(fullInput()) // check input is not empty
            {
                ffmpeg();
            }
        }
    }
    else
    {
        msgTemp("The format entered is incorrect.");
    }
}

void convertFormat::ffmpeg()
{
    QString temp = "ffmpeg -i ";
    if(format == "gif") //Because this is different for gifs
    {
        temp += fileName + " -y -vf scale=500:-1 -t 10 -r 10 " + outputFolder + "/" + getName() +"_Convert_format_is_Basu_Video_Studio." + format;
        msgTemp("Please click the OK button and wait for the result page to appear.");
        if(command(temp))
        {
            msgTemp("Done");
        }
        else
        {
            msgTemp("This is not possible!");
        }
    }
    else
    {
        temp += fileName + " -y -c:v libx264 -preset ultrafast " + outputFolder + "/" + getName() +"_Convert_format_is_Basu_Video_Studio." + format;
        msgTemp("Please click the OK button and wait for the result page to appear.");
        if(command(temp))
        {
            msgTemp("Done");
        }
        else
        {
            msgTemp("This is not possible!");
        }
    }
}
