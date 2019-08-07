#include "Timer.h"

Timer::Timer(unsigned long duration) {
    timerDuration = duration;
}

void Timer::update() {
    lastUpdate = millis();
}

bool Timer::timeHasPassed() {
    if(millis() - lastUpdate > timerDuration) {
        update();
        return true;
    }
    return false;
}

bool Timer::timeHasPassedNoUpdate() {
    return millis() - lastUpdate > timerDuration;
}
