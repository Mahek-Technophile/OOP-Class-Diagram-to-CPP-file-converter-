#ifndef UMLATTRIBUTE_H
#define UMLATTRIBUTE_H

#include <string>
#include <iostream>
using namespace std;

// =============================================================
//  UMLAttribute — represents one field/variable in a class
//  e.g.  private string name
//        private int rollNo
//
//  OOP CONCEPTS:
//  ✅ Encapsulation    — data + behavior in one class
//  ✅ Copy Constructor — safe deep copy inside STL vectors
// =============================================================

class UMLAttribute {
public:
    string access;    // "private" / "public" / "protected"
    string type;      // "string"  / "int" / "float"
    string name;      // "name"    / "rollNo"

    // Default Constructor
    UMLAttribute() : access(""), type(""), name("") {}

    // Parameterized Constructor
    UMLAttribute(string access, string type, string name) {
        this->access = access;
        this->type   = type;
        this->name   = name;
    }

    // -------------------------------------------------------
    // Copy Constructor — OOP CONCEPT
    // Called automatically when STL vector copies objects
    // -------------------------------------------------------
    UMLAttribute(const UMLAttribute& other) {
        this->access = other.access;
        this->type   = other.type;
        this->name   = other.name;
    }

    void display() const {
        cout << "  [ATTR]   " << access << " " << type << " " << name << "\n";
    }
};

#endif
