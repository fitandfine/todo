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




// --- Main entry point ---
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  %s add \"Task description\"   -> Add a task\n", argv[0]);
        printf("  %s list                      -> List tasks\n", argv[0]);
        printf("  %s del <task_number>         -> Delete a task\n", argv[0]);
        printf("  %s done <task_number>        -> Mark task as done\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            printf("Error: No task provided.\n");
            return 1;
        }
        addTask(argv[2]);
    } else if (strcmp(argv[1], "list") == 0) {
        listTasks();
    } else if (strcmp(argv[1], "del") == 0) {
        if (argc < 3) {
            printf("Error: No task number provided.\n");
            return 1;
        }
        deleteTask(atoi(argv[2]));
    } else if (strcmp(argv[1], "done") == 0) {
        if (argc < 3) {
            printf("Error: No task number provided.\n");
            return 1;
        }
        markDone(atoi(argv[2]));
    } else {
        printf("Unknown command: %s\n", argv[1]);
    }

    return 0;
}

// --- Helper to remove newline characters from fgets input ---
void trimNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// --- Append a new task to the file ---
void addTask(const char *task) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "[ ] %s\n", task); // "[ ]" means not done
    fclose(file);
    printf("Task added: %s\n", task);
}

// --- Display all tasks from the file ---
void listTasks() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No tasks found.\n");
        return;
    }

    char task[MAX_TASK_LEN];
    int count = 1;
    while (fgets(task, sizeof(task), file)) {
        trimNewline(task);
        printf("%d. %s\n", count++, task);
    }
    fclose(file);
}

// --- Delete a task by number (rewrite file without it) ---
void deleteTask(int taskNumber) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No tasks to delete.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Error creating temp file");
        fclose(file);
        return;
    }

    char task[MAX_TASK_LEN];
    int count = 1;
    int deleted = 0;

    while (fgets(task, sizeof(task), file)) {
        if (count != taskNumber) {
            fputs(task, temp);
        } else {
            deleted = 1;
        }
        count++;
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (deleted) {
        printf("Task %d deleted.\n", taskNumber);
    } else {
        printf("Task number %d not found.\n", taskNumber);
    }
}

// --- Mark a task as done ---
void markDone(int taskNumber) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No tasks found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Error creating temp file");
        fclose(file);
        return;
    }

    char task[MAX_TASK_LEN];
    int count = 1;
    int marked = 0;

    while (fgets(task, sizeof(task), file)) {
        if (count == taskNumber) {
            // Replace "[ ]" with "[x]" to indicate completion
            if (strncmp(task, "[ ]", 3) == 0) {
                fprintf(temp, "[x]%s", task + 3);
                marked = 1;
            } else {
                fputs(task, temp); // already marked done
            }
        } else {
            fputs(task, temp);
        }
        count++;
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (marked) {
        printf("Task %d marked as done.\n", taskNumber);
    } else {
        printf("Task number %d not found or already done.\n", taskNumber);
    }
}