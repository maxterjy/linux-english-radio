#pragma once
#include <gst/gst.h>

class AudioPlayer {
private:
    GstElement *pipeline, *source, *convert, *sink;
    GstBus *bus;
    
    char *strCurrentTime, *strDuration;

    static void pad_added_handler (GstElement * src, GstPad * srcPad, AudioPlayer *player);

    bool ready = false;

public:
    AudioPlayer();

    void init(char *url);
    void play();
    void pause();

    char* getDuration();
    char* getCurrentTime();

    bool isReady();
};

