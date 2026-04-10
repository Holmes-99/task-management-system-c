# Task Management System

A console-based Task Management System written in C, built as part of
the COMP2421 Data Structures course at Birzeit University.

## What it does
- Load tasks from a file (`tasks.txt`)
- Add, delete, and search for tasks
- Mark tasks as performed (removes from main list)
- Undo the last performed task (restores it to the list)
- View unperformed and performed tasks
- Generate a summary report saved to `Report.txt`

## Data Structures Used
- **Linked List** — stores all unperformed tasks
- **Stack** — tracks performed tasks for undo functionality
- **Queue** — manages undone tasks placed back at end of list

## How to Run

### Compile
gcc task_manager.c -o task_manager

### Run
./task_manager

Make sure `tasks.txt` is in the same folder before running.

## Input Format
Each line in `tasks.txt` follows this format:
ID#TaskName#Date#Duration(hours)

Example:
10#meeting#22/3/2025#1.5
11#attend lecture#25/3/2025#3

## Menu Options
1. Load Tasks File
2. Add a New Task
3. Delete a Task
4. Search for a Task
5. View Unperformed Tasks
6. Perform a Task
7. Undo Last Performed Task
8. View Performed Tasks
9. Generate Summary Report
10. Exit

## Course Info
- Course: COMP2421 — Data Structures
- University: Birzeit University
- Semester: Spring 2024/2025
