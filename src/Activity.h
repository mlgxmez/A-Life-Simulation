#include <memory>
#include <array>

#include "Person.h"

#ifndef ACTIVITY_H
#define ACTIVITY_H

enum class ActivityType {Commute, Eat, Sleep};

class Activity
{
    // Owned objects
    int _time;
    std::array<int, 3> _transitions;
    ActivityType _activity;

    // Not owned objects
    std::unique_ptr<Person> _person;

    public:
        Activity(int t, std::array<int, 3> tr, ActivityType a) : _time(t), _transitions(tr), _activity(a) {}
        ActivityType getActivity();
        int decideNewActivity();
        void movePersonToNewActivity(Activity *newActivity);
        void setCurrentPerson(std::unique_ptr<Person> p);
        void simulate();
};

/**
class Activity
{
    public:
        virtual void simulate() const = 0;
    protected:
        //void setCurrentPerson(Person p);
        void jumpActivity();

        int _time;
        std::array<int,3> _jump_probability;
        std::unique_ptr<Person> _person{}; // When it calls the constructor of Commute, it calls the constructor of Person

};

class Commute : Activity
{
    public:
        Commute()
        {
            _time = 300;
            _jump_probability[0] = 10;
            _jump_probability[1] = 50;
            _jump_probability[2] = 40;
            _person = nullptr;
        }
        void simulate() const;
};

class Sleep : Activity
{
    public:
        Sleep()
        {
            _time = 1200;
            _jump_probability[0] = 50;
            _jump_probability[1] = 0;
            _jump_probability[2] = 50;
            _person = nullptr;
        }
        void simulate() const;

};

class Eat : Activity
{
    public:
        Eat()
        {
            _time = 100;
            _jump_probability[0] = 70;
            _jump_probability[1] = 15;
            _jump_probability[2] = 15;
            _person = nullptr;
        }
        void simulate() const;

};
**/
#endif