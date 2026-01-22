#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// WiFi Credentials
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// Display Pins (ST7920 SW SPI)
#define LCD_CLOCK_PIN 18
#define LCD_DATA_PIN  23
#define LCD_CS_PIN    5
#define LCD_RESET_PIN 16

// Input Pins
#define BUTTON_JUMP_PIN 4
#define BUTTON_DUCK_PIN 2

// Output Pins
#define BUZZER_PIN 25

// Game Physics & Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GROUND_Y 50
#define DINO_X 15
#define DINO_WIDTH 12
#define DINO_HEIGHT 16
#define OBSTACLE_WIDTH 8
#define OBSTACLE_HEIGHT 16
#define JUMP_FORCE -18
#define GRAVITY 2
#define FAST_FALL_GRAVITY 4
#define MIN_DINO_Y 5

// Game Settings
#define INITIAL_GAME_SPEED 5
#define MAX_GAME_SPEED 10
#define SPEED_INCREMENT_INTERVAL 5 // Increase speed every 5 obstacles

#endif
