#include "ActivitiesRepository.h"
#include "DynamicArray.h"


Activity Repository::getActivityByTitle(const string& title) {
    auto it = find_if(this->activities.begin(), this->activities.end(), [title](const Activity &activity) {
        return activity.getTitle() == title;
    });
    if (it == this->activities.end()) {
        throw RepositoryExcepetion("Activity does not exist!");
    }
    return *it;
}

vector<Activity> Repository::getAllActivities() {
    return this->activities;
}

int Repository::length() {
    return this->activities.size();
}

void Repository::addActivity(const Activity &activity) {
    int index = findActivityIndex(activity);
    if (index != -1) {
        throw RepositoryExcepetion("Activity already exists!");
    }
    this->activities.push_back(activity);
}

void Repository::deleteActivity(const Activity &activity) {
    int index = findActivityIndex(activity);
    if (index == -1) {
        throw RepositoryExcepetion("Activity does not exist!");
    }
    this->activities.erase(this->activities.begin() + index);
}

void Repository::deleteAll() {
    this->activities.clear();
}

void Repository::updateActivity(Activity &activity,const Activity &newActivity) {
    int index = findActivityIndex(activity);
    if (index == -1) {
        throw RepositoryExcepetion("Activity does not exist!");
    }
    this->activities[index] = newActivity;
}

int Repository::findActivityIndex(const Activity &activity) {
    auto it = find_if(this->activities.begin(), this->activities.end(), [activity](Activity &activity2) {
            return activity2 == activity;
        });
    if (it == this->activities.end()) {
        return -1;
    }
    return it - this->activities.begin();
}

Repository::~Repository() {
    this->activities.clear();
}

