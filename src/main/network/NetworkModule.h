#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include <WiFi.h>
#include <WebServer.h>
#include "../game/GameModule.h"

class NetworkModule {
public:
    void init();
    void update(); // Handle client requests
    String getIP();

private:
    WebServer server{80};
    void handleRoot();
    void handleScore();
};

extern NetworkModule network;

#endif
