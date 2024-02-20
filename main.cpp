
//int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    return QApplication::exec();
//}

#include "UI.h"
#include "Tests.h"
#include "AbstractRepo.h"
#include "ActivitiesFileRepo.h"
#include "GUI.h"
#include "ActivitiesListGUI.h"
#include "ReadOnlyGUI.h"


int main(int argc, char *argv[]) {
    Tests tests = Tests();
    tests.testAll();

    QApplication a(argc, argv);
    QApplication::setFont(QFont("TimesNewRoman", 15));

    AbstractRepo *repository = new Repository();
    AbstractRepo *fileRepo =  new FileRepo("activities.txt");
    Service service = Service(fileRepo);
    // UI ui = UI(service);
    // ui.run();

    GUI gui{ service };
    gui.show();

    return QApplication::exec();
}


