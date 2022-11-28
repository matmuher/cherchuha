#pragma once

#include <list>

class Observer
{
public:

    virtual void update() = 0;
};

class Observable
{
    std::list<Observer*> _observers;

public:

    void notify_observers()
    {
        for (auto it = _observers.begin(); it != _observers.end(); it++)
        {
            (*it)->update();    
        }
    }

    void add_observer(Observer* obsrvr)
    {
        _observers.push_back(obsrvr);
    }
};