#include "ActivitiesFileRepo.h"
#include "ActivitiesRepository.h"
#include <fstream>

void FileRepo::addActivity(const Activity &activity) {
    int index = this->findActivityIndex(activity);
    if (index != -1) {
        throw RepositoryExcepetion("Activity already exists!");
    }
    this->activities.push_back(activity);
    this->writeToFile();
}

void FileRepo::deleteActivity(const Activity &activity) {
    int index = this->findActivityIndex(activity);
    if (index == -1) {
        throw RepositoryExcepetion("Activity does not exist!");
    }
    this->activities.erase(this->activities.begin() + index);
    writeToFile();
}

void FileRepo::deleteAll() {
    this->activities.clear();
    writeToFile();
}

void FileRepo::updateActivity(Activity &activity, const Activity &newActivity) {
    int index = this->findActivityIndex(activity);
    if (index == -1) {
        throw RepositoryExcepetion("Activity does not exist!");
    }
    this->activities[index] = newActivity;
    writeToFile();
}

vector<Activity> FileRepo::getAllActivities() {
    return this->activities;
}

int FileRepo::findActivityIndex(const Activity &activity) {
    auto it = find_if(this->activities.begin(), this->activities.end(), [activity](Activity &activity2) {
        return activity2 == activity;
    });
    if (it == this->activities.end()) {
        return -1;
    }
    return it - this->activities.begin();
}

Activity FileRepo::getActivityByTitle(const string &title) {
    auto it = find_if(this->activities.begin(), this->activities.end(), [title](const Activity &activity) {
        return activity.getTitle() == title;
    });
    if (it == this->activities.end()) {
        throw RepositoryExcepetion("Activity does not exist!");
    }
    return *it;
}

int FileRepo::length() {
    return this->activities.size();
}

void FileRepo::loadFromFile() {
    ifstream fin(this->fileName);
    if (!fin.is_open()) {
        throw RepositoryExcepetion("The file could not be opened!");
    }
    else {
        string title, description, type;
        int duration;
        while (fin >> title >> description >> type >> duration) {
            Activity activity = Activity(title, description, type, duration);
            this->addActivity(activity);
        }
    }
    fin.close();
}

void FileRepo::writeToFile() {
    ofstream out(fileName);
    if (!out.is_open()) {
        throw RepositoryExcepetion("The file could not be opened!");
    }
    else {
        for (auto &act: this->getAllActivities()) {
            out << act.getTitle() << " ";
            out << act.getDescription() << " ";
            out << act.getType() << " ";
            out << act.getDuration() << endl;
        }
        out.close();
    }
}






