#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Task {
    int id;
    char name[100];
    char date[20];
    float duration;
    struct Task* next;
};

struct Task* unperformed = NULL;  // linked list
struct Task* performed = NULL;  //  stack
struct Task* undone = NULL;       // linked list

void insertTask(int id, char* name1, char* date1, float duration) {

    struct Task* newNode = (struct Task*)malloc(sizeof(struct Task));
    if (newNode == NULL) {
        printf(" allocation failed\n");
        return;
    }

    newNode->id = id;
    strcpy(newNode->name, name1);
    strcpy(newNode->date, date1);
    newNode->duration = duration;
    newNode->next = NULL;

    if (unperformed == NULL) {
        unperformed = newNode;
    } else {
        struct Task* current = unperformed;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
void loadTasks(char* tasks) {
    FILE* file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("file couldnt be created\n");

        return;
    }

    int n;

    printf("Enter the number of tasks you want to add: ");
    scanf("%d", &n);


    for (int i = 0; i < n; i++) {

        int id;
        char name[100], date[20];
        float duration;

        printf("\nTask %d:\n", i + 1);
        printf("Enter ID: ");
        scanf("%d", &id);
        getchar();

        printf("Enter Name: ");
        fgets(name, sizeof(name), stdin); //read full line without spaces
        name[strcspn(name,"\n")]='\0';



        printf("Enter Date (dd/mm/yyyy): ");
        scanf("%s",  date);
        getchar();

        printf("Enter Duration (in hours): ");
        scanf("%f", &duration);
        getchar();


        fprintf(file,"%d#%s#%s#%.2f\n\n", id, name,date,duration);
    }

    fclose(file);

    file = fopen("tasks.txt","r");
    if (file== NULL) {
        printf("Could not open the file.\n");
        return;
    }

    char line[222];

    while (fgets(line, sizeof(line), file)) {
        char* token;
        int id = 0;
        char name[100] = "", date[20] = "";
        float duration = 0;

        token = strtok(line, "#");
        if (token) id = atoi(token);

        token = strtok(NULL, "#");
        if (token) strcpy(name, token);

        token = strtok(NULL, "#");
        if (token) strcpy(date, token);

        token = strtok(NULL, "#\n");
        if (token) duration=atof(token);

 insertTask(id, name, date, duration);
    }

    fclose(file);
    printf("---The Tasks have been loaded successfully---\n");
}


void addTask() {
    int id;
    char name[100];
    char date[20];
    float duration;

    printf("Task ID: ");
    scanf("%d", &id);
    getchar();

    printf("Task Name ): ");
    fgets(name, sizeof(name), stdin);

    printf("Date (dd/mm/yyyy): ");
    scanf("%s", date);
    getchar();

    printf("Duration (in hours): \n");
    scanf("%f", &duration);
    getchar();

    insertTask(id, name, date, duration);
    printf("---Task has been added successfully---\n");
}

struct Task* deleteTask(int id) {

    struct Task* current = unperformed;
    struct Task* previous=NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                unperformed = current->next;
            } else {
                previous->next = current->next;
            }
            current->next = NULL;
            return current;
        }
        previous = current;
        current = current->next;
    }

    return NULL;
}

void searchById(int id) {

    struct Task* current = unperformed;
    while (current != NULL) {
        if (current->id == id) {
            printf("Task Found:\n");
            printf("ID:%d\nName: %s\nDate: %s\nDuration: %.2f\n\n",
                   current->id, current->name, current->date, current->duration);
            return;
        }
        current = current->next;
    }
    printf("---Task with ID %d not found---\n", id);
}

void searchByName(char* name) {

    struct Task* current = unperformed;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Task Found:\n");
            printf("ID: %d\nName: %s\nDate: %s\nDuration: %.2f\n\n",
                   current->id, current->name, current->date, current->duration);
            return;
        }
        current = current->next;
    }
    printf("---Task with name \"%s\" is not found---\n", name);
}

