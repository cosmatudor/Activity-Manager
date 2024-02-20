#include "ActivitiesRepository.h"
#include <utility>

class FileRepo: public AbstractRepo {
private:
    string fileName;
    void loadFromFile();
    void writeToFile();

public:
    explicit FileRepo(string fName) : fileName{std::move( fName )} {
        this->loadFromFile();
    };

    void addActivity(const Activity &activity) override;

    void deleteActivity(const Activity&) override;

    void deleteAll() override;

    void updateActivity(Activity &activity, const Activity &newActivity) override;

    vector<Activity> getAllActivities() override;

    int findActivityIndex(const Activity &activity) override;

    Activity getActivityByTitle(const string& title) override;

    int length() override;
};

