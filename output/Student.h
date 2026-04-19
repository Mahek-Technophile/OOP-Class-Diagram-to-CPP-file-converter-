#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
using namespace std;

class Student : public Person {
private:
    int rollNo;
    float marks;
    string branch;

public:
    int getRollNo();
    float getMarks();
    void setMarks(float marks);
    void display();
};

#endif
