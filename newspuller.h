#pragma once
#include <vector>
#include <string>

typedef struct {
    std::string id;
    std::string name;
} Channel;

class NewsPuller {
private:
    std::vector<Channel> channels;

    void pullChannelFromNetworkToFile();
    void loadChannelFromFile();

public:
    void loadChannel();

};