#include <vector>

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
private:
    std::vector <Observer*> interested;

protected:
    void notify();

public:
    void addObserver(Observer* o);
    void removeObserver(Observer* o);
};