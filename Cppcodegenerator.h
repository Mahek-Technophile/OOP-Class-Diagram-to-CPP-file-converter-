#ifndef CPPCODEGENERATOR_H
#define CPPCODEGENERATOR_H
 
#include <iostream>
#include <fstream>
#include <string>
#include "UMLClass.h"
using namespace std;
 
// This class READS a UMLClass object and WRITES a .h file
// This is the CORE OUTPUT ENGINE of the project
 
class CPPCodeGenerator {
public:
 
    void generate(UMLClass& cls) {
 
        // ---- Create the output file ----
        // e.g. if className = "Student", file = "output/Student.h"
        string filename = "output/" + cls.className + ".h";
        ofstream outFile(filename);
 
        if (!outFile.is_open()) {
            cout << "ERROR: Could not create file: " << filename << endl;
            cout << "Make sure the 'output' folder exists!" << endl;
            return;
        }
 
        // ---- Write: class Student { ----
        outFile << "class " << cls.className << " {" << endl;
 
        // ---- Write PRIVATE section ----
        // Loop through all attributes and write the private ones
        outFile << "private:" << endl;
        for (auto& attr : cls.attributes) {
            if (attr.access == "private") {
                outFile << "    " << attr.type << " " << attr.name << ";" << endl;
            }
        }
 
        // ---- Write PUBLIC section ----
        outFile << endl << "public:" << endl;
 
        // Public attributes (rare but possible)
        for (auto& attr : cls.attributes) {
            if (attr.access == "public") {
                outFile << "    " << attr.type << " " << attr.name << ";" << endl;
            }
        }
 
        // Public methods
        for (auto& method : cls.methods) {
            if (method.access == "public") {
                outFile << "    " << method.returnType << " " << method.name << ";" << endl;
            }
        }
 
        // ---- Write: }; ----
        outFile << "};" << endl;
 
        outFile.close();
        cout << "SUCCESS: Generated " << filename << endl;
    }
};
 
#endif
 