#include <stdio.h>
#include "Person.h"

int Person::id = 0;

int Person::getId()
{
    return _id;
}

void Person::writeToLog(int i)
{
    _activityLog[i] += 1;
}

void Person::printLog()
{
    printf("Person ID: %d, Eat: %2d, Sleep: %2d, Commute: %2d\n", this->getId(), _activityLog[0], _activityLog[1], _activityLog[2]);
}