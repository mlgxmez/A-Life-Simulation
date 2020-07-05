class Person
{
    
    public:
        static int id;
        Person(): _id(id) {++Person::id;}

    private:
        int _id;

};