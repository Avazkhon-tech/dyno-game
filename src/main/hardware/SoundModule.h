#ifndef SOUND_MODULE_H
#define SOUND_MODULE_H

#include <Arduino.h>
#include "../config.h"

class SoundModule {
public:
    void init();
    void playJump();
    void playCollision();
    void playScore();
    void playStartup();
    void playMilestone();

private:
    void playTone(int frequency, int duration);
};

extern SoundModule sound;

#endif
