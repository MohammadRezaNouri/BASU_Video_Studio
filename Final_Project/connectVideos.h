#ifndef CONNECTVIDEOS_H
#define CONNECTVIDEOS_H

#include "videoEditor.h"

class connectVideos : public videoEditor
{
public:
    connectVideos();
    virtual bool fullInput();
    virtual void ffmpeg();
private:
    QStringList ls;
};

#endif // CONNECTVIDEOS_H
