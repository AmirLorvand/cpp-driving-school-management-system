# C++ Driving School Management System

This project is a console-based **Driving School Management System** developed in **C++**. It was originally created as a solo university coursework project and demonstrates object-oriented programming, CSV file handling, data management, and basic scheduling logic.

The system manages learners, instructors, cars, and driving lessons using structured C++ classes and CSV files.

---

## Project Timeline

* **Originally completed:** 2024
* **Refactored and published on GitHub:** 2026
* **Context:** Solo university coursework project

This repository has been cleaned and documented for portfolio purposes.

---

## Data Privacy Note

The CSV files included in this repository contain **fake sample data only**.
They are used purely to demonstrate how the system reads, stores, and manages learner, instructor, and lesson records.

No real personal information is included.

---

## Features

* Manage driving school members/learners
* Manage instructor records
* Manage car information
* Manage lesson bookings
* Read and write data using CSV files
* Store structured information using C++ classes
* Demonstrate relationships between learners, instructors, cars, and lessons
* Console-based program flow

---

## Technologies Used

* C++
* Object-Oriented Programming
* CSV file handling
* Console input/output
* Makefile

---

## Project Structure

```text
.
├── main.cpp
├── Person.h
├── Person.cpp
├── Member.h
├── Member.cpp
├── Instructor.h
├── Instructor.cpp
├── Car.h
├── Car.cpp
├── Lesson.h
├── Lesson.cpp
├── Date.h
├── Date.cpp
├── members.csv
├── instructors.csv
├── lessons.csv
├── Makefile
├── .gitignore
└── README.md
```

---

## Main Classes

### `Person`

Base class for shared personal information.

### `Member`

Represents a learner/member of the driving school.

### `Instructor`

Represents a driving instructor and their related information.

### `Car`

Represents a car used by the driving school.

### `Lesson`

Represents a driving lesson booking between a learner and an instructor.

### `Date`

Represents date-related information used in the system.

---

## How to Compile

Use the Makefile:

```bash
make
```

This compiles the C++ source files and creates the executable.

---

## How to Run

```bash
./output
```

If your Makefile creates a different executable name, run that file instead.

---

## How to Clean Build Files

```bash
make clean
```

This removes generated build files.

---

## Example Data Files

The system uses CSV files such as:

```text
members.csv
instructors.csv
lessons.csv
```

These files contain fake demonstration data and are included so the program can be tested without needing external data.

---

## What I Learned

Through this solo coursework project, I practised:

* Designing a C++ application using multiple classes
* Applying object-oriented programming principles
* Reading and managing CSV data
* Modelling a real-world management system
* Working with relationships between learners, instructors, cars, and lessons
* Structuring a C++ project for GitHub
* Preparing an older coursework project for portfolio presentation

---

## Future Improvements

Possible improvements include:

* Improving input validation
* Adding more robust error handling for missing or invalid CSV files
* Refactoring the project into `src`, `include`, and `data` folders
* Adding unit tests
* Improving lesson search and filtering
* Adding persistent update functionality for all records
* Adding a graphical user interface
* Replacing CSV storage with a database

---

## Author

**Amir Lorvand**

