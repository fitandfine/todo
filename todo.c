#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "tasks.txt"
#define MAX_TASK_LEN 256

// --- Function prototypes ---
void addTask(const char *task);
void listTasks();
void deleteTask(int taskNumber);
void markDone(int taskNumber);
void trimNewline(char *str);