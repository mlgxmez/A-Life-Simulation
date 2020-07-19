#pragma once
#include <array>
class Person
{
    
    public:
        static int id;
        Person(): _id(Person::id)
        {
            ++Person::id;
            _activityLog={0,0,0};
        }
        int getId();
        void writeToLog(int i);
        void printLog();

    private:
        const int _id;
        std::array<int,3> _activityLog;
};