#include <iostream>

class objectA
{
public:
    objectA() :
        id(++counter)
    {}

    void counterOut()
    {
        std::cout << "Counter: " << counter << std::endl;
    }
    static int counter;
    int id;
};

int objectA::counter = 0;

int main()
{
    objectA a;
    a.counterOut();
    objectA b;
    b.counterOut();
    objectA c;
    c.counterOut();
}