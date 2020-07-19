#include <iostream>
#include <chrono>
#include <random>
#include <string>

#include "Activity.h"

WaitingQueue::WaitingQueue() {}

WaitingQueue::WaitingQueue(int num_person)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);
    for(int i = 0; i < num_person; i++)
    {
        _personQueue.push_back(std::make_unique<Person>());
        ActivityType startingActivity = static_cast<ActivityType>(dist(gen));
        _activityQueue.push_back(startingActivity); // assign random activity
    }
}

void WaitingQueue::addToQueue(std::unique_ptr<Person> p, ActivityType new_activity)
{
    // Called after decided new activity
    std::unique_lock<std::mutex> alock(_mtx);
    _personQueue.push_back(std::move(p));
    _activityQueue.push_back(new_activity);
    alock.unlock();
}

void WaitingQueue::sendPersonToNewActivity(Activity *a)
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::unique_lock<std::mutex> alock(_mtx);
        if(_activityQueue.size() > 0)
        {
            for(int i = 0; i < _activityQueue.size(); i++)
            {
                if(_activityQueue[i] == a->getActivity())
                {
                    auto selectedPerson = std::move(_personQueue.at(i));
                    a->setCurrentPerson(std::move(selectedPerson));

                    _activityQueue.erase(_activityQueue.begin() + i);
                    _personQueue.erase(_personQueue.begin() + i);
                    return;
                }
            }
        }
        alock.unlock();
    }
}

ActivityType Activity::getActivity()
{
    return _activity;
}

void Activity::doActivity()
{
    std::vector<std::string> activityNames = {"Commute","Eat","Sleep"};
    int activity_index = static_cast<int>(this->getActivity());
    std::cout << "Person ID: " << _currentPerson->getId() << ", doing activity: " << activityNames[activity_index] << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(_time));
    _currentPerson->writeToLog(activity_index);
    _currentPerson->printLog();
}

void Activity::simulate()
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(!_currentPerson) // TODO: Change to wait
        {
            _waitingList->sendPersonToNewActivity(this);
        }
        doActivity();
        int next_activity = decideNewActivity();

        _waitingList->addToQueue(
            std::move(_currentPerson), 
            static_cast<ActivityType>(next_activity)
            );

    }
}

void Activity::setCurrentPerson(std::unique_ptr<Person> p)
{
    _currentPerson = std::move(p);
}

int Activity::decideNewActivity()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<int> distribution(_transitions.begin(), _transitions.end());
    // Choose new activity given the conditional probability that the person is in _activity
    return distribution(gen);
}