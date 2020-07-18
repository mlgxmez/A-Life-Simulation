#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <thread>
#include <iterator>
#include "Activity.h"
#include "Person.h"

int main() {
    int num_people;
    std::cout << "Choose number of people" << "\n";
    std::cin >> num_people; // Number of people
    //std::unique_ptr<Person> p = std::make_unique<Person>();
    WaitingQueue wq(num_people);
    std::vector<Activity> activities;
    activities.emplace_back(Activity(300, {20, 80, 0}, ActivityType::Eat, wq));
    activities.emplace_back(Activity(2000, {25, 35, 40}, ActivityType::Sleep, wq));
    activities.emplace_back(Activity(700, {50, 20, 30}, ActivityType::Commute, wq));
    //Activity a1 = Activity(300, {20, 80, 0}, ActivityType::Eat);
    //a1.setCurrentPerson(std::move(p));
    //std::thread t = std::thread(&Activity::simulate, std::move(a1));
    //t.join();
    //auto a = activities.begin()+1; // This is an iterator pointing to the first element
    //a->setCurrentPerson(std::move(p));
    //auto next_a = activities.end(); // Iterator pointing to the next element after end
    //

    
    std::vector<std::thread> workers;

    for(auto &ac: activities)
    {
        workers.emplace_back(std::thread(&Activity::simulate, std::move(ac)));
    }

   
    //workers.emplace_back(std::thread(&Activity::simulate, a1, this));
    /**
    for(auto &act: activities)
    {
        workers.emplace_back(std::thread(&Activity::simulate, act));
    }
    std::for_each(activities.begin(), activities.end(), [&workers](Activity &act){
        workers.emplace_back(std::thread(act.simulate()));
        });
    **/
    std::for_each(workers.begin(), workers.end(), [](std::thread &t){
        t.join();
    });
    
    /**
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
    **/
    return 0;
}