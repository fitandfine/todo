

# 📝 To-Do List Manager (C Language)

A **command-line To-Do List Manager** written in C.  
This project demonstrates **file handling, command-line argument parsing, and modular programming** — while being actually useful for daily task tracking.

---

## ✨ Features
- ✅ Add tasks
- 📋 List tasks
- ❌ Delete tasks
- ☑️ Mark tasks as **done**
- 🔄 Mark tasks as **undone**

Tasks are saved in `tasks.txt` so they persist between runs.

---

## ⚙️ Installation & Compilation (Ubuntu/Linux)
gcc todo.c -o todo

## Usage
```
**./todo add "Buy groceries"     # Add a task**

**./todo list                    # Show all tasks**

**./todo done 1                  # Mark task 1 as done**

**./todo undone 1                # Revert task 1 back to not done**

**./todo del 2                   # Delete task number 2**
```
---
## 🛠️ Function Documentation
### main(int argc, char *argv[])

Parses user commands (add, list, del, done, undone).

Dispatches to appropriate function.

### addTask(const char *task)

Appends a new task to tasks.txt.

Format: [ ] Task description.

### listTasks()

Reads all tasks and prints them with numbering.

### deleteTask(int taskNumber)

Deletes a task by rewriting all others into a new file.

### markDone(int taskNumber)

Changes [ ] to [x] for given task.

### markUndone(int taskNumber)

Changes [x] back to [ ] for given task.

### trimNewline(char *str)

Removes trailing newline from strings read with fgets.
---
##Example Session:
---
$ ./todo add "Finish Linux practice"
Task added: Finish Linux practice
---
$ ./todo add "Learn C file handling"
Task added: Learn C file handling
---
$ ./todo list
1. [ ] Finish Linux practice
2. [ ] Learn C file handling
---
$ ./todo done 1
Task 1 marked as done.
---
$ ./todo list
1. [x] Finish Linux practice
2. [ ] Learn C file handling
---
$ ./todo undone 1
Task 1 marked as not done.
---
$ ./todo list
1. [ ] Finish Linux practice
2. [ ] Learn C file handling
---
