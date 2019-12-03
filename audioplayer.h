#pragma once
#include <gst/gst.h>

class AudioPlayer {
public:
    AudioPlayer(int argc, char *argv[]);

    void load(char *url);
    void play();
    void pause();

    char* getDuration();
    char* getCurrentTime();

    GstElement *pipeline, *source, *convert, *sink;
    GstBus *bus;
    
    char *strCurrentTime, *strDuration;
};

