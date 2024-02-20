#include <QMessageBox>
#include "GUI.h"
#include "ActivitiesListGUI.h"
#include "ReadOnlyGUI.h"

void GUI::initGUI() {
    QHBoxLayout *mainLy = new QHBoxLayout{};
    setLayout(mainLy);

    mainLy->addLayout(buttonLayout);

    // first component = list for activities
    listV->setModel(model);
    mainLy->addWidget(listV);

    // second component = layout with fields and buttons
    auto comp2 = new QVBoxLayout;
    // It's composed of
    // 1. layout for fields of an Activity
    auto formLy = new QFormLayout;
    formLy->addRow("Title", titleText);
    formLy->addRow("Description", descText);
    formLy->addRow("Type", typeText);
    formLy->addRow("Duration", durText);
    comp2->addLayout(formLy);

    // 2. buttons
    auto btnLy = new QHBoxLayout{};
    btnLy->addWidget(addBtn);
    btnLy->addWidget(delBtn);
    btnLy->addWidget(updBtn);
    comp2->addLayout(btnLy);

    // Add it to main layout
    mainLy->addLayout(comp2);

    // third component - other buttons
    auto comp3 = new QVBoxLayout;
    auto btnLy2 = new QVBoxLayout;
    btnLy2->addWidget(findBtn);
    btnLy2->addWidget(filterBtn);
    btnLy2->addWidget(sortBtn);
    btnLy2->addWidget(undoBtn);
    btnLy2->addWidget(exitBtn);
    comp3->addLayout(btnLy2);

    mainLy->addLayout(comp3);

    // add a line to separate these components from the next one
    auto line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    mainLy->addWidget(line);

    // fourth component - activities list
    QVBoxLayout *comp4 = new QVBoxLayout();
    comp4->addWidget(addToALbtn);
    comp4->addWidget(gnrtALbtn);
    comp4->addWidget(clrALbtn);

    auto line2 = new QFrame();
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);
    comp4->addWidget(line2);

    comp4->addWidget(activityListBtn);
    comp4->addWidget(readOnlyBtn);
    mainLy->addLayout(comp4);
}

void GUI::loadData(const vector<Activity>& activities) {
    model->setActivities(activities);

    //comp1->clear();
    mapOfTypes.clear();
    for (const auto& a : activities) {
        //comp1->addItem(QString::fromStdString(a.getTitle()) + " | " + QString::fromStdString(a.getDescription()) + " | " +
        //QString::fromStdString(a.getType()) + " | " + QString::fromStdString(to_string(a.getDuration())));

        service.loadMapOfActivities(a, mapOfTypes);
    }
}

