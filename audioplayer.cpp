#include "audioplayer.h"
#include <string.h>
#include <stdio.h>

void pad_added_handler (GstElement * src, GstPad * srcPad, AudioPlayer *player) {
    GstPad *sinkPad = gst_element_get_static_pad(player->convert, "sink");
    gst_pad_link(srcPad, sinkPad);
}

AudioPlayer::AudioPlayer(int argc, char *argv[]){
    gst_init(&argc, &argv);

    strCurrentTime = (char*)malloc(16);
    strDuration = (char*)malloc(16);
}

void AudioPlayer::load(char *url){
    source = gst_element_factory_make("uridecodebin", "source");
    convert = gst_element_factory_make("audioconvert", "convert");
    sink = gst_element_factory_make("autoaudiosink", "sink");

    pipeline = gst_pipeline_new("pipeline");

    gst_bin_add_many(GST_BIN(pipeline), source, convert, sink, NULL);    
    
    gst_element_link(convert, sink);

    g_object_set(source, "uri", url, NULL);

    g_signal_connect(source, "pad-added", G_CALLBACK(pad_added_handler), this);    

    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    bus = gst_element_get_bus(pipeline);

    GstMessage *msg;

    //loop until state change to PLAY
    while (1) {
        msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_STATE_CHANGED));

        if (msg != NULL) {
            if (msg->type == GST_MESSAGE_ERROR) {
                g_print("load err\n");                
                break;
            }
            else if (msg->type == GST_MESSAGE_STATE_CHANGED) {
                GstState newState;
                gst_message_parse_state_changed(msg, NULL, &newState, NULL);

                if (newState == GST_STATE_PLAYING) {
                    gint64 duration;                    

                    gst_element_query_duration(pipeline, GST_FORMAT_TIME, &duration);
                    
                    char fullDurationTime[16];
                    sprintf(fullDurationTime, "%"GST_TIME_FORMAT,  GST_TIME_ARGS(duration));

                    strncpy(strDuration, fullDurationTime+2, 5);
                    strDuration[5] = 0;                

                    break;
                }
            }
        }
    }

    //loop until reach End of Sound
    char fullCurrentTime[16];
    while (1) {
        msg = gst_bus_timed_pop_filtered(bus, GST_SECOND, static_cast<GstMessageType>(GST_MESSAGE_EOS));

        if (msg){
            if (msg->type == GST_MESSAGE_EOS) {
                g_print("end of sound\n");
                break;
            }
        }
        else {
            gint64 current = -1;
            gst_element_query_position(pipeline, GST_FORMAT_TIME, &current);
            sprintf(fullCurrentTime, "%"GST_TIME_FORMAT,  GST_TIME_ARGS(current));

            strncpy(strCurrentTime, fullCurrentTime+2, 5);
            strCurrentTime[5] = 0;
        }
    }
}

void AudioPlayer::play(){
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

void AudioPlayer::pause(){
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
}

char* AudioPlayer::getDuration(){
    return strDuration;
}

char* AudioPlayer::getCurrentTime(){
    return strCurrentTime;
}


int main(int argc, char *argv[]) {
    AudioPlayer player(argc, argv);
    player.load("https://av.voanews.com/clips/VLE/2019/12/02/df3285f5-19bf-452a-a0bb-22103c2ac0e7_hq.mp3");

    return 0;
}