#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>

#include "ActivitiesService.h"

class ReadOnlyGUI: public QWidget, public Observer {
private:
    Service& service;

    void initGUI();
    void paintEvent(QPaintEvent* ev) override;

public:
    explicit ReadOnlyGUI(Service& service) : service{service} {
        initGUI();
        service.addObserver(this);
    };

    void update() override;
};