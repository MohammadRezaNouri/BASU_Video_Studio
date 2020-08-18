#ifndef DELETEPARTVIDEO_H
#define DELETEPARTVIDEO_H

#include "videoEditor.h"

class deletePartVideo : public videoEditor
{
public:
    deletePartVideo();
    virtual void ffmpeg();
};

#endif // DELETEPARTVIDEO_H
