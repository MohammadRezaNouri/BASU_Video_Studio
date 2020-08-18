#ifndef CHANGERESOLUTION_H
#define CHANGERESOLUTION_H

#include "videoEditor.h"

class changeResolution : public videoEditor
{
public:
    changeResolution();
    virtual void ffmpeg();
private:
    int width, height;
};

#endif // CHANGERESOLUTION_H
