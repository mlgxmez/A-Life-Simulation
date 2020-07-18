#pragma once

class Person
{
    
    public:
        static int id;
        Person(): _id(Person::id)
        {
            ++Person::id;
        }
        int getId();

    private:
        const int _id;
};