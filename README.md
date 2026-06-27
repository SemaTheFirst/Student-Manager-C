# Student-Manager-C

A robust, Command Line Interface (CLI) based Student Information System written in C. This project demonstrates system-level programming concepts, specifically focusing on **dynamic memory allocation**, pointer manipulation, and data structure management.

## 🚀 Features

- **Dynamic Memory Management:** Automatically resizes course arrays using `realloc` as new courses are added, ensuring efficient memory usage.
- **Memory Safety:** Implements proper garbage collection strategies using `free()` to prevent memory leaks upon exiting the system or deleting courses.
- **Comprehensive Grade Tracking:** Calculate overall GPA dynamically based on course credits and weighted midterm (40%) / final (60%) averages.
- **Deep Copy Functionality:** Allows cloning an entire student profile, including independent dynamic allocations for their course list.
- **Data Querying & Sorting:**
  - Search for specific courses via course codes.
  - Sort the course list alphabetically using a Bubble Sort algorithm.
  - Identify the highest graded course and list failed courses (< 50 average).

## 🛠️ Technical Stack
- **Language:** C
- **Core Concepts:** Structs, Pointers, Dynamic Memory Allocation (`malloc`, `calloc`, `realloc`, `free`), String Manipulation.

## 💻 How to Compile and Run

You will need a C compiler (like GCC) installed on your system.

1. Clone the repository:
   ```bash
   git clone https://github.com/SemaTheFirst/Student-Manager-C.git

2. Compile the code:
   ```bash
   gcc main.c -o student_system

3. Run the executable:
   ```bash
   ./student_system

## 📋 Menu Options

Upon running the program, you will be prompted to enter a student name and ID. Afterward, you can navigate the system using the following menu:

**Add course** - Dynamically allocates space and adds a new course.

**Enter grades** - Inputs midterm and final grades to calculate the average.

**Print report card** - Displays all courses, grades, and the overall average.

**List failed courses** - Filters courses with an average below 50.

**Find the highest graded course** - Displays the course with the top average.

**Total credit** - Sums up the current credit load.

**List courses alphabetically** - Sorts and displays courses by name.

**Update course information** - Modifies existing course details.

**Delete course** - Removes a course and dynamically shrinks the allocated memory.

**Update student information** - Modifies student name and ID.

**Copy the courses to another student** - Deep copies data to a new struct.

**Calculate the overall average** - Manually triggers GPA calculation.

**Search course** - Finds a course by its unique code.

**Exit** - Safely frees all allocated memory and terminates the program.

