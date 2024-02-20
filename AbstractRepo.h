#pragma once

#include <vector>
#include "activity.h"
#include "Exceptions.h"

using namespace std;

class AbstractRepo {
protected:
    vector<Activity> activities = vector<Activity>();
public:
    virtual ~AbstractRepo() {};

    virtual void addActivity(const Activity &activity) = 0;

    virtual void deleteActivity(const Activity&) = 0;

    virtual void deleteAll() = 0;

    virtual void updateActivity(Activity &activity, const Activity &newActivity) = 0;

    virtual vector<Activity> getAllActivities() = 0;

    virtual int findActivityIndex(const Activity &activity) = 0;

    virtual Activity getActivityByTitle(const string& title) = 0;

    virtual int length() = 0;
};

