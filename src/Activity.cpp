#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "Activity.h"
/**
void Activity::setCurrentPerson(Person p)
{
    _person = std::move(p);
}
**/
void Activity::jumpActivity()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<int> distribution(_jump_probability.begin(), _jump_probability.end());
    //distribution(gen) // Unfinished
    // TODO: jump to the activity associated with the id of _jump_probability vector
}

void Eat::simulate() const
{
    std::cout << "A person is eating" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(_time));
}

void Sleep::simulate() const
{
    std::cout << "A person is sleeping" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(_time));
}

void Commute::simulate() const
{
    std::cout << "A person is commuting" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(_time));
}