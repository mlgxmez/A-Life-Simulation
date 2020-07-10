#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <random>
#include <vector>
#include <string>
#include "Activity.h"

ActivityType Activity::getActivity()
{
    return _activity;
}

void Activity::simulate()
{
    std::vector<std::string> activityNames = {"Commute","Eat","Sleep"};
    std::cout << "A person with id " << _person->getId() <<" is doing the activty " << activityNames[static_cast<int>(_activity)] << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(_time));
}

void Activity::setCurrentPerson(std::unique_ptr<Person> p)
{
    _person = std::move(p);
}

int Activity::decideNewActivity()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<int> distribution(_transitions.begin(), _transitions.end());
    // Choose new activity given the conditional probability that the person is in _activity
    return distribution(gen);
}

void Activity::movePersonToNewActivity(Activity *newActivity)
{
    newActivity->setCurrentPerson(std::move(_person));
}