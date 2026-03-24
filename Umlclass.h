#ifndef UMLCLASS_H
#define UMLCLASS_H
 
#include <string>
#include <vector>
#include "UMLAttribute.h"
#include "UMLMethod.h"
using namespace std;
 
// Represents an ENTIRE class from the UML diagram
// It CONTAINS a list of attributes and a list of methods
// This is COMPOSITION — a class is made up of attributes + methods
 
class UMLClass {
public:
    string className;                    // "Student" / "Teacher"
    vector<UMLAttribute> attributes;     // all fields of this class
    vector<UMLMethod>    methods;        // all methods of this class
 
    // Constructor — just sets the class name
    UMLClass(string name) {
        this->className = name;
    }
 
    // Add one attribute to this class
    void addAttribute(UMLAttribute attr) {
        attributes.push_back(attr);
    }
 
    // Add one method to this class
    void addMethod(UMLMethod method) {
        methods.push_back(method);
    }
};
 
#endif
 