#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Activity.h"
#include "Person.h"

int main() {
    std::cout << "Hello World!" << "\n";
    std::unique_ptr<Person> p = std::make_unique<Person>();

    std::vector<Activity> activities;
    activities.emplace_back(Activity(300, {20, 80, 0}, ActivityType::Eat));
    activities.emplace_back(Activity(2000, {25, 35, 40}, ActivityType::Sleep));
    activities.emplace_back(Activity(700, {50, 20, 30}, ActivityType::Commute));
    auto a = activities.begin(); // This is an iterator pointing to the first element
    auto next_a = activities.end(); // Iterator pointing to the next element after end
    a->setCurrentPerson(std::move(p));
    while(true)
    {
        a->simulate();
        int next_index = a->decideNewActivity();
        if(a - activities.begin() != next_index)
        {
            next_a = activities.begin() + next_index; // Set iterator to new activity
            a->movePersonToNewActivity(&*next_a); // Arg is an iterator to pointer conversion
            std::swap(a, next_a); // Swap the position of two iterators
        }
    }
    return 0;
}