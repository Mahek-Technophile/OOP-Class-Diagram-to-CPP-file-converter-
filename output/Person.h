#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
using namespace std;

class Person {
private:
    // (none)

public:
    string getName();
    void setName(string name);
    int getAge();
    void display();

protected:
    string name;
    int age;
};

#endif
