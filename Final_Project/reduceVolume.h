#ifndef REDUCEVOLUME_H
#define REDUCEVOLUME_H

#include "videoEditor.h"

class reduceVolume : public videoEditor
{
public:
    reduceVolume();
    virtual void ffmpeg();
private:
    int crf;
};

#endif // REDUCEVOLUME_H
