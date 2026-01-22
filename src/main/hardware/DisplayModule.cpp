#include "DisplayModule.h"

void DisplayModule::init() {
    u8g2.begin();
    u8g2.setContrast(255);
}

void DisplayModule::drawGame(const GameState& state) {
    u8g2.clearBuffer();
    
    // Draw ground
    u8g2.drawHLine(0, GROUND_Y + DINO_HEIGHT, SCREEN_WIDTH);
    
    // Draw dino
    drawDino(state.dinoY);
    
    // Draw obstacle
    drawObstacle(state.obstacleX);
    
    // UI - Scores
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawStr(70, 10, "Score:");
    u8g2.setCursor(106, 10);
    u8g2.print(state.score);
    
    u8g2.drawStr(70, 19, "Best:");
    u8g2.setCursor(100, 19);
    u8g2.print(state.highScore);
    
    u8g2.sendBuffer();
}

void DisplayModule::drawDino(int y) {
    u8g2.drawFrame(DINO_X, y, DINO_WIDTH, DINO_HEIGHT);
    u8g2.drawBox(DINO_X + 2, y + 2, DINO_WIDTH - 4, DINO_HEIGHT - 4);
    // Legs
    u8g2.drawVLine(DINO_X + 3, y + DINO_HEIGHT, 2);
    u8g2.drawVLine(DINO_X + 8, y + DINO_HEIGHT, 2);
}

void DisplayModule::drawObstacle(int x) {
    u8g2.drawBox(x, GROUND_Y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    u8g2.drawVLine(x + 2, GROUND_Y - 4, 4);
    u8g2.drawVLine(x + 6, GROUND_Y - 4, 4);
}

void DisplayModule::showStartScreen() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(20, 20, "DINO GAME");
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawStr(32, 38, "Press button");
    u8g2.drawStr(41, 50, "to start!");
    u8g2.sendBuffer();
}

void DisplayModule::showGameOver(const GameState& state) {
    u8g2.clearBuffer();
    
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(15, 12, "GAME OVER");
    
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawStr(5, 26, "Score:");
    u8g2.setCursor(45, 26);
    u8g2.print(state.score);
    
    u8g2.drawStr(5, 36, "Best:");
    u8g2.setCursor(45, 36);
    u8g2.print(state.highScore);
    
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(4, 48, "IP:");
    u8g2.setCursor(15, 48);
    u8g2.print(state.ipAddress);
    
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawStr(5, 60, "Press to restart");
    
    u8g2.sendBuffer();
}

void DisplayModule::showConnecting() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawStr(10, 20, "Connecting WiFi...");
    u8g2.sendBuffer();
}

DisplayModule display;
