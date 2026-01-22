#include "SoundModule.h"

void SoundModule::init() {
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void SoundModule::playTone(int frequency, int duration) {
    tone(BUZZER_PIN, frequency, duration);
    delay(duration);
    noTone(BUZZER_PIN);
}

void SoundModule::playJump() {
    playTone(600, 50);
}

void SoundModule::playCollision() {
    playTone(800, 100);
    playTone(600, 100);
    playTone(400, 100);
    playTone(200, 200);
}

void SoundModule::playScore() {
    playTone(1000, 30);
}

void SoundModule::playStartup() {
    playTone(523, 100);  // C
    playTone(659, 100);  // E
    playTone(784, 150);  // G
}

void SoundModule::playMilestone() {
    playTone(659, 80);   // E
    playTone(784, 80);   // G
    playTone(988, 80);   // B
    playTone(1047, 150); // C (high)
}

SoundModule sound;