void GUI::initConnect() {
     QObject::connect(exitBtn, &QPushButton::clicked, [&]() {
        close();
     });

     QObject::connect(addBtn, &QPushButton::clicked, [&]() {
        auto title = titleText->text().toStdString();
        auto desc = descText->text().toStdString();
        auto type = typeText->text().toStdString();
        auto dur = durText->text().toInt();
        try {
            service.addActivityService(title, desc, type, dur, mapOfTypes);
            loadData(service.getAllActivitiesService());
        } catch (RepositoryExcepetion &err) {
            cout << err << '\n';
        } catch (ValidationException &err) {
            cout << err.getMessage() << '\n';
        }
        addButton();
     });

     QObject::connect(delBtn, &QPushButton::clicked, [&]() {
         auto title = titleText->text().toStdString();
         try {
             service.deleteActivityService(title);
             loadData(service.getAllActivitiesService());
         } catch (RepositoryExcepetion &err) {
             cout << err << '\n';
         } catch (ValidationException &err) {
             cout << err.getMessage() << '\n';
         }
         addButton();
     });

     QObject::connect(updBtn, &QPushButton::clicked, [&]() {
         auto title = titleText->text().toStdString();
         auto desc = descText->text().toStdString();
         auto type = typeText->text().toStdString();
         auto dur = durText->text().toInt();
         try {
             service.updateActivityService(title, title, desc, type, dur);
             loadData(service.getAllActivitiesService());
         } catch (RepositoryExcepetion &err) {
             cout << err << '\n';
         } catch (ValidationException &err) {
             cout << err.getMessage() << '\n';
         }
         addButton();
     });

     QObject::connect(findBtn, &QPushButton::clicked, [&]() {
         auto title = titleText->text().toStdString();
         auto activity = service.findActivityService(title);
         auto wdg = new FindGUI(activity);
         wdg->show();
     });

     QObject::connect(undoBtn, &QPushButton::clicked, [&](){
        try {
            service.undo();
            loadData(service.getAllActivitiesService());
            qDebug() << "Action undone!";
        } catch (RepositoryExcepetion& err) {
            cout << err << '\n';
        }
         addButton();
    });

    QObject::connect(filterBtn, &QPushButton::clicked, [&]() {
        auto desc = descText->text();
        auto type = typeText->text();
        auto wdg = new FilterGUI(service, desc, type);
        wdg->show();
    });

    QObject::connect(sortBtn, &QPushButton::clicked, [&]() {
        auto wdg = new SortGUI(service);
        wdg->show();
    });

     QObject::connect(comp1, &QListWidget::itemSelectionChanged, [&]() {
         auto selected = comp1->selectedItems();
         if (selected.isEmpty()) {
             titleText->setText("");
             descText->setText("");
             typeText->setText("");
             durText->setText("");
             return;
         }
         auto firstSelected = selected.at(0);
         auto title = firstSelected->text().split(" | ").at(0).toStdString();
         auto desc = firstSelected->text().split(" | ").at(1).toStdString();
         auto type = firstSelected->text().split(" | ").at(2).toStdString();
         auto dur = firstSelected->text().split(" | ").at(3).toInt();
         titleText->setText(QString::fromStdString(title));
         descText->setText(QString::fromStdString(desc));
         typeText->setText(QString::fromStdString(type));
         durText->setText(QString::fromStdString(to_string(dur)));
     });

     QObject::connect(addToALbtn, &QPushButton::clicked, [&]() {
         auto title = titleText->text().toStdString();
         try {
             service.addActivityToActivityList(title);
         } catch (RepositoryExcepetion &err) {
             cout << err << '\n';
         } catch (ValidationException &err) {
             cout << err.getMessage() << '\n';
         }
     });

        QObject::connect(gnrtALbtn, &QPushButton::clicked, [&]() {
            int total = service.getAllActivitiesService().size();
            int random = rand() % total + 1;
            try {
                service.generateRandomActivityList(random);
            } catch (RepositoryExcepetion &err) {
                cout << err << '\n';
            } catch (ValidationException &err) {
                cout << err.getMessage() << '\n';
            }
        });

        QObject::connect(clrALbtn, &QPushButton::clicked, [&]() {
            service.emptyActivityList();
        });

        QObject::connect(activityListBtn, &QPushButton::clicked, [&]() {
            auto wdg = new ActivitiesListGUI(service);
            wdg->show();
        });

        QObject::connect(readOnlyBtn, &QPushButton::clicked, [&]() {
            auto wdg = new ReadOnlyGUI(service);
            wdg->show();
        });
}

