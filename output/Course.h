#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
using namespace std;

class Course {
private:
    string courseCode;
    string courseName;
    int credits;

public:
    string getCourseCode();
    string getCourseName();
    void display();
};

#endif
