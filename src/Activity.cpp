#include <iostream>
#include <chrono>
#include <random>
#include <string>
//#include <mutex>

#include "Activity.h"

void WaitingQueue::addToQueue(std::unique_ptr<Person> p, ActivityType new_activity)
{
    // Called after decided new activity
    std::unique_lock<std::mutex> alock(_mtx);
    _personQueue.push_back(std::move(p));
    _activityQueue.push_back(new_activity);
    alock.unlock();
    //_promises.push_back(std::move(promise));
    std::cout << "Person added to waiting list" << std::endl;

}

void WaitingQueue::sendPersonToNewActivity(Activity *a)
{
    std::cout << "Entering sendPersonToNewActivity by activity " << static_cast<int>(a->getActivity()) << std::endl;
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

/**
void WaitingQueue::sendPersonToNewActivity(Activity *a, std::promise<void> &&promise)
{
    // TODO: Find the activity that corresponds to the type
    std::cout << "Entering sendPersonToNewActivity by activity " << static_cast<int>(a->getActivity()) << std::endl;
    int i = 0;
    for(i; i < _activityQueue.size(); i++)
    {
        if(_activityQueue[i] == a->getActivity())
        {
            auto selectedPerson = std::move(_personQueue.at(i));
            a->setCurrentPerson(std::move(selectedPerson));
            //_promises[i].set_value();
            // Erase the element i for all vectors
            _activityQueue.erase(_activityQueue.begin() + i);
            _personQueue.erase(_personQueue.begin() + i);
            //_promises.erase(_promises.begin() + i);
            promise.set_value();
            std::cout << "Fulfilled promise" << std::endl;
            return;
        }
    }
    if(i == _activityQueue.size())
        std::cout << "No person is waiting for in activity " << static_cast<int>(a->getActivity()) << std::endl;
    return;
}
**/
ActivityType Activity::getActivity()
{
    return _activity;
}
/**
void Activity::simulate()
{
    std::promise<void> prmsPersonComingToActivity;
    std::future<void> ftrPersonComingToActivity = prmsPersonComingToActivity.get_future();

    _threads.emplace_back(std::move(prmsPersonComingToActivity)); // simulate adds promises to thread, and another function must processed them
}
**/

void Activity::doActivity()
{
    std::vector<std::string> activityNames = {"Commute","Eat","Sleep"};
    std::cout << "A person with id " << _currentPerson->getId() << " is doing activity: " << activityNames[static_cast<int>(this->getActivity())] << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(_time));
}

void Activity::simulate()
{
    //std::mutex _mtx;
    //std::unique_lock<std::mutex> alock(_mtx, std::defer_lock);
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(!_currentPerson) // TODO: Change to wait
        {
            //std::promise<void> prmsSendPerson;
            //std::future<void> ftrSendPerson = prmsSendPerson.get_future();
            //std::this_thread::sleep_for(std::chrono::milliseconds(300));
            //alock.lock();
            _waitingList->sendPersonToNewActivity(this); // Risk of deadlock
            //alock.unlock();

            //ftrSendPerson.wait(); // Wait until a Person is set in _currentPerson
            std::cout << "Wait has ended" << std::endl;
        }
        doActivity();
        int next_activity = decideNewActivity();
        std::cout << "Next activity will be " << next_activity << std::endl;
        //std::promise<void> prmsSendToWaitingList;
        //std::future<void> ftrSendToWaitingList = prmsSendToWaitingList.get_future();
        //alock.lock();
        _waitingList->addToQueue(
            std::move(_currentPerson), 
            static_cast<ActivityType>(next_activity)
            );
        //alock.unlock();
        //ftrSendToWaitingList.wait();
    }
}

/**
void Activity::simulate()
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(!_personQueue.empty() && !_currentPerson)
        {
            _currentPerson = std::move(_personQueue.front());
            _personQueue.pop_front();
            std::vector<std::string> activityNames = {"Commute","Eat","Sleep"};
            std::cout << "A person with id " << _currentPerson->getId() <<" is doing the activty " << activityNames[static_cast<int>(_activity)] << std::endl;
            int next_activity = decideNewActivity();
            movePersonToNewActivity(&(this[0])); // TODO: How to pass another activity to the function
        }
    }
}
**/
/**
void Activity::processIncomingPerson()
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if(!_currentPerson)
        {
            // Make a call to a function to a method of _waitingList to add someone to _currentPerson
            std::promise<Person> prmsNextPerson;
            std::future<Person> ftrNextPerson = prmsNextPerson.get_future();
            _waitingList->funReturnPerson(); // Inside you set_value to promise

            _person = ftrNextPerson.get(); // I have the person here


            
        }
    }
}
**/
void Activity::setCurrentPerson(std::unique_ptr<Person> p)
{
    //_currentPerson = std::move(p);
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
/**
void Activity::movePersonToNewActivity(Activity *newActivity)
{
    newActivity->setCurrentPerson(std::move(_currentPerson));
}

void Activity::movePersonToWaitingList(WaitingList *w)
{
    w->addToQueue(std::move(_currentPerson));
}
**/