void searchTask() {
    int choice;
    printf("Choose your search type:\n");
    printf("1.Task ID\n");
    printf("2.Task Name\n");
    printf("Enter choice: ");

    scanf("%d",&choice);
    getchar();

    if (choice == 1) {
        int id;
        printf("Enter the Task ID: ");
        scanf("%d", &id);
        getchar();
        searchById(id);

    } else if (choice == 2) {
        char name[100];

        printf("Enter Task Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        searchByName(name);

    } else {
        printf("---Invalid choice---\n");
    }
}


void viewUnperformedTasks() {

    if (unperformed == NULL) {
        printf("No unperformed tasks found.\n");
        return;
    }

    struct Task* current = unperformed;
    printf("\n--- Unperformed Tasks ---\n");

    while (current != NULL) {

        printf("ID:%d\n", current->id);
        printf("Name: %s\n", current->name);
    printf("Date: %s\n", current->date);
        printf("Duration:%.3f\n", current->duration);
        printf(">>>----------------------<<<\n");
        current = current->next;
    }
}

void performTask() {

    if (unperformed == NULL) {
        printf("No unperformed tasks available.\n");
        return;
    }

    int id;
    printf("Enter the ID of the task to perform: ");
    scanf("%d", &id);
    getchar();

    struct Task* current = unperformed;
    struct Task* previous = NULL;

    while (current != NULL) {
        if (current->id ==id) {
            if (previous == NULL) {
                unperformed = current->next;
            } else {
                previous->next = current->next;
            }
            current->next = performed;
            performed = current;
            printf("Task -%s- with ID -%d- has been performed.\n", current->name, current->id);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("---Task with ID %d was not found in the unperformed tasks---\n", id);
}

void undoLastPerformedTask() {
    if (performed == NULL) {
        printf("There are no performed tasks to undo.\n");
        return;
    }

    struct Task* undone = performed;
    performed = performed->next;
    undone->next = NULL;

    insertTask(undone->id, undone->name, undone->date, undone->duration);
    free(undone);
    printf("---Task -%s- with ID -%d- has been undone---\n",
           undone->name, undone->id);
}

void viewPerformedTasks() {
    if (performed == NULL) {
        printf("No tasks found that have been performed.\n");
        return;
    }

    struct Task* current = performed;
    printf("\n--- Performed Tasks ---\n");
    while (current != NULL) {
        printf("ID: %d\n", current->id);
        printf("Name: %s\n", current->name);
        printf("Date: %s\n" , current->date);
        printf("Duration: %.2f\n\n", current->duration);

        current = current ->next;
    }
}
void generateSummaryReport() {

    FILE* report = fopen("Report.txt", "w");

    if (report == NULL) {
        return;
    }

    fprintf(report, "\n------- Task Summary Report -------\n\n");

    fprintf(report, "\n|| Unperformed Tasks ||\n");

    struct Task* current = unperformed;
    if (current == NULL) fprintf(report, "None\n");
    while (current != NULL) {
        fprintf(report, "ID: %d | name: %s | Date: %s | Duration: %.2f hours\n",
                current->id, current->name, current->date, current->duration);
        current = current->next;
    }
    fprintf(report, "\n");

    // Undone
    fprintf(report, "||Undone Tasks ||\n");
    current = undone;
    if (current == NULL) fprintf(report, "None\n");
    while (current != NULL) {
        fprintf(report, "ID: %d | Name: %s | Date: %s | Duration: %.2f hours\n",
                current->id, current->name, current->date, current->duration);
        current = current->next;
    }
    fprintf(report, "\n");

    // Performed
    fprintf(report, "|| Performed Tasks ||\n");
    current = performed;

    if (current == NULL) fprintf(report, "None\n");

    while (current != NULL) {
        fprintf(report, "ID: %d | Name: %s | Date: %s | Duration: %.2f hrs\n",
                current->id, current->name, current->date, current->duration);
        current = current->next;
    }

    fclose(report);

printf("Summary report generated successfully in Report.txt\n");
}

void end(struct Task* head) {
    struct Task* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


 int main() {

    int choice=0;

        while (choice != 10) {

        printf("\n--------------- Task Management Menu -----------------\n\n");
        printf("1. Load Tasks File\n");
        printf("2. Add a New Task\n");
        printf("3. Delete a Task\n");
        printf("4. Search for a Task\n");
        printf("5. View Unperformed Tasks\n");
        printf("6. Perform a Task\n");
        printf("7. Undo Last Performed Task\n");
        printf("8. View Performed Tasks\n");
        printf("9. Generate Summary Report\n");
        printf("10. Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                loadTasks("tasks.txt");
                break;
            case 2:
                addTask();
                break;
            case 3: {
    int id;
    printf("Enter the ID of the task to delete: ");
    scanf("%d", &id);
    struct Task* deleted = deleteTask(id);

    if (deleted != NULL) {
        printf("Task with ID %d deleted: %s\n", deleted->id, deleted->name);
        free(deleted);

    } else {
        printf("Task with ID %d not found.\n", id);
    }

    break;
}

            case 4:
                searchTask();
                break;

            case 5:
                viewUnperformedTasks();
                break;

            case 6:
                performTask();
                break;

            case 7:
                undoLastPerformedTask();
                break;

            case 8:
                viewPerformedTasks();
                break;

            case 9:
                generateSummaryReport();
                break;

            case 10:
                printf("Exiting the program...\n");
                end(unperformed);
                end(performed);
                end(undone);
                return 0;

            default:
                printf("Invalid choice, try again...\n");
        }
    }
}

