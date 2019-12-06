#include <stdio.h>
#include <pthread.h>
#include "audioplayer.h"
#include "newspuller.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    NewsPuller newsPuller;
    newsPuller.init();

    sleep(5);

    std::vector<Channel> channels = newsPuller.getChannels();

    int numChannel = channels.size();
    printf("\tLIST OF CHANNEL:\n\n");
    for(int i = 0; i < numChannel; i++) {
        printf("\t%d: %s\n\n", i, channels[i].title.c_str());
    }

    printf("Press a number from 0 to %d select channel: ", numChannel-1);

    int n;
    scanf("%d", &n);
    if (n < 0 || n >= numChannel) {
        printf("Invalid channel number");
        return -1;
    }
    
    std::string channelID = channels[n].id;
    std::vector<News> news = newsPuller.getNews(channelID);
    int numNews = news.size();

    printf("\tLIST OF NEWS:\n\n");
    for(int i = 0; i < numNews; i++) {
        printf("\t%d: %s\n\n", i, news[i].title.c_str());
    }

    printf("Press a number from 0 to %d select news: ", numNews-1);
    scanf("%d", &n);
    if (n < 0 || n >= numNews){
        printf("Invalid news number");
        return -1;
    }

    char* url = (char*)news[n].url.c_str();

    printf("\n\nLoading news: %s\n\n", news[n].title.c_str());
    AudioPlayer audioplayer;
    audioplayer.init(url);

    return 0;
}