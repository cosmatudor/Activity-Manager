#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "ActivitiesService.h"

class ActivitiesListGUI: public QWidget, public Observer{
private:
    Service& service;

    void update() override;
    void initGUI();
    void loadData(vector<Activity> array);
    void initConnect();

    QListWidget *list = new QListWidget();

    QPushButton *generateBtn = new QPushButton("&Generate");
    QPushButton *clearBtn = new QPushButton("&Clear");


public:
    explicit ActivitiesListGUI(Service& service): service{service} {
        service.addObserver(this);
        initGUI();
        loadData(vector<Activity>{});
        initConnect();
    };

};