#ifndef UMLATTRIBUTE_H
#define UMLATTRIBUTE_H
 
#include <string>
using namespace std;
 
// Represents ONE field/variable in a class
// Example: private string name
//          ^access  ^type   ^name
 
class UMLAttribute {
public:
    string access;   // "private" / "public" / "protected"
    string type;     // "string" / "int" / "float"
    string name;     // "name" / "rollNo" / "age"
 
    // Constructor — sets all 3 values at once
    UMLAttribute(string access, string type, string name) {
        this->access = access;
        this->type   = type;
        this->name   = name;
    }
};
 
#endif