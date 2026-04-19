#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <string>
#include <vector>
#include <iostream>
#include "UMLAttribute.h"
#include "UMLMethod.h"
using namespace std;

// =============================================================
//  UMLClass — the MAIN container
//  Represents a complete class from the UML diagram
//
//  OOP CONCEPTS:
//  ✅ Encapsulation       — className, attributes, methods bundled
//  ✅ Function Overloading— addAttribute() and addMethod() have
//                           two versions each (object vs raw strings)
//  ✅ Operator Overloading— operator+ works for both UMLAttribute
//                           and UMLMethod (detects type automatically)
// =============================================================

class UMLClass {
public:
    string className;                    // "Student" / "Teacher"
    string parentClass;                  // for inheritance: "Person" or ""
    vector<UMLAttribute> attributes;
    vector<UMLMethod>    methods;

    // Constructor
    UMLClass(string name, string parent = "") {
        this->className   = name;
        this->parentClass = parent;
    }

    // -------------------------------------------------------
    // addAttribute — Overload 1: UMLAttribute object
    // -------------------------------------------------------
    void addAttribute(UMLAttribute attr) {
        attributes.push_back(attr);
    }

    // -------------------------------------------------------
    // addAttribute — Overload 2: raw strings
    // OOP CONCEPT: Function Overloading
    // -------------------------------------------------------
    void addAttribute(string access, string type, string name) {
        attributes.push_back(UMLAttribute(access, type, name));
    }

    // -------------------------------------------------------
    // addMethod — Overload 1: UMLMethod object
    // -------------------------------------------------------
    void addMethod(UMLMethod method) {
        methods.push_back(method);
    }

    // -------------------------------------------------------
    // addMethod — Overload 2: raw strings
    // OOP CONCEPT: Function Overloading
    // -------------------------------------------------------
    void addMethod(string access, string returnType, string name) {
        methods.push_back(UMLMethod(access, returnType, name));
    }

    // -------------------------------------------------------
    // operator+ for UMLAttribute
    // OOP CONCEPT: Operator Overloading
    // Usage: student = student + UMLAttribute("private","int","age")
    // -------------------------------------------------------
    UMLClass operator+(const UMLAttribute& attr) {
        attributes.push_back(attr);
        return *this;
    }

    // -------------------------------------------------------
    // operator+ for UMLMethod
    // OOP CONCEPT: Operator Overloading (same operator, diff type)
    // Usage: student = student + UMLMethod("public","void","show()")
    // -------------------------------------------------------
    UMLClass operator+(const UMLMethod& method) {
        methods.push_back(method);
        return *this;
    }

    // Display summary of the class
    void display() const {
        cout << "\nClass: " << className;
        if (!parentClass.empty()) cout << " extends " << parentClass;
        cout << "\n";
        for (auto& a : attributes) a.display();
        for (auto& m : methods)    m.display();
    }
};

#endif
