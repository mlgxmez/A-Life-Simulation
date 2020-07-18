#pragma once
#include <memory>
#include <array>
#include <vector>
#include <future>
#include <mutex>

#include "ActivityType.h"
#include "Person.h"

class WaitingQueue;

class Activity
{
    // Owned objects
    int _time;
    std::array<int, 3> _transitions;
    ActivityType _activity;
    WaitingQueue *_waitingList = nullptr;
    
    // Not owned objects
    std::unique_ptr<Person> _currentPerson;

public:
    Activity(int t, std::array<int, 3> tr, ActivityType a, WaitingQueue &wq) : _time(t), _transitions(tr), _activity(a), _waitingList(&wq) {}
    ActivityType getActivity();
    int decideNewActivity();
    void doActivity();
    void setCurrentPerson(std::unique_ptr<Person> p);
    void simulate();
};

class WaitingQueue
{
public:
    WaitingQueue();
    WaitingQueue(int num_person);
    void addToQueue(std::unique_ptr<Person> p, ActivityType new_activity);
    void sendPersonToNewActivity(Activity *a); // Calling with this op
private:
    std::mutex _mtx;
    std::vector<std::unique_ptr<Person>> _personQueue; // we use a->moveCurrentPerson
    std::vector<ActivityType> _activityQueue; // vector of next activity
    //std::vector<std::promise<void>> _promises; //probably the promise must contain the index to next_activity
};