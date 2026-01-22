#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include <U8g2lib.h>
#include "../config.h"
#include "../game/GameModule.h"

class DisplayModule {
public:
    void init();
    void drawGame(const GameState& state);
    void showStartScreen();
    void showGameOver(const GameState& state);
    void showConnecting();
    
    // Low level access if needed
    void clear() { u8g2.clearBuffer(); }
    void update() { u8g2.sendBuffer(); }

private:
    U8G2_ST7920_128X64_F_SW_SPI u8g2{U8G2_R0, LCD_CLOCK_PIN, LCD_DATA_PIN, LCD_CS_PIN, LCD_RESET_PIN};
    void drawDino(int y);
    void drawObstacle(int x);
};

extern DisplayModule display;

#endif
