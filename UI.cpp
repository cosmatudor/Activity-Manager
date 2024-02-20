#include "UI.h"
#include <iostream>
#include <map>

using namespace std;

void UI::printMenu() {
    cout << "\n";
    cout << "1. Add activity\n"; //done
    cout << "2. Delete activity\n"; //done
    cout << "3. Update activity\n"; //done
    cout << "4. Find activity\n"; //TODO
    cout << "5. Filter activities\n";//done
    cout << "6. Sort activities\n";// done
    cout << "7. Map of activities by type\n"; //no
    cout << "---Menu for Activity List---\n"; //no
    cout << "8. Empty list of activities\n"; //no
    cout << "9. Add activity in list\n"; //no
    cout << "10. Generate a random list\n"; //no
    cout << "----------------------------\n";
    cout << "11. Undo\n"; // done
    cout << "0. Exit\n"; //done
    cout << "\n";
}

void UI::printAllActivities(const vector<Activity>& list) {
    cout << "\n";
    cout << "All activities: \n";
    for (const auto& activity : list) {
        cout << activity.getTitle() << " | " << activity.getDescription() << " | " << activity.getType() << " | " << activity.getDuration() << '\n';
    }
    cout << "-------------------------------------\n";
    cout << "Activity List: \n";
    auto list2 = this->service.getAllActivityList();
    for (const auto& activity : list2) {
        cout << activity.getTitle() << " | " << activity.getDescription() << " | " << activity.getType() << " | " << activity.getDuration() << '\n';
    }
}

void UI::addActivityCommand(map<string,vector<Activity>>& mapOfTypes) {
    string title, description, type;
    int duration;
    cout << "Title: "; cin >> title;
    cout << "Description: "; cin >> description;
    cout << "Type: "; cin >> type;
    cout << "Duration: "; cin >> duration;
    try {
        this->service.addActivityService(title, description, type, duration, mapOfTypes);
        this->printAllActivities(this->service.getAllActivitiesService());
    } catch (RepositoryExcepetion &err) {
        cout << err << '\n';
    } catch (ValidationException &err) {
        cout << err.getMessage() << '\n';
    }
}

void UI::deleteActivityCommand() {
    string title;
    cout << "Title: "; cin >> title;
    try {
        this->service.deleteActivityService(title);
        this->printAllActivities(this->service.getAllActivitiesService());
    } catch (RepositoryExcepetion &err) {
        cout << err << '\n';
    } catch (ValidationException &err) {
        cout << err.getMessage() << '\n';
    }
}

void UI::updateActivityCommand() {
    string title, newTitle, newDescription, newType;
    int newDuration;
    cout << "Title of activity to change: "; cin >> title;
    cout << "New title: "; cin >> newTitle;
    cout << "New description: "; cin >> newDescription;
    cout << "New type: "; cin >> newType;
    cout << "New duration: "; cin >> newDuration;
    try {
        this->service.updateActivityService(title, newTitle, newDescription, newType, newDuration);
        this->printAllActivities(this->service.getAllActivitiesService());
    } catch (RepositoryExcepetion &err) {
        cout << err << '\n';
    } catch (ValidationException &err) {
        cout << err.getMessage() << '\n';
    }
}

void UI::findActivityCommand() {
    string title;
    cout << "Title: "; cin >> title;
    try {
        Activity a = this->service.findActivityService(title);
        cout << a.getTitle() << " | " << a.getDescription() << " | " << a.getType() << " | " << a.getDuration() << '\n';
    } catch (RepositoryExcepetion &err) {
        cout << err << '\n';
    }
}

void UI::filterActivitiesCommand() {
    string option;
    cout << "Filter activities by (description/type): ";
    try {
        cin >> option;
        if (option == "description") {
            cout << "Description: ";
        } else if (option == "type") {
            cout << "Type: ";
        } else {
            throw UIException("You must choose between description or type!");
        }

        string str; cin >> str;
        auto array = this->service.filterActivitiesService(option, str);
        this->printAllActivities(array);

    } catch (UIException &err) {
        cout << err.getMessage() << '\n';
    } catch (RepositoryExcepetion &err) {
        cout << err << '\n';
    }
}

void UI::sortActivitiesCommand() {
    string option;
    cout << "Sort activities by: 1. Title | 2. Description | 3. Type + Duration\nOption(#): ";
    cin >> option;
    int optionInt = stoi(option);
    try {
        if (option != "1" && option != "2" && option != "3") {
            throw UIException("You must choose between 1, 2 or 3!");
        }
        auto array = this->service.sortActivitiesService(optionInt);
        this->printAllActivities(array);
    } catch (UIException &err) {
        cout << err.getMessage() << '\n';
    } catch (RepositoryExcepetion &err) {
        cout << err << '\n';
    }
}

void UI::printMapCommand(map<string,vector<Activity>>& mapOfTypes) {
    auto it = mapOfTypes.begin();
    while (it != mapOfTypes.end())
    {
        cout << it->first << " => ";
        auto list = it->second;
        for (const auto& item : list) {
            cout << item.getTitle() << " ; ";
        }
        cout << '\n';
        ++it;
    }
}

void UI::emptyListCommand() {
    this->service.emptyActivityList();
    cout << "Number of activities reduced to 0.\n";
}

void UI::addActivityInListCommand() {
    cout << "Select a title of activity: ";
    string title; cin >> title;
    try {
        this->service.addActivityToActivityList(title);
        cout << "Current number of activities in Activity List: " << this->service.getActivityListLength() << "\n";
    } catch(RepositoryExcepetion& err) {
        cout << err << '\n';
    }
}

void UI::generateRandomListCommand() {
    cout << "Number of random activities: ";
    int nr; cin >> nr;
    this->service.generateRandomActivityList(nr);
    cout << "Current number of activities in Activity List: " << this->service.getActivityListLength() << "\n";
}

void UI::undoCommand() {
    try {
        this->service.undo();
        cout << "Action undone!";
        this->printAllActivities(this->service.getAllActivitiesService());
    } catch (RepositoryExcepetion& err) {
        cout << err << '\n';
    }
}

void UI::run() {
    map <string, vector<Activity>> mapOfTypes = map <string, vector<Activity>>();
    while (true) {
        this->printMenu();
        cout << "Command: ";
        int command; cin >> command;

        switch (command) {
            case 1: {
                this->addActivityCommand(mapOfTypes);
                break;
            }

            case 2: {
                this->deleteActivityCommand();
                break;
            }

            case 3: {
                this->updateActivityCommand();
                break;
            }

            case 4: {
                this->findActivityCommand();
                break;
            }

            case 5: {
                this->filterActivitiesCommand();
                break;
            }

            case 6: {
                this->sortActivitiesCommand();
                break;
            }

            case 7: {
                this->printMapCommand(mapOfTypes);
                break;
            }

            case 8: {
                this->emptyListCommand();
                break;
            }

            case 9: {
                this->addActivityInListCommand();
                break;
            }

            case 10: {
                this->generateRandomListCommand();
                break;
            }

            case 11: {
                this->undoCommand();
                break;
            }

            case 0: {
                cout << "You exit the application!";
                return;
            }

            default: {
                cout << "Invalid command!\n";
            }
        }
    }
}






