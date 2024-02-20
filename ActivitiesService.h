#pragma once

#include "Validation.h"
#include "ActivitiesRepository.h"
#include "Undo.h"
#include "Observer.h"

#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <map>
#include <memory>

using std::unique_ptr;

typedef bool(*Verify)(Activity, string);

class Service: public Observable {
private:
    AbstractRepo *repository;
    Repository activityList = Repository();
    vector<unique_ptr<UndoAction>> undoList = vector<unique_ptr<UndoAction>>();

public:
    Service(AbstractRepo *repository) : repository{repository} {};

    void addActivityService(string title, string description, string type, int duration, map<string,vector<Activity>>&);

    void deleteActivityService(string title);

    void updateActivityService(string title, string newTitle, string newDescription, string newType, int newDuration);

    Activity findActivityService(string title);

    vector<Activity> filterActivitiesService(string option, string str);

    vector<Activity> filter(Verify, string);

    static bool compareTypeAndDuration(Activity x, Activity y);

    vector<Activity> sortActivitiesService(int option);

    vector<Activity> getAllActivitiesService();

    int countActivitiesByTypeService(string type, map <string, vector<Activity>> mapOfTypes);

    void loadMapOfActivities(const Activity &activity, map<string, vector<Activity>> &mapOfTypes);

    int length();

    void undo();


    // Activity List
    void addActivityToActivityList(const string& title);

    void emptyActivityList();

    void generateRandomActivityList(int numberOfActivities);

    int getActivityListLength();

    vector<Activity> getAllActivityList();
};