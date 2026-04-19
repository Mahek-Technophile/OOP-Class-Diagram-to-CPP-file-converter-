#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
using namespace std;

class Teacher {
private:
    string teacherName;
    string subject;
    int employeeId;

public:
    string getTeacherName();
    string getSubject();
    void setSubject(string subject);
    void display();
};

#endif
