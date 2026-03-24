# UML Class Diagram → C++ Header File Converter

A C++ program that reads a plain-text file describing UML class diagrams, builds an in-memory object model, and automatically generates compilable `.h` C++ header files — one per class.

---

## Table of Contents

- [Project Overview](#project-overview)
- [The 4-Layer Architecture](#the-4-layer-architecture)
- [File Structure](#file-structure)
- [Data Classes (OOP Model Layer)](#data-classes-oop-model-layer)
  - [UMLAttribute](#umlattribute)
  - [UMLMethod](#umlmethod)
  - [UMLClass](#umlclass)
- [Input Format — `diagram.txt`](#input-format--diagramtxt)
- [Parser — `UMLParser`](#parser--umlparser)
- [Code Generator — `CPPCodeGenerator`](#code-generator--cppcodegenerator)
- [Build & Run Instructions](#build--run-instructions)
- [Example: End-to-End Walkthrough](#example-end-to-end-walkthrough)
- [OOP Concepts Demonstrated](#oop-concepts-demonstrated)
- [Build Order Summary](#build-order-summary)
- [Phase Roadmap](#phase-roadmap)

---

## Project Overview

This project is an educational tool that demonstrates core **Object-Oriented Programming** principles by implementing a mini-compiler pipeline:

1. You describe your classes in a simple text file (`diagram.txt`).
2. The **Parser** reads each line and constructs in-memory UML objects.
3. The **Code Generator** walks those objects and emits valid C++ header files.

The result: type `CLASS Student … END` in a text file and get a ready-to-use `Student.h` in the `output/` folder.

---

## The 4-Layer Architecture

```
diagram.txt  →  UMLParser  →  UML Objects  →  CPPCodeGenerator  →  Student.h
  (input)       (parsing)     (in memory)       (generation)        (output)
```

| Layer | Responsibility |
|-------|---------------|
| **Input** (`diagram.txt`) | Human-readable description of UML classes |
| **Parser** (`UMLParser`) | Reads the file line-by-line; builds `UMLClass` objects |
| **UML Objects** (`UMLClass`, `UMLAttribute`, `UMLMethod`) | In-memory representation of the diagram |
| **Generator** (`CPPCodeGenerator`) | Serialises objects into `.h` files |

---

## File Structure

```
UML-Code-Generator/
├── main.cpp                  ← Entry point: wires parser → generator
├── UMLAttribute.h            ← Data class: one field (access + type + name)
├── UMLMethod.h               ← Data class: one method (access + return type + name + params)
├── UMLClass.h                ← Data class: one class (name + attributes + methods)
├── UMLParser.h               ← Parser interface declaration
├── UMLParser.cpp             ← Parser implementation (reads diagram.txt)
├── CodeGenerator.h           ← Abstract base class for generators
├── CPPCodeGenerator.h        ← C++ generator interface declaration
├── CPPCodeGenerator.cpp      ← C++ generator implementation (writes .h files)
├── diagram.txt               ← Your test input (describe your UML classes here)
└── output/
    └── *.h                   ← Generated C++ header files land here
```

---

## Data Classes (OOP Model Layer)

These three classes form the **backbone** of the system — they hold data and have no generation logic (pure encapsulation).

### UMLAttribute

Represents a single class field, e.g. `private string name`.

```cpp
// UMLAttribute.h
class UMLAttribute {
public:
    string access;   // "private" or "public"
    string type;     // e.g. "string", "int", "double"
    string name;     // e.g. "name", "rollNo"
};
```

### UMLMethod

Represents a single method declaration, e.g. `public string getName()`.

```cpp
// UMLMethod.h
class UMLMethod {
public:
    string access;             // "private" or "public"
    string returnType;         // e.g. "string", "void", "int"
    string name;               // e.g. "getName", "setName"
    vector<string> parameters; // e.g. {"string", "int"}
};
```

### UMLClass

The main container — holds one complete class worth of UML data.

```cpp
// UMLClass.h
#include "UMLAttribute.h"
#include "UMLMethod.h"

class UMLClass {
public:
    string className;                  // e.g. "Student"
    vector<UMLAttribute> attributes;   // all fields
    vector<UMLMethod> methods;         // all methods
};
```

---

## Input Format — `diagram.txt`

Each class block starts with `CLASS <ClassName>` and ends with `END`.  
Inside the block, use `ATTR` for fields and `METHOD` for methods.

```
CLASS Student
ATTR private string name
ATTR private int rollNo
METHOD public string getName()
METHOD public void setName(string)
END

CLASS Teacher
ATTR private string subject
ATTR private int employeeId
METHOD public string getSubject()
METHOD public void setEmployeeId(int)
END
```

### Keyword reference

| Keyword | Syntax | Description |
|---------|--------|-------------|
| `CLASS` | `CLASS <Name>` | Starts a new class block |
| `ATTR` | `ATTR <access> <type> <name>` | Declares a member variable |
| `METHOD` | `METHOD <access> <returnType> <name>(<params>)` | Declares a method |
| `END` | `END` | Closes the current class block |

---

## Parser — `UMLParser`

`UMLParser` reads `diagram.txt` line-by-line using `ifstream` and `istringstream`, and returns a `vector<UMLClass>`.

**Parsing logic (pseudocode):**

```
open file
while (read each line):
    split line into tokens

    if token[0] == "CLASS":
        create new UMLClass; store className = token[1]

    if token[0] == "ATTR":
        create UMLAttribute {access=token[1], type=token[2], name=token[3]}
        append to currentClass.attributes

    if token[0] == "METHOD":
        parse "name(param1, param2, …)" from remaining tokens
        create UMLMethod {access, returnType, name, parameters}
        append to currentClass.methods

    if token[0] == "END":
        push currentClass into result vector

return result vector
```

**Key C++ standard library components used:**
- `std::ifstream` — opens and reads the input file
- `std::getline` — reads one line at a time
- `std::istringstream` — splits a line into whitespace-separated tokens
- `std::vector` — stores the collection of parsed classes

---

## Code Generator — `CPPCodeGenerator`

`CPPCodeGenerator` inherits from the abstract `CodeGenerator` base class and overrides the `generate()` method.  
For each `UMLClass` it receives, it opens `output/<ClassName>.h` and writes a valid C++ header.

**Generation logic (pseudocode):**

```
open output/<ClassName>.h for writing

write "#pragma once"
write ""
write "class <ClassName> {"

write "private:"
for each attribute where access == "private":
    write "    <type> <name>;"

write ""
write "public:"
for each attribute where access == "public":
    write "    <type> <name>;"

for each method where access == "public":
    write "    <returnType> <name>(<parameters>);"

write "};"

close file
```

**Abstract base class** (`CodeGenerator.h`):

```cpp
class CodeGenerator {
public:
    virtual void generate(const UMLClass& cls) = 0;  // pure virtual
    virtual ~CodeGenerator() = default;
};
```

This design means you can later add `JavaCodeGenerator`, `PythonCodeGenerator`, etc. by simply inheriting from `CodeGenerator` — a direct application of the **Open/Closed Principle**.

---

## Build & Run Instructions

### Prerequisites

- A C++17-compatible compiler (g++ ≥ 7 or clang++ ≥ 5)
- `make` (optional but recommended)

### Compile manually

```bash
g++ -std=c++17 -Wall -o uml_converter \
    main.cpp \
    UMLParser.cpp \
    CPPCodeGenerator.cpp
```

### Run

```bash
./uml_converter
```

The program reads `diagram.txt` from the current directory and writes header files into the `output/` folder.  
Make sure the `output/` directory exists before running:

```bash
mkdir -p output
./uml_converter
```

### Expected output

```
output/
├── Student.h
└── Teacher.h
```

---

## Example: End-to-End Walkthrough

**Input (`diagram.txt`):**

```
CLASS Student
ATTR private string name
ATTR private int rollNo
METHOD public string getName()
METHOD public void setName(string)
END
```

**Generated (`output/Student.h`):**

```cpp
#pragma once

class Student {
private:
    string name;
    int rollNo;

public:
    string getName();
    void setName(string);
};
```

---

## OOP Concepts Demonstrated

| Concept | Where it appears |
|---------|-----------------|
| **Encapsulation** | `UMLAttribute`, `UMLMethod`, `UMLClass` bundle related data into objects |
| **Composition** | `UMLClass` contains vectors of `UMLAttribute` and `UMLMethod` |
| **Abstraction** | `CodeGenerator` exposes only `generate()` — implementation details are hidden |
| **Inheritance** | `CPPCodeGenerator` extends `CodeGenerator` |
| **Polymorphism** | Swapping in `JavaCodeGenerator` requires zero changes to `main.cpp` |

---

## Build Order Summary

Follow this order when writing the code from scratch:

1. **`UMLAttribute.h`** — simplest file, no dependencies
2. **`UMLMethod.h`** — same level, no dependencies
3. **`UMLClass.h`** — depends on the two above
4. **`diagram.txt`** — write your test input by hand
5. **`CodeGenerator.h`** — abstract base (pure virtual interface)
6. **`UMLParser.h` / `UMLParser.cpp`** — reads `diagram.txt`, fills `UMLClass` objects
7. **`CPPCodeGenerator.h` / `CPPCodeGenerator.cpp`** — generates `.h` files
8. **`main.cpp`** — connects parser → generator and drives the whole pipeline

---

## Phase Roadmap

| Phase | Status | Description |
|-------|--------|-------------|
| **Phase 1** | ✅ Complete | OOP model layer (`UMLAttribute`, `UMLMethod`, `UMLClass`) + `CPPCodeGenerator` producing compilable headers |
| **Phase 2** | 🔜 Next | Wire `UMLParser` to automate input — replace hand-crafted objects with file-driven parsing |
| **Phase 3** | 🔜 Planned | Add `CodeGenerator` abstraction and `JavaCodeGenerator` / `PythonCodeGenerator` variants |
| **Phase 4** | 🔜 Planned | GUI or web front-end for drawing class diagrams visually |

---

> **Phase 1 target:** Implement the OOP model layer (`UMLAttribute`, `UMLMethod`, `UMLClass`) with proper encapsulation, and the `CPPCodeGenerator` that produces compilable C++ header files from those objects. `UMLParser` is **not** part of Phase 1 — connecting the parser to automate file-driven input is the Phase 2 goal.