#ifndef CHANGEVOLUME_H
#define CHANGEVOLUME_H

#include "videoEditor.h"

class changeVolume : public videoEditor
{
public:
    changeVolume();
    virtual void ffmpeg();
private:
    int crf; // for Change resulation
};

#endif // CHANGEVOLUME_H
