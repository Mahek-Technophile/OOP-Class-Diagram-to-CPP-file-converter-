#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <string>
#include <iostream>
#include "UMLClass.h"
using namespace std;

// =============================================================
//  CodeGenerator — ABSTRACT BASE CLASS
//
//  OOP CONCEPTS:
//  ✅ Abstraction     — pure virtual generate() hides HOW code
//                       is written; only exposes WHAT to do
//  ✅ Polymorphism    — each subclass overrides generate() with
//                       its own language-specific logic
//  ✅ Inheritance     — CPPCodeGenerator inherits from this
//
//  You CANNOT instantiate CodeGenerator directly.
//  Must subclass and implement generate().
//  A future JavaCodeGenerator would just override generate().
// =============================================================

class CodeGenerator {
public:

    // -------------------------------------------------------
    // Pure Virtual Function — makes this class ABSTRACT
    // OOP CONCEPT: Abstraction + Polymorphism
    // -------------------------------------------------------
    virtual void generate(UMLClass& cls) = 0;

    // -------------------------------------------------------
    // Virtual helper — can be overridden by subclasses
    // -------------------------------------------------------
    virtual void printStatus(const string& filename) {
        cout << "[CodeGenerator] Writing: " << filename << "\n";
    }

    // -------------------------------------------------------
    // Virtual Destructor — OOP BEST PRACTICE
    // Ensures derived class destructor is called properly
    // ✅ OOP CONCEPT: Virtual Destructor
    // -------------------------------------------------------
    virtual ~CodeGenerator() {
        cout << "[CodeGenerator] Destructor called.\n";
    }
};

#endif
