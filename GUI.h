#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QListWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QObject>
#include <QTableWidget>

#include "MyTableModel.h"
#include "ActivitiesService.h"

class GUI: public QWidget {
public:
    explicit GUI(Service& service) : service{ service } {
        initGUI();
        loadData(service.getAllActivitiesService());
        initConnect();
        addButton();
    }

private:
    Service& service;
    map <string, vector<Activity>> mapOfTypes = map <string, vector<Activity>>();

    QListWidget* comp1 = new QListWidget; // list
    QListView* listV = new QListView;
    MyTableModel* model = new MyTableModel(service.getAllActivitiesService());

    QPushButton* addBtn = new QPushButton{ "&Add" };
    QPushButton* delBtn = new QPushButton{ "&Delete" };
    QPushButton* updBtn = new QPushButton{ "&Update" };
    QPushButton* findBtn = new QPushButton{ "&Find" };
    QPushButton* exitBtn = new QPushButton{ "&Exit" };
    QPushButton* undoBtn = new QPushButton{ "&Undo" };
    QPushButton* filterBtn = new QPushButton{ "&Filter" };
    QPushButton* sortBtn = new QPushButton{ "&Sort" };
    QPushButton* addToALbtn = new QPushButton{ "&Add to Activity List" };
    QPushButton* gnrtALbtn = new QPushButton{ "&Generate Activity List" };
    QPushButton* clrALbtn = new QPushButton{ "&Clear Activity List" };
    QPushButton* readOnlyBtn = new QPushButton{ "&Read Only" };
    QPushButton* activityListBtn = new QPushButton{ "&Activity List" };

    QVBoxLayout* buttonLayout = new QVBoxLayout();
    vector<QPushButton*> btns;

    QLineEdit* titleText = new QLineEdit();
    QLineEdit* descText = new QLineEdit();
    QLineEdit* typeText = new QLineEdit();
    QLineEdit* durText = new QLineEdit();

    void initGUI();
    void loadData(const vector<Activity>& activities);
    void initConnect();
    void addButton();
};


class FilterGUI : public QWidget {
private:
    Service& service;
    QString desc;
    QString type;
    QListWidget* comp = new QListWidget;

    QPushButton* filterDescBtn = new QPushButton{ "&By description" };
    QPushButton* filterTypeBtn = new QPushButton{ "&By type" };

    void initFilterGUI();
    void initConnect();

public:
    FilterGUI(Service& service, QString desc, QString type) : service{ service }, desc{ std::move(desc) }, type{ std::move(type) } {
        initFilterGUI();
        initConnect();
    }
};


class SortGUI: public QWidget {
public:
    explicit SortGUI(Service& service) : service{ service } {
        initSortGUI();
        initConnect();
    };

private:
    Service& service;

    // buttons
    QPushButton* byTitle = new QPushButton{ "&By title "};
    QPushButton* byDesc = new QPushButton{ "&By description "};
    QPushButton* byTyDur = new QPushButton{ "&By type + duration "};

    // Widgets
    QListWidget* comp1 = new QListWidget; // list
    QTableWidget* table = new QTableWidget(0,4); // table

    // methods
    void initSortGUI();
    void initConnect();
};


class FindGUI: public QWidget {
public:
    explicit FindGUI(const Activity& a) : activity { a } {
        initFindGUI();
        loadData();
    };

private:
    Activity activity;

    // Widgets
    QListWidget* comp1 = new QListWidget;

    // methods
    void initFindGUI();
    void loadData();
};