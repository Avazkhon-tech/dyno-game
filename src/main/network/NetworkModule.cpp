#include "NetworkModule.h"

const char* WIFI_SSID = "13 Pro";
const char* WIFI_PASSWORD = "12345678";

void NetworkModule::init() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        
        server.on("/", [this]() { this->handleRoot(); });
        server.on("/score", [this]() { this->handleScore(); });
        server.begin();
    }
}

void NetworkModule::update() {
    server.handleClient();
}

String NetworkModule::getIP() {
    if (WiFi.status() == WL_CONNECTED) {
        return WiFi.localIP().toString();
    }
    return "No Connection";
}

void NetworkModule::handleRoot() {
    const GameState& state = game.getState();
    String html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<title>Dino Game Score</title>";
    html += "<style>body{font-family:Arial,sans-serif;text-align:center;padding:50px;background:#f0f0f0;}";
    html += ".score-box{background:white;padding:30px;border-radius:10px;box-shadow:0 2px 10px rgba(0,0,0,0.1);max-width:400px;margin:0 auto;}";
    html += ".score{font-size:48px;color:#4CAF50;font-weight:bold;margin:20px 0;}";
    html += ".label{font-size:18px;color:#666;}";
    html += "button{background:#4CAF50;color:white;border:none;padding:15px 30px;font-size:16px;border-radius:5px;cursor:pointer;margin-top:20px;}</style>";
    html += "<script>setInterval(()=>location.reload(), 5000);</script>";
    html += "</head><body><div class='score-box'>";
    html += "<h1>🦖 Dino Game</h1>";
    html += "<div class='label'>Current Score</div><div class='score'>" + String(state.score) + "</div>";
    html += "<div class='label'>High Score</div><div class='score'>" + String(state.highScore) + "</div>";
    html += "<div class='label'>Obstacles Passed: " + String(state.obstaclesPassed) + "</div>";
    html += "<div class='label'>Status: " + String(state.gameOver ? "Game Over" : "Playing") + "</div>";
    html += "<button onclick='location.reload()'>Refresh</button>";
    html += "</div></body></html>";
    
    server.send(200, "text/html", html);
}

void NetworkModule::handleScore() {
    const GameState& state = game.getState();
    String json = "{";
    json += "\"score\":" + String(state.score) + ",";
    json += "\"highScore\":" + String(state.highScore) + ",";
    json += "\"obstaclesPassed\":" + String(state.obstaclesPassed) + ",";
    json += "\"gameOver\":" + String(state.gameOver ? "true" : "false");
    json += "}";
    
    server.send(200, "application/json", json);
}

NetworkModule network;
