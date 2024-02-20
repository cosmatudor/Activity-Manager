#include <QHBoxLayout>
#include "ActivitiesListGUI.h"

void ActivitiesListGUI::initGUI() {
    auto mainLy = new QVBoxLayout();
    setLayout(mainLy);
    mainLy->addWidget(list);

    auto wnd1 = new QHBoxLayout();
    wnd1->addWidget(generateBtn);
    wnd1->addWidget(clearBtn);
    mainLy->addLayout(wnd1);
}

void ActivitiesListGUI::initConnect() {
    QObject::connect(generateBtn, &QPushButton::clicked, [&]() {
       int len = service.getAllActivitiesService().size();
       // generate a random number between 1 and len
         int random = rand() % len + 1;
         service.generateRandomActivityList(random);

         // Don't need it
         // loadData(service.getAllActivityList());
    });

    QObject::connect(clearBtn, &QPushButton::clicked, [&]() {
        service.emptyActivityList();
    });
}

void ActivitiesListGUI::loadData(vector<Activity> array) {
    list->clear();
    for (const auto& a : array) {
        auto item = QString::fromStdString(a.getTitle() + " | " + a.getDescription() + " | " +
                a.getType() + " | " + to_string(a.getDuration()));
        list->addItem(item);
    }
}

void ActivitiesListGUI::update() {
    loadData(service.getAllActivityList());
}

