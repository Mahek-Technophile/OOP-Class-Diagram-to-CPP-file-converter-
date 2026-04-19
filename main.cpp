#include <iostream>
#include <vector>
#include "UMLAttribute.h"
#include "UMLMethod.h"
#include "UMLClass.h"
#include "UMLParser.h"
#include "CodeGenerator.h"
#include "CPPCodeGenerator.h"
using namespace std;

// =============================================================
//  UML Class Diagram Code Generator — main.cpp
//
//  HOW IT WORKS:
//  1. UMLParser reads diagram.txt → builds UMLClass objects
//  2. CPPCodeGenerator loops over them → writes .h files
//
//  All OOP concepts demonstrated:
//  ✅ Encapsulation       (UMLAttribute, UMLMethod, UMLClass)
//  ✅ Abstraction         (CodeGenerator abstract base class)
//  ✅ Inheritance         (CPPCodeGenerator : public CodeGenerator)
//  ✅ Polymorphism        (generate() overridden in CPPCodeGenerator)
//  ✅ Function Overloading(addAttribute/addMethod — 2 versions each)
//  ✅ Operator Overloading(operator+ for UMLAttribute and UMLMethod)
//  ✅ Copy Constructor    (UMLAttribute and UMLMethod copy ctors)
//  ✅ Virtual Destructor  (CodeGenerator base class)
// =============================================================

int main() {

    cout << "=====================================================\n";
    cout << "   UML Class Diagram Code Generator in C++\n";
    cout << "   MIT-WPU | SYCSE | OOP Mini Project\n";
    cout << "=====================================================\n\n";

    // ----------------------------------------------------------
    // STEP 1: Parse diagram.txt → get vector of UMLClass objects
    // ----------------------------------------------------------
    UMLParser parser;
    vector<UMLClass> classes = parser.parseFile("diagram.txt");

    if (classes.empty()) {
        cout << "No classes found. Check diagram.txt.\n";
        return 1;
    }

    // Show what was parsed
    cout << "Parsed classes:\n";
    for (auto& cls : classes) cls.display();
    cout << "\n";

    // ----------------------------------------------------------
    // STEP 2: Use POLYMORPHISM — CodeGenerator pointer points
    //         to CPPCodeGenerator (runtime binding)
    // ----------------------------------------------------------
    CodeGenerator* gen = new CPPCodeGenerator();   // ← Polymorphism

    cout << "=====================================================\n";
    cout << "Generating C++ header files...\n";
    cout << "=====================================================\n";

    for (UMLClass& cls : classes) {
        gen->generate(cls);    // ← virtual dispatch → CPPCodeGenerator::generate()
    }

    cout << "\n=====================================================\n";
    cout << "Done! " << classes.size() << " file(s) written to output/\n";
    cout << "=====================================================\n\n";

    // ----------------------------------------------------------
    // STEP 3: Also demo operator+ overloading inline
    // ----------------------------------------------------------
    cout << "--- operator+ Overloading Demo ---\n";
    UMLClass extra("ExtraDemo");
    extra = extra + UMLAttribute("private", "string", "demoField");
    extra = extra + UMLMethod("public", "void", "demoMethod()");
    gen->generate(extra);

    // ----------------------------------------------------------
    // Cleanup — delete calls virtual destructor chain
    // ✅ Virtual Destructor in action
    // ----------------------------------------------------------
    delete gen;

    return 0;
}
