#include "newspuller.h"
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

void NewsPuller::pullChannelFromNetworkToFile(){
    CURL *curl = curl_easy_init();
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://learningenglish.voanews.com/podcasts");
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2);

    FILE *fp = fopen(".channel_html", "w+");
    FILE *fp2 = fopen(".channel_list", "w+");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    CURLcode res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    fclose(fp);

    size_t n = 1024;
    char *buff = (char*)malloc(n);
    
    char *sub1 = "<a class=\"handler\" href=\"/z/";
    int len1 = strlen(sub1);
    char *p1 = NULL, *p2 = NULL, *p3 = NULL;

    char id[5], title[256];

    fp = fopen(".channel_html", "r");

    while (getline((char**)&buff, &n, fp) != -1) {
        p1 = strstr(buff, sub1);

        if (p1) {
            // printf("%s\n", p1);
            strncpy(id, p1+len1, 4);

            if (id[3] == '\"')
                id[3]=0;
            else 
                id[4]=0;

            p2 = strchr(p1, '>');
            p3 = strchr(p2, '<');

            int len = p3-p2-1;
            strncpy(title, p2+1, p3-p2-1);
            title[len] = 0;
            
            fprintf(fp2, "%s\n", id);
            fprintf(fp2, "%s\n", title);
        }
    }

    free(buff);
    fclose(fp);
    fclose(fp2);
}

void NewsPuller::loadChannelFromFile() {
    FILE* fp = fopen(".channel_list", "r");
    size_t n1 = 5, n2 = 256, ret;

    char *id = (char*) malloc(n1);
    int len1, len2;
    char *title = (char*) malloc(n2);    

    while (1) {
        if (getline(&id, &n1, fp) <= 0)
            break;

        len1 = strlen(id);
        if (id[len1-1] == '\n')
            id[len1-1] = 0;

        // printf("%s\n", id);

        if (getline(&title, &n2, fp) <= 0)
            break;

        len2 = strlen(title);
        if (title[len2-1] == '\n')
            title[len2-1] = 0;

        // printf("%s\n", title);

        std::string sId(id);
        std::string sTitle(title);

        channels.push_back({sId, sTitle});        
    }

    fclose(fp);
    free(id);
    free(title);
}

void NewsPuller::loadChannel() {
    FILE *fp = fopen(".channel_list", "r");

    if (!fp) {
        pullChannelFromNetworkToFile();
    }

    loadChannelFromFile();
}

int main(int argc, char *argv[]) {
    NewsPuller puller;
    puller.loadChannel();

    return 0;
}