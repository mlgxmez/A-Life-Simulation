#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <thread>
#include <iterator>
#include "Activity.h"
#include "Person.h"

void setTimer()
{
    std::this_thread::sleep_for(std::chrono::seconds(60));
}

int main() {
    int num_people;
    std::cout << "Choose number of people" << "\n";
    std::cin >> num_people; // Number of people

    WaitingQueue wq(num_people);
    std::vector<Activity> activities;
    activities.emplace_back(Activity(300, {20, 80, 0}, ActivityType::Eat, wq));
    activities.emplace_back(Activity(2000, {25, 35, 40}, ActivityType::Sleep, wq));
    activities.emplace_back(Activity(700, {50, 20, 30}, ActivityType::Commute, wq));


    std::vector<std::thread> workers;
    for(auto &ac: activities)
    {
        workers.emplace_back(std::thread(&Activity::simulate, std::move(ac)));
    }

   std::thread time_thread(setTimer); // Wait for 60 seconds
   time_thread.join();

    std::for_each(workers.begin(), workers.end(), [](std::thread &t){
        t.detach();
    });

    return 0;
}