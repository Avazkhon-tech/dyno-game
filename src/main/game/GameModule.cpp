#include "GameModule.h"
#include "../hardware/SoundModule.h"

GameModule::GameModule() {
    reset();
}

void GameModule::init() {
    pinMode(BUTTON_JUMP_PIN, INPUT_PULLUP);
    pinMode(BUTTON_DUCK_PIN, INPUT_PULLUP);
    reset();
}

void GameModule::reset() {
    state.dinoY = GROUND_Y;
    state.dinoVelocity = 0;
    state.isJumping = false;
    state.fastFalling = false;
    state.obstacleX = SCREEN_WIDTH;
    state.score = 0;
    state.obstaclesPassed = 0;
    state.gameSpeed = INITIAL_GAME_SPEED;
    state.gameOver = false;
    state.obstacleWasBehindDino = false;
}

void GameModule::update() {
    if (state.gameOver) {
        if (digitalRead(BUTTON_JUMP_PIN) == LOW) {
            sound.playJump();
            reset();
            delay(200);
        }
        return;
    }

    handlePhysics();
    handleObstacles();
    handleScoring();

    if (checkCollision()) {
        state.gameOver = true;
        sound.playCollision();
        if (state.score > state.highScore) {
            state.highScore = state.score;
        }
    }
}

void GameModule::handlePhysics() {
    // Jump trigger
    if (digitalRead(BUTTON_JUMP_PIN) == LOW && !state.isJumping) {
        state.isJumping = true;
        state.dinoVelocity = JUMP_FORCE;
        state.fastFalling = false;
        sound.playJump();
    }

    // Fast fall trigger
    if (digitalRead(BUTTON_DUCK_PIN) == LOW && state.isJumping && !state.fastFalling) {
        state.dinoVelocity = -JUMP_FORCE; // Force down
        state.fastFalling = true;
    }

    // Gravity and movement
    if (state.isJumping) {
        state.dinoY += state.dinoVelocity;
        state.dinoVelocity += state.fastFalling ? FAST_FALL_GRAVITY : GRAVITY;

        if (state.dinoY < MIN_DINO_Y) {
            state.dinoY = MIN_DINO_Y;
            state.dinoVelocity = 0;
        }

        if (state.dinoY >= GROUND_Y) {
            state.dinoY = GROUND_Y;
            state.isJumping = false;
            state.fastFalling = false;
            state.dinoVelocity = 0;
        }
    }
}

void GameModule::handleObstacles() {
    state.obstacleX -= state.gameSpeed;
    if (state.obstacleX < -OBSTACLE_WIDTH) {
        state.obstacleX = SCREEN_WIDTH;
        state.obstacleWasBehindDino = false;
    }
}

void GameModule::handleScoring() {
    if (state.obstacleX + OBSTACLE_WIDTH < DINO_X && !state.obstacleWasBehindDino) {
        state.obstaclesPassed++;
        state.score = state.obstaclesPassed * 10;
        state.obstacleWasBehindDino = true;
        sound.playScore();

        // Speed increase and milestone sound
        if (state.score % 100 == 0 && state.score > 0) {
            sound.playMilestone();
        }

        if (state.obstaclesPassed % SPEED_INCREMENT_INTERVAL == 0 && state.gameSpeed < MAX_GAME_SPEED) {
            state.gameSpeed++;
        }
    }
}

bool GameModule::checkCollision() {
    bool horizontalMatch = (state.obstacleX < DINO_X + DINO_WIDTH && state.obstacleX + OBSTACLE_WIDTH > DINO_X);
    bool verticalMatch = (state.dinoY + DINO_HEIGHT >= GROUND_Y);
    return horizontalMatch && verticalMatch;
}

GameModule game;
