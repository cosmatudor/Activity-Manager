#pragma once

#include <vector>
#include "activity.h"
#include "Exceptions.h"
#include "AbstractRepo.h"


using namespace std;

class Repository: public AbstractRepo {
public:
    Repository() = default;

    ~Repository() override;

    void addActivity(const Activity &activity) override;

    void deleteActivity(const Activity&) override;

    void deleteAll()  override;

    void updateActivity(Activity &activity, const Activity &newActivity) override;

    vector<Activity> getAllActivities() override;

    int findActivityIndex(const Activity &activity) override;

    Activity getActivityByTitle(const string& title) override;

    int length() override;
};

