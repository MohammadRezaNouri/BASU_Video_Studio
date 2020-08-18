#ifndef CONVERTFORMAT_H
#define CONVERTFORMAT_H

#include "qmessagebox.h"
#include "videoEditor.h"

class convertFormat : public videoEditor
{
public:
    convertFormat();
    virtual void ffmpeg();
private:
    QString format;
};

#endif // CONVERTFORMAT_H
