#ifndef UMLPARSER_H
#define UMLPARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "UMLClass.h"
using namespace std;

// =============================================================
//  UMLParser — reads a diagram.txt file line by line
//  and builds a vector of UMLClass objects from it
//
//  INPUT FORMAT (diagram.txt):
//
//    CLASS Student
//    ATTR private string name
//    ATTR private int rollNo
//    METHOD public string getName()
//    METHOD public void setName(string name)
//    END
//
//    CLASS Teacher EXTENDS Person
//    ATTR private string subject
//    METHOD public string getSubject()
//    END
//
//  OOP CONCEPTS:
//  ✅ Encapsulation — parsing logic hidden inside this class
//  ✅ Abstraction   — caller just calls parseFile() and gets objects
//                     doesn't need to know HOW parsing works
// =============================================================

class UMLParser {
public:

    // -------------------------------------------------------
    // parseFile — main public method
    // Opens the file, reads line by line, builds UMLClass objects
    // Returns vector of all parsed classes
    // -------------------------------------------------------
    vector<UMLClass> parseFile(string filename) {

        vector<UMLClass> classes;
        ifstream inFile(filename);

        if (!inFile.is_open()) {
            cout << "[UMLParser] ERROR: Cannot open file: " << filename << "\n";
            return classes;
        }

        cout << "[UMLParser] Reading: " << filename << "\n";

        string line;
        UMLClass* current = nullptr;   // pointer to the class being built

        while (getline(inFile, line)) {

            // Skip empty lines and comment lines (start with //)
            if (line.empty() || line.substr(0, 2) == "//") continue;

            // Tokenize the line into words
            vector<string> tokens = tokenize(line);
            if (tokens.empty()) continue;

            string keyword = tokens[0];

            // -------------------------------------------
            // CLASS keyword — start a new class
            // Format: CLASS ClassName
            //      or CLASS ClassName EXTENDS ParentName
            // -------------------------------------------
            if (keyword == "CLASS") {
                // If we were building a class, save it first
                if (current != nullptr) {
                    classes.push_back(*current);
                    delete current;
                }

                string className = tokens[1];
                string parentName = "";

                // Check for EXTENDS keyword (inheritance)
                if (tokens.size() >= 4 && tokens[2] == "EXTENDS") {
                    parentName = tokens[3];
                }

                current = new UMLClass(className, parentName);
                cout << "  Found CLASS: " << className;
                if (!parentName.empty()) cout << " (extends " << parentName << ")";
                cout << "\n";
            }

            // -------------------------------------------
            // ATTR keyword — add an attribute
            // Format: ATTR access type name
            // e.g.    ATTR private string name
            // -------------------------------------------
            else if (keyword == "ATTR" && current != nullptr) {
                if (tokens.size() >= 4) {
                    string access = tokens[1];   // "private"
                    string type   = tokens[2];   // "string"
                    string name   = tokens[3];   // "name"
                    current->addAttribute(access, type, name);
                }
            }

            // -------------------------------------------
            // METHOD keyword — add a method
            // Format: METHOD access returnType fullSignature
            // e.g.    METHOD public string getName()
            //         METHOD public void setName(string name)
            // -------------------------------------------
            else if (keyword == "METHOD" && current != nullptr) {
                if (tokens.size() >= 4) {
                    string access     = tokens[1];   // "public"
                    string returnType = tokens[2];   // "string"

                    // Everything from token[3] onward is the method signature
                    // This handles cases like: setName(string name)
                    string sig = "";
                    for (int i = 3; i < (int)tokens.size(); i++) {
                        if (i > 3) sig += " ";
                        sig += tokens[i];
                    }

                    current->addMethod(access, returnType, sig);
                }
            }

            // -------------------------------------------
            // END keyword — finish building the current class
            // -------------------------------------------
            else if (keyword == "END" && current != nullptr) {
                classes.push_back(*current);
                delete current;
                current = nullptr;
            }
        }

        // Handle last class if END was missing
        if (current != nullptr) {
            classes.push_back(*current);
            delete current;
        }

        inFile.close();
        cout << "[UMLParser] Done. Parsed " << classes.size() << " class(es).\n\n";
        return classes;
    }

private:

    // -------------------------------------------------------
    // tokenize — splits a line into words by whitespace
    // -------------------------------------------------------
    vector<string> tokenize(const string& line) {
        vector<string> tokens;
        istringstream iss(line);
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

#endif
