#include "Observer.h"

void Observable::notify() {
    for (auto obs : interested) {
        obs->update();
    }
}

void Observable::addObserver(Observer *o) {
    interested.push_back(o);
}

void Observable::removeObserver(Observer *o) {
    interested.erase(std::find(interested.begin(), interested.end(), o));
}
