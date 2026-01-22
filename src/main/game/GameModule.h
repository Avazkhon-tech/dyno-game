#ifndef GAME_MODULE_H
#define GAME_MODULE_H

#include <Arduino.h>
#include "../config.h"

struct GameState {
    int dinoY;
    int dinoVelocity;
    bool isJumping;
    bool fastFalling;
    int obstacleX;
    int score;
    int highScore;
    int obstaclesPassed;
    int gameSpeed;
    bool gameOver;
    bool obstacleWasBehindDino;
    String ipAddress;
};

class GameModule {
public:
    GameModule();
    void init();
    void update();
    void reset();
    bool checkCollision();
    
    // Getters for state
    const GameState& getState() const { return state; 
        }
    void setIP(String ip) { state.ipAddress = ip; }

private:
    GameState state;
    void handlePhysics();
    void handleObstacles();
    void handleScoring();
};

extern GameModule game;

#endif
