# UML Class Diagram → C++ Header File Converter

A C++ program that reads a plain-text file describing UML class diagrams, builds an in-memory object model, and automatically generates compilable `.h` C++ header files — one per class.

---
## Phase 1 demo:

https://github.com/user-attachments/assets/6aae2bcf-93eb-42d7-ac31-944379da3924

## Phase Roadmap

| Phase | Status | Description |
|-------|--------|-------------|
| **Phase 1** | ✅ Complete | OOP model layer (`UMLAttribute`, `UMLMethod`, `UMLClass`) + `CPPCodeGenerator` producing compilable headers |
| **Phase 2** | 🔜 Next | Wire `UMLParser` to automate input — replace hand-crafted objects with file-driven parsing |
| **Phase 3** | 🔜 Planned | Add `CodeGenerator` abstraction and `JavaCodeGenerator` / `PythonCodeGenerator` variants |
| **Phase 4** | 🔜 Planned | GUI or web front-end for drawing class diagrams visually |


# UML Class Diagram → C++ Header Generator

A C++ program that reads a plain-text file describing UML class diagrams, builds an in-memory object model using core OOP principles, and automatically generates compilable `.h` C++ header files — one per class.

---

## Table of Contents
- [Project Overview](#project-overview)
- [The 4-Layer Architecture](#the-4-layer-architecture)
- [File Structure](#file-structure)
- [Data Classes — OOP Model Layer](#data-classes--oop-model-layer)
  - [UMLAttribute](#umlattribute)
  - [UMLMethod](#umlmethod)
  - [UMLClass](#umlclass)
- [Input Format — diagram.txt](#input-format--diagramtxt)
- [Parser — UMLParser](#parser--umlparser)
- [Abstract Base — CodeGenerator](#abstract-base--codegenerator)
- [Code Generator — CPPCodeGenerator](#code-generator--cppcodegenerator)
- [Build & Run Instructions](#build--run-instructions)
- [End-to-End Walkthrough](#end-to-end-walkthrough)
- [OOP Concepts Demonstrated](#oop-concepts-demonstrated)
- [Build Order](#build-order)
- [Extending to Other Languages](#extending-to-other-languages)
- [Team](#team)

---

## Project Overview

This project is a mini-compiler pipeline built entirely in C++ that demonstrates all core Object-Oriented Programming principles in a real working system — not just as isolated examples, but as a cohesive architecture.

**The problem it solves:**
Translating a UML class diagram into C++ class declarations is repetitive, tedious, and error-prone. This tool automates that entirely. You describe your classes in a simple text file and the program generates ready-to-compile `.h` files for you.

**How it works:**
1. You describe your classes in `diagram.txt` using a simple keyword format
2. `UMLParser` reads the file line by line and builds in-memory `UMLClass` objects
3. `CPPCodeGenerator` walks those objects and emits valid C++ header files
4. Generated files land in the `output/` folder — ready to `#include` in any project

---

## The 4-Layer Architecture

```
diagram.txt  →  UMLParser  →  UML Objects  →  CPPCodeGenerator  →  output/*.h
  (input)        (parsing)     (in memory)       (generation)         (output)
```

| Layer | File(s) | Responsibility |
|---|---|---|
| **Input** | `diagram.txt` | Human-readable plain-text UML description |
| **Parser** | `UMLParser.h` | Reads file line-by-line; builds `vector<UMLClass>` |
| **Model** | `UMLAttribute.h`, `UMLMethod.h`, `UMLClass.h` | In-memory object representation of the diagram |
| **Generator** | `CodeGenerator.h`, `CPPCodeGenerator.h` | Serialises objects into `.h` files |
| **Entry Point** | `main.cpp` | Wires parser → generator; demonstrates polymorphic dispatch |

---

## File Structure

```
UML-Code-Generator/
│
├── main.cpp                ← Entry point: parser → generator pipeline
│
├── UMLAttribute.h          ← Data class: one field (access + type + name)
├── UMLMethod.h             ← Data class: one method (access + returnType + name + params)
├── UMLClass.h              ← Data class: one full class (name + attributes[] + methods[])
│
├── UMLParser.h             ← Reads diagram.txt → returns vector<UMLClass>
│
├── CodeGenerator.h         ← Abstract base class with pure virtual generate()
├── CPPCodeGenerator.h      ← Inherits CodeGenerator; writes .h files to output/
│
├── diagram.txt             ← Your input — edit this to describe your classes
│
└── output/
    └── *.h                 ← Auto-generated C++ header files land here
```

---

## Data Classes — OOP Model Layer

These three classes form the backbone of the system. They are pure data containers — no generation logic, no file I/O. This is **Encapsulation** at its clearest: each class bundles related data and a constructor into one unit.

---

### UMLAttribute

Represents a single class field.

```
private string name    →   access="private"  type="string"  name="name"
private int rollNo     →   access="private"  type="int"     name="rollNo"
public float gpa       →   access="public"   type="float"   name="gpa"
```

```cpp
class UMLAttribute {
public:
    string access;    // "private" / "public" / "protected"
    string type;      // "string"  / "int"    / "float"
    string name;      // "name"    / "rollNo" / "gpa"

    UMLAttribute() : access(""), type(""), name("") {}

    UMLAttribute(string access, string type, string name) {
        this->access = access;
        this->type   = type;
        this->name   = name;
    }

    // Copy Constructor — called automatically when STL vector resizes
    UMLAttribute(const UMLAttribute& other) {
        this->access = other.access;
        this->type   = other.type;
        this->name   = other.name;
    }
};
```

**Why the copy constructor?**
When `vector<UMLAttribute>` grows beyond its current capacity, it allocates a larger block of memory and copies every existing element into it. The explicit copy constructor ensures each field is properly duplicated into the new object — this is called during STL vector reallocation and any pass-by-value scenario.

---

### UMLMethod

Represents a single method declaration.

```
public string getName()           →  access="public"  returnType="string"  name="getName()"
public void setName(string name)  →  access="public"  returnType="void"    name="setName(string name)"
```

```cpp
class UMLMethod {
public:
    string access;
    string returnType;
    string name;
    vector<string> params;

    UMLMethod() : access(""), returnType(""), name("") {}

    // Constructor 1 — without explicit params list
    UMLMethod(string access, string returnType, string name) {
        this->access     = access;
        this->returnType = returnType;
        this->name       = name;
    }

    // Constructor 2 — with explicit params list  (Function Overloading)
    UMLMethod(string access, string returnType, string name, vector<string> params) {
        this->access     = access;
        this->returnType = returnType;
        this->name       = name;
        this->params     = params;
    }

    // Copy Constructor
    UMLMethod(const UMLMethod& other) {
        this->access     = other.access;
        this->returnType = other.returnType;
        this->name       = other.name;
        this->params     = other.params;
    }
};
```

**Two constructors = Function Overloading.** The compiler picks the correct version at compile time based on how many arguments you pass.

---

### UMLClass

The aggregate root — the main container that holds a complete class worth of UML data.

```cpp
class UMLClass {
public:
    string className;
    string parentClass;               // "Person" if EXTENDS used, else ""
    vector<UMLAttribute> attributes;
    vector<UMLMethod>    methods;

    UMLClass(string name, string parent = "") {
        this->className   = name;
        this->parentClass = parent;
    }

    // addAttribute — Overload 1: pass a UMLAttribute object
    void addAttribute(UMLAttribute attr) { attributes.push_back(attr); }

    // addAttribute — Overload 2: pass raw strings  (Function Overloading)
    void addAttribute(string access, string type, string name) {
        attributes.push_back(UMLAttribute(access, type, name));
    }

    // addMethod — Overload 1
    void addMethod(UMLMethod method) { methods.push_back(method); }

    // addMethod — Overload 2  (Function Overloading)
    void addMethod(string access, string returnType, string name) {
        methods.push_back(UMLMethod(access, returnType, name));
    }

    // operator+ for UMLAttribute  (Operator Overloading)
    UMLClass operator+(const UMLAttribute& attr) {
        attributes.push_back(attr);
        return *this;
    }

    // operator+ for UMLMethod  (Operator Overloading)
    UMLClass operator+(const UMLMethod& method) {
        methods.push_back(method);
        return *this;
    }
};
```

**Two kinds of overloading at work:**
- `addAttribute()` and `addMethod()` each have two versions — one takes an object, one takes raw strings. Compiler resolves at compile time.
- `operator+` is overloaded twice — once for `UMLAttribute`, once for `UMLMethod`. Enables intuitive syntax: `student = student + UMLAttribute(...)`.

---

## Input Format — diagram.txt

Each class block starts with `CLASS <ClassName>` and ends with `END`. Supports inheritance via `EXTENDS`. Lines starting with `//` are treated as comments and ignored.

```
// Keyword reference:
// CLASS  ClassName [EXTENDS ParentClass]
// ATTR   access  type  name
// METHOD access  returnType  signature
// END
```

**Full example:**
```
// Base class
CLASS Person
ATTR protected string name
ATTR protected int age
METHOD public string getName()
METHOD public void setName(string name)
METHOD public int getAge()
METHOD public void display()
END

// Derived class
CLASS Student EXTENDS Person
ATTR private int rollNo
ATTR private float marks
ATTR private string branch
METHOD public int getRollNo()
METHOD public float getMarks()
METHOD public void setMarks(float marks)
METHOD public void display()
END

CLASS Teacher
ATTR private string teacherName
ATTR private string subject
ATTR private int employeeId
METHOD public string getTeacherName()
METHOD public string getSubject()
METHOD public void setSubject(string subject)
METHOD public void display()
END
```

| Keyword | Syntax | Description |
|---|---|---|
| `CLASS` | `CLASS Name` or `CLASS Name EXTENDS Parent` | Starts a new class block |
| `ATTR` | `ATTR access type name` | Declares a member variable |
| `METHOD` | `METHOD access returnType signature` | Declares a method |
| `END` | `END` | Closes the current class block |
| `//` | `// comment text` | Comment line — ignored by parser |

---

## Parser — UMLParser

`UMLParser` reads `diagram.txt` line-by-line using `std::ifstream` and `std::getline`, tokenizes each line with `std::istringstream`, and drives a simple keyword-based state machine to build `UMLClass` objects.

```cpp
class UMLParser {
public:
    vector<UMLClass> parseFile(string filename);

private:
    vector<string> tokenize(const string& line);  // splits line into words
};
```

**Parsing logic:**
```
open file with ifstream
while getline reads a line:

    skip if line is empty
    skip if line starts with "//"

    tokenize line into words via istringstream

    if token[0] == "CLASS":
        if a class was being built → save it to result vector
        create new UMLClass from token[1]
        if token[2] == "EXTENDS" → set parentClass = token[3]

    if token[0] == "ATTR":
        create UMLAttribute {access=token[1], type=token[2], name=token[3]}
        call currentClass->addAttribute(...)

    if token[0] == "METHOD":
        access     = token[1]
        returnType = token[2]
        signature  = join token[3..end]   (handles multi-word signatures)
        call currentClass->addMethod(...)

    if token[0] == "END":
        push currentClass into result vector
        reset currentClass = nullptr

return result vector
```

**Key standard library components used:**

| Component | Purpose |
|---|---|
| `std::ifstream` | Opens and reads the input file sequentially |
| `std::getline` | Reads one newline-delimited line at a time |
| `std::istringstream` | Splits a line into whitespace-separated tokens |
| `std::vector<UMLClass>` | Stores all parsed classes to return to caller |

---

## Abstract Base — CodeGenerator

`CodeGenerator` is a **pure abstract class** — it cannot be instantiated directly. It defines the interface that every generator must implement.

```cpp
class CodeGenerator {
public:
    virtual void generate(UMLClass& cls) = 0;   // pure virtual
    virtual void printStatus(const string& filename);
    virtual ~CodeGenerator();                    // virtual destructor
};
```

**Why abstract?**
- Forces every subclass to implement `generate()` — compiler enforces this
- `main.cpp` uses a `CodeGenerator*` pointer without knowing which language is being generated
- Adding `JavaCodeGenerator` or `PythonCodeGenerator` requires zero changes to `main.cpp`

**Why virtual destructor?**
When `delete` is called on a `CodeGenerator*` that holds a `CPPCodeGenerator`, C++ uses the vtable to call `CPPCodeGenerator::~CPPCodeGenerator()` first, then `CodeGenerator::~CodeGenerator()`. Without `virtual`, only the base destructor runs — undefined behavior and potential resource leak.

---

## Code Generator — CPPCodeGenerator

`CPPCodeGenerator` inherits from `CodeGenerator` and overrides `generate()` with C++-specific output logic. For each `UMLClass` it receives, it opens `output/<ClassName>.h` and writes a valid C++ header file.

```cpp
class CPPCodeGenerator : public CodeGenerator {
public:
    void generate(UMLClass& cls) override;
    void printStatus(const string& filename) override;
    ~CPPCodeGenerator();
};
```

**Generation logic:**
```
build filename = "output/" + className + ".h"
open with ofstream

write include guard  (#ifndef / #define)
write #include <string>, #include <vector>, using namespace std

write class declaration:
    "class ClassName {"               ← no parent
    "class ClassName : public Parent" ← if EXTENDS was used

write "private:" section:
    for each attribute where access == "private" → write "    type name;"
    for each method   where access == "private" → write "    returnType name;"

write "public:" section:
    for each attribute where access == "public" → write "    type name;"
    for each method   where access == "public"  → write "    returnType name;"

if anything is "protected":
    write "protected:" section

write "};"
write "#endif"
close file
```

---

## Build & Run Instructions

**Requirements:** Any C++11-compatible compiler (`g++`, `clang++`, MSVC)

```bash
# Step 1 — Compile
g++ main.cpp -o generator

# Step 2 — Create output folder (first time only)
mkdir -p output

# Step 3 — Run
./generator          # Linux / Mac
generator.exe        # Windows
```

**To test your own classes:**
1. Open `diagram.txt`
2. Add your class blocks using the keyword format above
3. Save and re-run `./generator`
4. Check `output/` for generated `.h` files

**Expected terminal output:**
```
[UMLParser] Reading: diagram.txt
  Found CLASS: Person
  Found CLASS: Student (extends Person)
  Found CLASS: Teacher
  Found CLASS: Course
[UMLParser] Done. Parsed 4 class(es).

[CPPCodeGenerator] Generating: output/Person.h
  Done → output/Person.h
[CPPCodeGenerator] Generating: output/Student.h
  Done → output/Student.h
...

Done! 4 file(s) written to output/
[CPPCodeGenerator] Destructor called.
[CodeGenerator] Destructor called.
```

The destructor messages at the end confirm the **virtual destructor chain** fired correctly — derived destructor first, then base.

---

## End-to-End Walkthrough

**Input (`diagram.txt`):**
```
CLASS Student EXTENDS Person
ATTR private int rollNo
ATTR private float marks
METHOD public int getRollNo()
METHOD public void setMarks(float marks)
METHOD public void display()
END
```

**Generated (`output/Student.h`):**
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
using namespace std;

class Student : public Person {
private:
    int rollNo;
    float marks;

public:
    int getRollNo();
    void setMarks(float marks);
    void display();
};

#endif
```

**What happened step by step:**
1. `UMLParser::parseFile()` opened `diagram.txt` with `ifstream`
2. Saw `CLASS Student EXTENDS Person` → created `UMLClass("Student", "Person")`
3. Saw `ATTR private int rollNo` → called `addAttribute("private", "int", "rollNo")`
4. Saw `METHOD public int getRollNo()` → called `addMethod("public", "int", "getRollNo()")`
5. Saw `END` → pushed completed `UMLClass` into result vector
6. `main.cpp` called `gen->generate(student)` via polymorphic base-class pointer
7. C++ resolved the vtable → called `CPPCodeGenerator::generate()`
8. File written to `output/Student.h`

---

## OOP Concepts Demonstrated

| Concept | Where | How |
|---|---|---|
| **Encapsulation** | `UMLAttribute`, `UMLMethod`, `UMLClass` | Data + constructor + behavior bundled in one unit |
| **Abstraction** | `CodeGenerator` | Pure virtual `generate()` hides implementation behind interface |
| **Inheritance** | `CPPCodeGenerator : public CodeGenerator` | Derives interface and behaviour from abstract base |
| **Polymorphism** | `CodeGenerator* gen = new CPPCodeGenerator()` | Virtual dispatch resolves correct `generate()` at runtime via vtable |
| **Function Overloading** | `addAttribute()`, `addMethod()`, `UMLMethod` constructors | Same name, different parameter signatures — resolved at compile time |
| **Operator Overloading** | `operator+` in `UMLClass` | `student = student + UMLAttribute(...)` and `+ UMLMethod(...)` |
| **Copy Constructor** | `UMLAttribute`, `UMLMethod` | Explicit copy ctor invoked during STL vector reallocation and pass-by-value |
| **Virtual Destructor** | `CodeGenerator` | Correct derived→base destructor chain when `delete gen` is called |

---

## Build Order

Follow this order when writing the code from scratch — each file only depends on files listed above it:

```
1. UMLAttribute.h        — no dependencies
2. UMLMethod.h           — no dependencies
3. UMLClass.h            — depends on UMLAttribute.h and UMLMethod.h
4. diagram.txt           — write your test input
5. CodeGenerator.h       — abstract base, depends on UMLClass.h
6. UMLParser.h           — depends on UMLClass.h
7. CPPCodeGenerator.h    — depends on CodeGenerator.h and UMLClass.h
8. main.cpp              — depends on everything above
```

---

## Extending to Other Languages

The architecture is designed to be **open for extension, closed for modification**. To add a Java generator:

```cpp
class JavaCodeGenerator : public CodeGenerator {
public:
    void generate(UMLClass& cls) override {
        // open output/ClassName.java
        // write: public class ClassName { ... }
        // write: private type name;
        // write: public returnType name() { }
    }
};
```

Then in `main.cpp`, swap **one line**:
```cpp
CodeGenerator* gen = new JavaCodeGenerator();  // nothing else changes
```

The rest of `main.cpp` is untouched. That is polymorphism and the Open/Closed Principle working together.

---

**Course:** Object Oriented Programming in C++ — CSE1003B
**Institute:** MIT World Peace University, Pune
**Year:** SY CSE — 2025-26