void GUI::addButton() {
    // Here, we delete all the connections and clear the button array
    for (const auto &btn: btns) {
        QObject::disconnect(btn, &QPushButton::clicked, nullptr, nullptr);
    }
    btns.clear();

    // Here, we delete all the items from the layout
    QLayoutItem *child;
    while ((child = buttonLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Create new buttons with every existent type
    for (const auto& type: mapOfTypes) {
        auto newBtn = new QPushButton(QString::fromStdString(type.first));
        btns.push_back(newBtn);
        buttonLayout->addWidget(newBtn);
    }

    // Make new connections
    for (const auto& btn : btns) {
        QObject::connect(btn, &QPushButton::clicked, [&]() {
            auto type = btn->text().toStdString();
            auto nr = service.countActivitiesByTypeService(type, mapOfTypes);
            QMessageBox::information(this, "Number of activities: ", QString::fromStdString(to_string(nr)));
        });
    }
}


// --- SortGUI ---

void SortGUI::initSortGUI() {
    QVBoxLayout* mainLy = new QVBoxLayout;
    setLayout(mainLy);

    // firts component
    mainLy->addWidget(table);

    // second component
    QHBoxLayout* comp2 = new QHBoxLayout;
    comp2->addWidget(byTitle);
    comp2->addWidget(byDesc);
    comp2->addWidget(byTyDur);
    mainLy->addLayout(comp2);
}

void SortGUI::initConnect() {
    QObject::connect(byTitle, &QPushButton::clicked, [&]() {
        try {
            table->clear();
            table->setRowCount(0);
            auto array = service.sortActivitiesService(1);
            for (const auto &a: array) {
                int row = table->rowCount();
                table->insertRow(row);
                table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getTitle())));
                table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getDescription())));
                table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getType())));
                table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(to_string(a.getDuration()))));
            }
        } catch (UIException &err) {
            cout << err.getMessage() << '\n';
        } catch (RepositoryExcepetion &err) {
            cout << err << '\n';
        }
    });

    QObject::connect(byDesc, &QPushButton::clicked, [&]() {
        try {
            table->clear();
            table->setRowCount(0);
            auto array = service.sortActivitiesService(2);
            for (const auto &a: array) {
                int row = table->rowCount();
                table->insertRow(row);
                table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getTitle())));
                table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getDescription())));
                table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getType())));
                table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(to_string(a.getDuration()))));
            }
        } catch (UIException &err) {
            cout << err.getMessage() << '\n';
        } catch (RepositoryExcepetion &err) {
            cout << err << '\n';
        }
    });

    QObject::connect(byTyDur, &QPushButton::clicked, [&]() {
        try {
            table->clear();
            table->setRowCount(0);
            auto array = service.sortActivitiesService(3);
            for (const auto &a: array) {
                int row = table->rowCount();
                table->insertRow(row);
                table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getTitle())));
                table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getDescription())));
                table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getType())));
                table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(to_string(a.getDuration()))));
            }
        } catch (UIException &err) {
            cout << err.getMessage() << '\n';
        } catch (RepositoryExcepetion &err) {
            cout << err << '\n';
        }
    });
}


// --- Filter GUI ---

void FilterGUI::initFilterGUI() {
    QVBoxLayout *mainLy = new QVBoxLayout{};
    setLayout(mainLy);
    mainLy->addWidget(comp);

    auto comp2 = new QHBoxLayout;
    auto btnLy = new QHBoxLayout{};
    btnLy->addWidget(filterDescBtn);
    btnLy->addWidget(filterTypeBtn);
    comp2->addLayout(btnLy);
    mainLy->addLayout(comp2);
}

void FilterGUI::initConnect() {
    QObject::connect(filterDescBtn, &QPushButton::clicked, [&]() {
        try {
            auto array = service.filterActivitiesService("description", desc.toStdString());
            comp->clear();
            for (const auto& a : array) {
                comp->addItem(QString::fromStdString(a.getTitle()) + " | " + QString::fromStdString(a.getDescription()) + " | " +
                              QString::fromStdString(a.getType()) + " | " + QString::fromStdString(to_string(a.getDuration())));
            }
        } catch (const exception& ex) {
            QMessageBox::critical(this, "Error", ex.what());
        } catch (RepositoryExcepetion &err) {
            cout << err << '\n';
        }
    });

    QObject::connect(filterTypeBtn, &QPushButton::clicked, [&]() {
        try {
            auto array = service.filterActivitiesService("type", type.toStdString());
            comp->clear();
            for (const auto& a : array) {
                comp->addItem(QString::fromStdString(a.getTitle()) + " | " + QString::fromStdString(a.getDescription()) + " | " +
                              QString::fromStdString(a.getType()) + " | " + QString::fromStdString(to_string(a.getDuration())));
            }
        } catch (const exception& ex) {
            QMessageBox::critical(this, "Error", ex.what());
        } catch (RepositoryExcepetion &err) {
            cout << err << '\n';
        }
    });
}


// --- FIlter GUI ---

void FindGUI::initFindGUI() {
    QHBoxLayout* mainLy = new QHBoxLayout;
    setLayout(mainLy);
    mainLy->addWidget(comp1);
}

void FindGUI::loadData() {
    comp1->clear();
    comp1->addItem(QString::fromStdString(activity.getTitle()) + " | "
    + QString::fromStdString(activity.getDescription()) + " | "
    + QString::fromStdString(activity.getType()) + " | "
    + QString::fromStdString(to_string(activity.getDuration())));
}
