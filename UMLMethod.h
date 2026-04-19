#ifndef UMLMETHOD_H
#define UMLMETHOD_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// =============================================================
//  UMLMethod — represents one function/method in a class
//  e.g.  public string getName()
//        public void setName(string)
//
//  OOP CONCEPTS:
//  ✅ Encapsulation       — data + behavior in one class
//  ✅ Function Overloading— two constructors (with/without params)
//  ✅ Copy Constructor    — safe deep copy inside STL vectors
// =============================================================

class UMLMethod {
public:
    string access;           // "private" / "public" / "protected"
    string returnType;       // "void" / "string" / "int"
    string name;             // full signature e.g. "getName()"
    vector<string> params;   // optional explicit param types

    // Default Constructor
    UMLMethod() : access(""), returnType(""), name("") {}

    // -------------------------------------------------------
    // Constructor 1 — without explicit params list
    // OOP CONCEPT: Function Overloading
    // -------------------------------------------------------
    UMLMethod(string access, string returnType, string name) {
        this->access      = access;
        this->returnType  = returnType;
        this->name        = name;
    }

    // -------------------------------------------------------
    // Constructor 2 — with explicit params list
    // OOP CONCEPT: Function Overloading (same name, diff signature)
    // -------------------------------------------------------
    UMLMethod(string access, string returnType, string name, vector<string> params) {
        this->access      = access;
        this->returnType  = returnType;
        this->name        = name;
        this->params      = params;
    }

    // -------------------------------------------------------
    // Copy Constructor — OOP CONCEPT
    // Called when vector resizes or passes by value
    // -------------------------------------------------------
    UMLMethod(const UMLMethod& other) {
        this->access      = other.access;
        this->returnType  = other.returnType;
        this->name        = other.name;
        this->params      = other.params;
    }

    void display() const {
        cout << "  [METHOD] " << access << " " << returnType << " " << name << "\n";
    }
};

#endif
