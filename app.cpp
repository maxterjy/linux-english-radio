#include <stdio.h>
#include <pthread.h>
#include "audioplayer.h"
#include "newspuller.h"
#include <unistd.h>

void* playAudio(void *arg);

typedef struct {
    AudioPlayer *player;
    char* url;
} AudioArg;

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    NewsPuller *newsPuller = new NewsPuller();
    newsPuller->init();

    std::vector<Channel> channels = newsPuller->getChannels();

    int numChannel = channels.size();
    printf("\n\n%16c--- LIST OF CHANNEL ---\n\n", ' ');
    for(int i = 0; i < numChannel; i++) {
        printf("\t%d: %-32s \t %ld news\n\n", i, channels[i].title.c_str(), newsPuller->getNews(channels[i].id).size());
    }

    printf("\nPress a number from 0 to %d select channel: ", numChannel-1);

    int n;
    scanf("%d", &n);
    if (n < 0 || n >= numChannel) {
        printf("Invalid number\n\n");
        return -1;
    }

    printf("\n\nSelected: %s\n", channels[n].title.c_str());
    
    std::string channelID = channels[n].id;
    std::vector<News> news = newsPuller->getNews(channelID);
    int numNews = news.size();

    printf("\n\n%16c--- LIST OF NEWS ---\n\n", ' ');
    for(int i = 0; i < numNews; i++) {
        printf("\t%d: %s\n\n", i, news[i].title.c_str());
    }

    printf("\nPress a number from 0 to %d select news: ", numNews-1);
    scanf("%d", &n);
    if (n < 0 || n >= numNews){
        printf("Invalid number\n\n");
        return -1;
    }

    char* url = (char*)news[n].url.c_str();

    printf("\n\nSelected: %s\n\n", news[n].title.c_str());


    AudioPlayer *audioPlayer = new AudioPlayer();

    pthread_t audioThread;
    AudioArg *data = new AudioArg();
    data->player = audioPlayer;
    data->url = url;

    pthread_create(&audioThread, NULL, playAudio, (void*)data);


    printf("\tLoading "); fflush(stdout);
    
    while (1) {
        sleep(1);
        write(STDIN_FILENO, ". ", 2);

        if (audioPlayer->isReady()) {
            printf("Ready\n\n");
            break;
        }
    }
    
    char msg[32];

    while (1) {      
        sleep(1);  
        sprintf(msg, "\r\tPlaying: %s / %s", audioPlayer->getCurrentTime(), audioPlayer->getDuration());
        write(STDIN_FILENO, msg, strlen(msg));
        

        if (audioPlayer->isFinished()) {
            
            break;
        }
    }
    printf("\n\tFinished\n");


    pthread_join(audioThread, NULL);

    delete data;
    delete newsPuller;
    delete audioPlayer;

    return 0;    
}

void* playAudio(void *arg) {
    AudioArg *data = (AudioArg*)arg;
    AudioPlayer *player = data->player;
    char* url = data->url;

    player->init(url);
}