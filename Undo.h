#include "ActivitiesRepository.h"

class UndoAction {
public:
    virtual void doUndo() = 0;

    virtual ~UndoAction() {};
};

class AddUndo: public UndoAction {
private:
    AbstractRepo *repo;
    Activity activity;
public:
    AddUndo(AbstractRepo *repo, const Activity& activity) : repo{ repo }, activity{ activity} {};

    void doUndo() override;
};

class DeleteUndo: public UndoAction {
private:
    AbstractRepo *repo;
    Activity activity;
public:
    DeleteUndo(AbstractRepo *repo, const Activity& activity) : repo{ repo }, activity{ activity} {};

    void doUndo() override;
};

class UpdateUndo: public UndoAction {
private:
    AbstractRepo *repo;
    Activity activity;
    Activity newActivity;
public:
    UpdateUndo(AbstractRepo *repo, const Activity& activity, Activity& newActivity) : repo{ repo }, activity{ activity}, newActivity{ newActivity } {};

    void doUndo() override;
};
