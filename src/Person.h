#ifndef PERSON_H
#define PERSON_H

class Person
{
    
    public:
        static int id;
        Person(): _id(Person::id) {++Person::id;}
        int getId();

    private:
        int _id;

};

#endif