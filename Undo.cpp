#include "Undo.h"

void AddUndo::doUndo() {
    this->repo->deleteActivity(activity);
}

void DeleteUndo::doUndo() {
    this->repo->addActivity(activity);
}

void UpdateUndo::doUndo() {
    this->repo->updateActivity(newActivity, activity);
}
