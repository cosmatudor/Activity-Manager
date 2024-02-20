#pragma once

#include <string>
#include <iostream>

using std::string;
using std::cout;

class Activity {
private:
    std::string title;
    std::string description;
    std::string type;
    int duration;

public:
    Activity();

    Activity(const string ti, const string de, const string ty, int du);

    Activity(const Activity& ot);

    string getTitle() const;

    string getDescription() const;

    string getType() const;

    int getDuration() const;

    bool operator==(const Activity &activity);

    Activity& operator=(const Activity& activity);
};
