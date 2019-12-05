#pragma once

#include <vector>
#include <string>
#include <map>

typedef struct {
    std::string title;
    std::string url;
} News;

typedef struct {
    std::string id;
    std::string title;   
} Channel;

class NewsPuller {
private:
    std::vector<Channel> channels;
    std::vector<Channel> avaiableChannels;
    std::map<std::string, std::vector<News>> mNews; //mNews[channel id] --> news list  

    void pullChannelFromNetworkToFile();
    void loadChannelFromFile();
    void loadChannel();
    
public:
    void init();
    std::vector<Channel> getChannels();
    std::vector<News> getNews(std::string channleId);

    void pullNews(std::string channelId);
};