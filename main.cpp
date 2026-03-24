#include <iostream>
#include "UMLAttribute.h"
#include "UMLMethod.h"
#include "UMLClass.h"
#include "CPPCodeGenerator.h"
using namespace std;
 
int main() {
 
    cout << "=== UML Class Diagram Code Generator ===" << endl;
    cout << "Checkpoint Demo — Hardcoded Input" << endl;
    cout << "========================================" << endl << endl;
 
    // -----------------------------------------------
    // STEP 1: Manually build a "Student" UML class
    // (Later this data will come from parsing a file)
    // -----------------------------------------------
 
    UMLClass student("Student");
 
    // Add attributes (fields)
    student.addAttribute(UMLAttribute("private", "string", "name"));
    student.addAttribute(UMLAttribute("private", "int",    "rollNo"));
    student.addAttribute(UMLAttribute("private", "float",  "marks"));
 
    // Add methods
    student.addMethod(UMLMethod("public", "string", "getName()"));
    student.addMethod(UMLMethod("public", "void",   "setName(string)"));
    student.addMethod(UMLMethod("public", "int",    "getRollNo()"));
    student.addMethod(UMLMethod("public", "void",   "display()"));
 
    // -----------------------------------------------
    // STEP 2: Build a second class "Teacher"
    // Showing the generator works for ANY class
    // -----------------------------------------------
 
    UMLClass teacher("Teacher");
 
    teacher.addAttribute(UMLAttribute("private", "string", "teacherName"));
    teacher.addAttribute(UMLAttribute("private", "string", "subject"));
    teacher.addAttribute(UMLAttribute("private", "int",    "experience"));
 
    teacher.addMethod(UMLMethod("public", "string", "getTeacherName()"));
    teacher.addMethod(UMLMethod("public", "void",   "setSubject(string)"));
    teacher.addMethod(UMLMethod("public", "void",   "display()"));
 
    // -----------------------------------------------
    // STEP 3: Generate .h files using CPPCodeGenerator
    // -----------------------------------------------
 
    CPPCodeGenerator generator;
 
    cout << "Generating C++ header files..." << endl << endl;
 
    generator.generate(student);   // creates output/Student.h
    generator.generate(teacher);   // creates output/Teacher.h
 
    cout << endl;
    cout << "Done! Check the 'output/' folder for generated files." << endl;
 
    return 0;
}