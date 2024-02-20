#include "ActivitiesService.h"
#include <map>

class UI {
private:
    Service& service;

    static void printMenu();

    void addActivityCommand(map<string,vector<Activity>>&);

    void deleteActivityCommand();

    void updateActivityCommand();

    void findActivityCommand();

    void filterActivitiesCommand();

    void sortActivitiesCommand();

    void undoCommand();

    static void printMapCommand(map<string,vector<Activity>>&);

    void emptyListCommand();

    void addActivityInListCommand();

    void generateRandomListCommand();

    void printAllActivities(const vector<Activity>& activities);
public:
    UI(Service &service): service{ service } {};

    void run();
};