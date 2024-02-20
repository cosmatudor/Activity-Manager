#include "Tests.h"
#include <cassert>
#include <map>

void Tests::testAll() {
    testDomain(); cout << "Domain tests run successfully!\n";
    testRepository(); cout << "Repository tests run successfully!\n";
    testService(); cout << "Service tests run successfully!\n";
}

void Tests::testDomain() {
    Activity activity = Activity{"baschet", "smecher", "sport", 90};
    assert(activity.getTitle() == "baschet");
    assert(activity.getDescription() == "smecher");
    assert(activity.getType() == "sport");
    assert(activity.getDuration() == 90);

    Activity activity2 = Activity{"baschet", "smecher", "sport", 90};
    assert(activity == activity2);

    Activity activity3 = Activity();
    assert(activity3.getTitle() == "");
    assert(activity3.getDescription() == "");
    assert(activity3.getType() == "");
    assert(activity3.getDuration() == 0);
}

void Tests::testRepository() {
    Repository repo = Repository();

    Activity activity = Activity{"baschet", "smecher", "sport", 90};
    repo.addActivity(activity);
    try {
        repo.addActivity(activity);
        assert(false);
    } catch (RepositoryExcepetion &excepetion) {
        assert(true);
    }
    assert(repo.length() == 1);

    Activity newActivity = Activity{"fotbal", "naspa", "sport", 120};
    Activity getActivity = repo.getActivityByTitle("baschet");
    repo.updateActivity(getActivity, newActivity);
    auto otherActivity = repo.getAllActivities()[0];
    assert(otherActivity.getTitle() == "fotbal");
    assert(otherActivity.getDescription() == "naspa");
    assert(otherActivity.getType() == "sport");
    assert(otherActivity.getDuration() == 120);
    try {
        Activity getActivity = Activity{"plimbat", "naspa", "sport", 30};
        repo.updateActivity(getActivity, newActivity);
        assert(false);
    } catch (RepositoryExcepetion &excepetion) {
        assert(true);
    }

    assert(repo.findActivityIndex(repo.getAllActivities()[0]) == 0);
    repo.deleteActivity(newActivity);
    assert(repo.length() == 0);
    try {
        repo.deleteActivity(activity);
        assert(false);
    } catch (RepositoryExcepetion &excepetion) {
        assert(true);
    }

    try {
        repo.getActivityByTitle("fotbal");
        assert(false);
    } catch (RepositoryExcepetion &excepetion) {
        assert(true);
    }
}

void Tests::testService() {
/*
    Repository repo = Repository();
    Service service = Service(repo);
    map<string,vector<Activity>> mapOfTypes;

    service.addActivityService("baschet", "smecher", "sport", 90, mapOfTypes);
    assert(service.length() == 1);

    service.updateActivityService("baschet", "fotbal", "naspa", "sport", 120);
    auto otherActivity = service.getAllActivitiesService()[0];
    assert(otherActivity.getTitle() == "fotbal");
    assert(otherActivity.getDescription() == "naspa");
    assert(otherActivity.getType() == "sport");
    assert(otherActivity.getDuration() == 120);

    service.deleteActivityService("fotbal");
    assert(service.length() == 0);

    // tests for findActivityService()
    service.addActivityService("baschet", "smecher", "sport", 90, mapOfTypes);
    Activity activity = service.findActivityService("baschet");
    assert(activity.getTitle() == "baschet");
    assert(activity.getDescription() == "smecher");
    assert(activity.getType() == "sport");
    assert(activity.getDuration() == 90);

    // tests for filter()
    service.addActivityService("fotbal", "naspa", "b", 120, mapOfTypes);
    service.addActivityService("plimbat", "lejer", "a", 30, mapOfTypes);
    service.addActivityService("tenis", "lejer", "b", 60, mapOfTypes);
    service.addActivityService("volei", "lejer", "a", 60, mapOfTypes);
    service.addActivityService("handbal", "naspa", "a", 60, mapOfTypes);
    service.addActivityService("pingpong", "naspa", "b", 60, mapOfTypes);
    //service.sortActivitiesService(3);

    vector<Activity> array1 = service.filter([](Activity activity, string str) { return activity.getType() == str; }, "a");
    assert(array1.size() == 3);
    assert(array1[0].getTitle() == "plimbat");
    assert(array1[1].getTitle() == "volei");
    assert(array1[2].getTitle() == "handbal");
    //service.sortActivitiesService(1);

    vector<Activity> array2 = service.filter([](Activity activity, string str) { return activity.getDescription() == str; }, "naspa");
    assert(array2.size() == 3);
    assert(array2[0].getTitle() == "fotbal");
    assert(array2[1].getTitle() == "handbal");
    assert(array2[2].getTitle() == "pingpong");
    //service.sortActivitiesService(2);


    // tests for filterActivitiesService
    vector<Activity> array3 = service.filterActivitiesService("type", "a");
    assert(array3[0].getTitle() == array1[0].getTitle());

    vector<Activity> array4 = service.filterActivitiesService("description", "naspa");
    assert(array4[0].getTitle() == array2[0].getTitle());

    vector<Activity> array5 = service.filterActivitiesService("", "a");
    assert(array5.empty());

    // test for compareTypeAndDuration()
    Activity activity1 = Activity{"baschet", "smecher", "sport", 90};
    Activity activity2 = Activity{"fotbal", "naspa", "sport", 120};
    assert(service.compareTypeAndDuration(activity1, activity2) == true);
    assert(service.compareTypeAndDuration(activity2, activity1) == false);


    // tests for sortActivitiesService()
    auto sortedArray = service.sortActivitiesService(1);
    assert(sortedArray[0].getTitle() == "baschet");
    assert(sortedArray[1].getTitle() == "fotbal");
    assert(sortedArray[2].getTitle() == "handbal");
    assert(sortedArray[3].getTitle() == "pingpong");
    assert(sortedArray[4].getTitle() == "plimbat");
    assert(sortedArray[5].getTitle() == "tenis");
    assert(sortedArray[6].getTitle() == "volei");

    sortedArray = service.sortActivitiesService(2);
    assert(sortedArray[0].getTitle() == "plimbat");
    assert(sortedArray[1].getTitle() == "tenis");
    assert(sortedArray[2].getTitle() == "volei");
    assert(sortedArray[3].getTitle() == "fotbal");
    assert(sortedArray[4].getTitle() == "handbal");
    assert(sortedArray[5].getTitle() == "pingpong");
    assert(sortedArray[6].getTitle() == "baschet");

    sortedArray = service.sortActivitiesService(3);
    assert(sortedArray[0].getTitle() == "plimbat");
    assert(sortedArray[1].getTitle() == "volei");
    assert(sortedArray[2].getTitle() == "handbal");
    assert(sortedArray[3].getTitle() == "tenis");
    assert(sortedArray[4].getTitle() == "pingpong");
    assert(sortedArray[5].getTitle() == "fotbal");
    assert(sortedArray[6].getTitle() == "baschet");
*/
}