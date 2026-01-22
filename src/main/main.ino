#include <Arduino.h>
#include "game/GameModule.h"
#include "hardware/DisplayModule.h"
#include "hardware/SoundModule.h"
#include "network/NetworkModule.h"

void setup() {
    Serial.begin(115200);

    // Initialize modules
    sound.init();
    display.init();
    game.init();
    
    // Connect to WiFi
    display.showConnecting();
    network.init();
    game.setIP(network.getIP());
    
    // Start game
    sound.playStartup();
    display.showStartScreen();
    
    // Wait for initial button press to start
    while (digitalRead(BUTTON_JUMP_PIN) == HIGH) {
        delay(10);
    }
    sound.playJump();
    delay(200);
}

void loop() {
    // 1. Update Network Tasks
    network.update();

    // 2. Update Game State
    game.update();

    // 3. Render Display
    const GameState& state = game.getState();
    if (state.gameOver) {
        display.showGameOver(state);
    } else {
        display.drawGame(state);
    }

    delay(30);
}
