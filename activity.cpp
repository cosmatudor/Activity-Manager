#include "activity.h"

// Default constructor
Activity::Activity() {
    this->title = "";
    this->description = "";
    this->type = "";
    this->duration = 0;
}

// Constructor with parameters
Activity::Activity(string title, string description, string type, int duration) {
    this->title = title;
    this->description = description;
    this->type = type;
    this->duration = duration;
}

// Copy constructor
Activity::Activity(const Activity &ot) {
    title = ot.title;
    description = ot.description;
    type = ot.type;
    duration = ot.duration;
}

// Getters
string Activity::getTitle() const {
    return this->title;
}

string Activity::getDescription() const {
    return this->description;
}

string Activity::getType() const {
    return this->type;
}

int Activity::getDuration() const {
    return this->duration;
}

// Operators overload
 bool Activity::operator==(const Activity &activity) {
    return this->title == activity.title;
}

Activity& Activity::operator=(const Activity &activity) {
    this->title = activity.title;
    this->description = activity.description;
    this->type = activity.type;
    this->duration = activity.duration;
    return *this;
}


