#ifndef CPPCODEGENERATOR_H
#define CPPCODEGENERATOR_H

#include <fstream>
#include <iostream>
#include <string>
#include "CodeGenerator.h"
#include "UMLClass.h"
using namespace std;

// =============================================================
//  CPPCodeGenerator — generates C++ .h files from UMLClass data
//
//  OOP CONCEPTS:
//  ✅ Inheritance    — inherits interface from CodeGenerator
//  ✅ Polymorphism   — overrides generate() with C++ logic
//  ✅ Encapsulation  — generation logic hidden inside this class
// =============================================================

class CPPCodeGenerator : public CodeGenerator {    // ← Inheritance

public:

    // -------------------------------------------------------
    // generate() — OOP CONCEPT: Polymorphism (method overriding)
    // Reads a UMLClass → writes a properly formatted .h file
    // -------------------------------------------------------
    void generate(UMLClass& cls) override {

        string filename = "output/" + cls.className + ".h";
        printStatus(filename);

        ofstream out(filename);
        if (!out.is_open()) {
            cout << "  ERROR: Cannot create " << filename << "\n";
            return;
        }

        // ── 1. Include guard ───────────────────────────────
        string guard = cls.className;
        for (char& c : guard) c = toupper(c);
        out << "#ifndef " << guard << "_H\n";
        out << "#define " << guard << "_H\n\n";
        out << "#include <string>\n";
        out << "#include <vector>\n";
        out << "using namespace std;\n\n";

        // ── 2. Class declaration (handle inheritance) ──────
        out << "class " << cls.className;
        if (!cls.parentClass.empty()) {
            out << " : public " << cls.parentClass;   // e.g. class Student : public Person
        }
        out << " {\n";

        // ── 3. private: section ────────────────────────────
        out << "private:\n";
        bool hasPrivate = false;
        for (UMLAttribute& a : cls.attributes)
            if (a.access == "private") { out << "    " << a.type << " " << a.name << ";\n"; hasPrivate = true; }
        for (UMLMethod& m : cls.methods)
            if (m.access == "private") { out << "    " << m.returnType << " " << m.name << ";\n"; hasPrivate = true; }
        if (!hasPrivate) out << "    // (none)\n";

        // ── 4. public: section ─────────────────────────────
        out << "\npublic:\n";
        bool hasPublic = false;
        for (UMLAttribute& a : cls.attributes)
            if (a.access == "public") { out << "    " << a.type << " " << a.name << ";\n"; hasPublic = true; }
        for (UMLMethod& m : cls.methods)
            if (m.access == "public") { out << "    " << m.returnType << " " << m.name << ";\n"; hasPublic = true; }
        if (!hasPublic) out << "    // (none)\n";

        // ── 5. protected: section (only if needed) ─────────
        bool hasProtected = false;
        for (auto& a : cls.attributes) if (a.access == "protected") hasProtected = true;
        for (auto& m : cls.methods)    if (m.access == "protected")  hasProtected = true;

        if (hasProtected) {
            out << "\nprotected:\n";
            for (UMLAttribute& a : cls.attributes)
                if (a.access == "protected") out << "    " << a.type << " " << a.name << ";\n";
            for (UMLMethod& m : cls.methods)
                if (m.access == "protected") out << "    " << m.returnType << " " << m.name << ";\n";
        }

        // ── 6. Close class + include guard ─────────────────
        out << "};\n\n#endif\n";
        out.close();
        cout << "  Done → " << filename << "\n";
    }

    // -------------------------------------------------------
    // printStatus — OOP CONCEPT: Polymorphism (overriding parent)
    // -------------------------------------------------------
    void printStatus(const string& filename) override {
        cout << "[CPPCodeGenerator] Generating: " << filename << "\n";
    }

    ~CPPCodeGenerator() {
        cout << "[CPPCodeGenerator] Destructor called.\n";
    }
};

#endif
