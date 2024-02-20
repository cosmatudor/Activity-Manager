#include "ActivitiesService.h"
#include <algorithm>

void Service::addActivityService(string title, string description, string type, int duration, map<string,vector<Activity>>& mapOfTypes) {
    Activity activity = Activity(title, description, type, duration);
    Validation::validate(activity);
    this->repository->addActivity(activity);

    // Add activity to map of types
    loadMapOfActivities(activity, mapOfTypes);

    // Action for undo
    undoList.push_back(make_unique<AddUndo>(repository, activity));
}

void Service::deleteActivityService(string title) {
    Activity activity = this->repository->getActivityByTitle(title);
    Validation::validate(activity);
    this->repository->deleteActivity(activity);

    // Action for undo
    undoList.push_back(make_unique<DeleteUndo>(repository, activity));
}

void Service::updateActivityService(string title, string newTitle, string newDescription, string newType,
                                    int newDuration) {
    Activity newActivity = Activity{newTitle, newDescription, newType, newDuration};
    Validation::validate(newActivity);
    Activity activity = this->repository->getActivityByTitle(title);
    this->repository->updateActivity(activity, newActivity);

    // Action for undo
    undoList.push_back(make_unique<UpdateUndo>(repository, activity, newActivity));
}


Activity Service::findActivityService(string title) {
    Activity activity = this->repository->getActivityByTitle(title);
    return activity;
}

int Service::length() {
    return this->repository->length();
}

vector<Activity> Service::getAllActivitiesService() {
    return this->repository->getAllActivities();
}


bool Service::compareTypeAndDuration(Activity x, Activity y) {
    return (x.getType() < y.getType()) || (x.getType() == y.getType() && x.getDuration() < y.getDuration());
}

vector<Activity> Service::filter(Verify verify, string str) {
    vector array = vector<Activity>();
    auto activities = this->repository->getAllActivities();
    copy_if(activities.begin(), activities.end(), back_inserter(array), [verify, str](Activity activity) {
        return verify(activity, str);
    });
    return array;
}

vector<Activity> Service::filterActivitiesService(string option, string str) {
    if (option == "description") {
        return this->filter([](Activity activity, string str) {return activity.getDescription() == str;}, str);
    }
    else if (option == "type") {
        return this->filter([](Activity activity, string str) {return activity.getType() == str;}, str);
    }
    return {};
}


vector<Activity> Service::sortActivitiesService(int option) {
    vector array = this->repository->getAllActivities();
    if (option == 1) {
        std::sort(array.begin(), array.end(), [](Activity x, Activity y) { return x.getTitle() < y.getTitle(); });
    }
    else if (option == 2) {
        std::sort(array.begin(), array.end(), [](Activity x, Activity y) { return x.getDescription() < y.getDescription(); });
    }
    else if (option == 3) {
        std::sort(array.begin(), array.end(), compareTypeAndDuration);
    }
    return array;
}

void Service::addActivityToActivityList(const string& title) {
    auto activity = this->repository->getActivityByTitle(title);
    this->activityList.addActivity(activity);
    this->notify();
}

void Service::emptyActivityList() {
    this->activityList.deleteAll();
    this->notify();
}

int Service::getActivityListLength() {
    return this->activityList.length();
}

void Service::generateRandomActivityList(int numberOfActivities) {
    auto copyRepo = this->repository->getAllActivities();

    // shuffle 'copyRepo' array
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(copyRepo.begin(), copyRepo.end(), std::default_random_engine(seed));

    // first we empty the list
    Service::emptyActivityList();

    for (unsigned int i = 0; const auto& activity : copyRepo) {
        if (i < numberOfActivities) {
            this->activityList.addActivity(activity);
            i++;
        } else {
            break;
        }
    }
    this->notify();
}

vector<Activity> Service::getAllActivityList() {
    return this->activityList.getAllActivities();
}

void Service::undo() {
    if (undoList.empty()) {
        throw RepositoryExcepetion("No more operations to be undone!");
    }
    undoList.back()->doUndo();
    undoList.pop_back();
}

int Service::countActivitiesByTypeService(string type, map <string, vector<Activity>> mapOfTypes) {
    return mapOfTypes[type].size();
}

void Service::loadMapOfActivities(const Activity &activity, map<string, vector<Activity>> &mapOfTypes) {
    auto type = activity.getType();
    // we add in the map of types too
    // first we check if the type doesn't exist in the map
    if (mapOfTypes.find(type) == mapOfTypes.end()) {
        // if it doesn't exist, we add it
        vector<Activity> activities;
        activities.push_back(activity);
        mapOfTypes.insert(pair<string, vector<Activity>>(type, activities));
    }
    else {
        // if it exists, we add the activity to the vector of activities
        mapOfTypes[type].push_back(activity);
    }
}





