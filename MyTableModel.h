#include <vector>
#include <QAbstractTableModel>
#include "activity.h"

class MyTableModel : public QAbstractTableModel {
    std::vector<Activity> activities;

public:
    MyTableModel(const std::vector<Activity>& ac) : activities{ ac } {};

    int rowCount(const QModelIndex & parent = QModelIndex()) const override {
        return activities.size();
    }

    int columnCount(const QModelIndex & parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            Activity a = activities[index.row()];
            if (index.column() == 0) {
                return QString::fromStdString(a.getTitle());
            }
            if (index.column() == 1) {
                return QString::fromStdString(a.getDescription());
            }
            if (index.column() == 2) {
                return QString::fromStdString(a.getType());
            }
            if (index.column() == 3) {
                return QString::fromStdString(std::to_string(a.getDuration()));
            }
        }
        return QVariant{};
    }

    void setActivities(const std::vector<Activity> acts) {
        this->activities = acts;
        auto topLeft = createIndex(0, 0);
        auto bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);
    }
};