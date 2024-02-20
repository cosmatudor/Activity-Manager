#include "ReadOnlyGUI.h"

void ReadOnlyGUI::paintEvent(QPaintEvent *ev) {
    QPainter painter(this);
    int x = 0, y = 0;
    for (int i = 0; i < service.getAllActivityList().size(); ++i) {
        painter.drawRect(x, y, 20,30);
        QImage image("banana.jpg");
        if (image.load("banana.jpg")) {
            // Image loaded successfully
        } else {
            // Image loading failed
            qDebug() << "Failed to load image!";
        }
        painter.drawImage(x, y, image);
        x += 150;
        y += 150;
    }
}

void ReadOnlyGUI::update() {
   repaint();
}

void ReadOnlyGUI::initGUI() {
    auto mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    setBaseSize(500, 500);
}
