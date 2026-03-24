#ifndef UMLMETHOD_H
#define UMLMETHOD_H
 
#include <string>
#include <vector>
using namespace std;
 
// Represents ONE method/function in a class
// Example: public string getName()
//          ^access ^returnType ^name
 
class UMLMethod {
public:
    string access;       // "public" / "private"
    string returnType;   // "string" / "void" / "int"
    string name;         // "getName()" / "setName(string)"
 
    // Constructor
    UMLMethod(string access, string returnType, string name) {
        this->access     = access;
        this->returnType = returnType;
        this->name       = name;
    }
};
 
#endif