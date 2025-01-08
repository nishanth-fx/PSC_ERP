#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char username[50];
    char password[50];
    char name[50];
    float attendance;
    float cgpa;
    char department[50];
    int semester;
    char email[50];
};

void saveToFile(const struct Student *s) {
    FILE *fp = fopen("students.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "USERNAME=%s\n", s->username);
    fprintf(fp, "PASSWORD=%s\n", s->password);
    fprintf(fp, "NAME=%s\n", s->name);
    fprintf(fp, "DEPARTMENT=%s\n", s->department);
    fprintf(fp, "SEMESTER=%d\n", s->semester);
    fprintf(fp, "CGPA=%.2f\n", s->cgpa);
    fprintf(fp, "ATTENDANCE=%.2f\n", s->attendance);
    fprintf(fp, "EMAIL=%s\n", s->email);
    fprintf(fp, "==========\n");
    fclose(fp);
}

void readLine(char *buffer, int maxLen) {
    if (fgets(buffer, maxLen, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

struct Student* readStudentFromFile(FILE *fp) {
    char line[256];
    struct Student *s = malloc(sizeof(struct Student));
    if (s == NULL) return NULL;

    // Initialize the struct to prevent undefined behavior
    memset(s, 0, sizeof(struct Student));

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        
        if (strcmp(line, "==========") == 0) {
            return s;
        }
        
        char *value = strchr(line, '=');
        if (value == NULL) continue;
        value++; // Skip the '=' character
        
        if (strncmp(line, "USERNAME=", 9) == 0) {
            strncpy(s->username, value, sizeof(s->username) - 1);
            s->username[sizeof(s->username) - 1] = '\0';
        } else if (strncmp(line, "PASSWORD=", 9) == 0) {
            strncpy(s->password, value, sizeof(s->password) - 1);
            s->password[sizeof(s->password) - 1] = '\0';
        } else if (strncmp(line, "NAME=", 5) == 0) {
            strncpy(s->name, value, sizeof(s->name) - 1);
            s->name[sizeof(s->name) - 1] = '\0';
        } else if (strncmp(line, "DEPARTMENT=", 11) == 0) {
            strncpy(s->department, value, sizeof(s->department) - 1);
            s->department[sizeof(s->department) - 1] = '\0';
        } else if (strncmp(line, "SEMESTER=", 9) == 0) {
            s->semester = atoi(value);
        } else if (strncmp(line, "CGPA=", 5) == 0) {
            s->cgpa = atof(value);
        } else if (strncmp(line, "ATTENDANCE=", 11) == 0) {
            s->attendance = atof(value);
        } else if (strncmp(line, "EMAIL=", 6) == 0) {
            strncpy(s->email, value, sizeof(s->email) - 1);
            s->email[sizeof(s->email) - 1] = '\0';
        }
    }
    
    free(s);
    return NULL;
}

int checkLogin(const char *username, const char *password) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) return 0;
    
    struct Student *s;
    int found = 0;
    
    while ((s = readStudentFromFile(fp)) != NULL) {
        if (strcmp(s->username, username) == 0 && strcmp(s->password, password) == 0) {
            found = 1;
            free(s);
            break;
        }
        free(s);
    }
    
    fclose(fp);
    return found;
}

void displayStudent(const struct Student *s) {
    if (s == NULL) return;
    
    printf("\n--- Student Details ---\n");
    printf("Name: %s\n", s->name);
    printf("Department: %s\n", s->department);
    printf("Semester: %d\n", s->semester);
    printf("CGPA: %.2f\n", s->cgpa);
    printf("Attendance: %.2f%%\n", s->attendance);
    printf("Email: %s\n", s->email);
}

void searchStudent() {
    char searchName[50];
    int found = 0;
    
    printf("Enter student name to search: ");
    readLine(searchName, sizeof(searchName));
    
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("No student records found!\n");
        return;
    }
    
    struct Student *s;
    while ((s = readStudentFromFile(fp)) != NULL) {
        if (strstr(s->name, searchName) != NULL) {
            displayStudent(s);
            found = 1;
        }
        free(s);
    }
    
    if (!found) {
        printf("No student found with name containing '%s'\n", searchName);
    }
    fclose(fp);
}

void updateStudent(const char *username) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Create a temporary file
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    int found = 0;
    struct Student *s;
    struct Student updated;
    memset(&updated, 0, sizeof(struct Student));  // Initialize the struct
    
    while ((s = readStudentFromFile(fp)) != NULL) {
        if (strcmp(s->username, username) == 0) {
            found = 1;
            printf("Current details:\n");
            displayStudent(s);
            
            // Copy username and password
            strncpy(updated.username, s->username, sizeof(updated.username) - 1);
            strncpy(updated.password, s->password, sizeof(updated.password) - 1);
            
            printf("\nEnter new details:\n");
            printf("Name: ");
            readLine(updated.name, sizeof(updated.name));
            
            printf("Department: ");
            readLine(updated.department, sizeof(updated.department));
            
            printf("Semester: ");
            if (scanf("%d", &updated.semester) != 1) {
                printf("Invalid semester input!\n");
                free(s);
                fclose(fp);
                fclose(temp);
                remove("temp.txt");
                return;
            }
            getchar();  // Consume newline
            
            printf("CGPA: ");
            if (scanf("%f", &updated.cgpa) != 1) {
                printf("Invalid CGPA input!\n");
                free(s);
                fclose(fp);
                fclose(temp);
                remove("temp.txt");
                return;
            }
            getchar();  // Consume newline
            
            printf("Attendance: ");
            if (scanf("%f", &updated.attendance) != 1) {
                printf("Invalid attendance input!\n");
                free(s);
                fclose(fp);
                fclose(temp);
                remove("temp.txt");
                return;
            }
            getchar();  // Consume newline
            
            printf("Email: ");
            readLine(updated.email, sizeof(updated.email));
            
            fprintf(temp, "USERNAME=%s\n", updated.username);
            fprintf(temp, "PASSWORD=%s\n", updated.password);
            fprintf(temp, "NAME=%s\n", updated.name);
            fprintf(temp, "DEPARTMENT=%s\n", updated.department);
            fprintf(temp, "SEMESTER=%d\n", updated.semester);
            fprintf(temp, "CGPA=%.2f\n", updated.cgpa);
            fprintf(temp, "ATTENDANCE=%.2f\n", updated.attendance);
            fprintf(temp, "EMAIL=%s\n", updated.email);
            fprintf(temp, "==========\n");
        } else {
            fprintf(temp, "USERNAME=%s\n", s->username);
            fprintf(temp, "PASSWORD=%s\n", s->password);
            fprintf(temp, "NAME=%s\n", s->name);
            fprintf(temp, "DEPARTMENT=%s\n", s->department);
            fprintf(temp, "SEMESTER=%d\n", s->semester);
            fprintf(temp, "CGPA=%.2f\n", s->cgpa);
            fprintf(temp, "ATTENDANCE=%.2f\n", s->attendance);
            fprintf(temp, "EMAIL=%s\n", s->email);
            fprintf(temp, "==========\n");
        }
        free(s);
    }

    fclose(fp);
    fclose(temp);
    
    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        printf("Student details updated successfully!\n");
    } else {
        remove("temp.txt");
        printf("Student not found!\n");
    }
}

void sortByCGPA() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("No student records found!\n");
        return;
    }
    
    // Count number of students
    int count = 0;
    struct Student *s;
    while ((s = readStudentFromFile(fp)) != NULL) {
        count++;
        free(s);
    }
    rewind(fp);
    
    // Allocate array of pointers
    struct Student **students = malloc(count * sizeof(struct Student*));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return;
    }
    
    // Read all students
    int i = 0;
    while ((s = readStudentFromFile(fp)) != NULL && i < count) {
        students[i++] = s;
    }
    fclose(fp);
    
    // Sort by CGPA
    for (i = 0; i < count-1; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (students[j]->cgpa < students[j+1]->cgpa) {
                struct Student *temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
    
    // Display sorted students
    printf("\n--- Students Sorted by CGPA (Highest to Lowest) ---\n");
    for (i = 0; i < count; i++) {
        printf("\nRank %d:\n", i+1);
        displayStudent(students[i]);
    }
    
    // Clean up
    for (i = 0; i < count; i++) {
        free(students[i]);
    }
    free(students);
}

int main() {
    int choice;
    char username[50], password[50];

    while(1) {
        printf("\n1. Register New Student\n");
        printf("2. Login\n");
        printf("3. Search Student\n");
        printf("4. Display Students by CGPA\n");
        printf("5. Update Student Details\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();  // Consume newline

        switch(choice) {
            case 1: {
                struct Student s;
                memset(&s, 0, sizeof(struct Student));  // Initialize the struct
                
                printf("Enter username: ");
                readLine(s.username, sizeof(s.username));
                
                printf("Enter password: ");
                readLine(s.password, sizeof(s.password));
                
                printf("Enter name: ");
                readLine(s.name, sizeof(s.name));
                
                printf("Enter department: ");
                readLine(s.department, sizeof(s.department));
                
                printf("Enter semester: ");
                if (scanf("%d", &s.semester) != 1 || s.semester < 1) {
                    printf("Invalid semester input!\n");
                    while (getchar() != '\n');
                    continue;
                }
                getchar();  // Consume newline
                
                printf("Enter CGPA: ");
                if (scanf("%f", &s.cgpa) != 1 || s.cgpa < 0.0 || s.cgpa > 10.0) {
                    printf("Invalid CGPA input!\n");
                    while (getchar() != '\n');
                    continue;
                }
                getchar();  // Consume newline
                
                printf("Enter attendance percentage: ");
                if (scanf("%f", &s.attendance) != 1 || s.attendance < 0.0 || s.attendance > 100.0) {
                    printf("Invalid attendance input!\n");
                    while (getchar() != '\n');
                    continue;
                }
                getchar();  // Consume newline
                
                printf("Enter email: ");
                readLine(s.email, sizeof(s.email));
                
                saveToFile(&s);
                printf("Registration successful!\n");
                break;
            }
                
            case 2:
                printf("Enter username: ");
                readLine(username, sizeof(username));
                
                printf("Enter password: ");
                readLine(password, sizeof(password));
                
                if (checkLogin(username, password)) {
                    printf("Login successful!\n");
                    FILE *fp = fopen("students.txt", "r");
                    if (fp != NULL) {
                        struct Student *s;
                        while ((s = readStudentFromFile(fp)) != NULL) {
                            if (strcmp(s->username, username) == 0) {
                                displayStudent(s);
                                free(s);
                                break;
                            }
                            free(s);
                        }
                        fclose(fp);
                    }
                } else {
                    printf("Invalid credentials!\n");
                }
                break;
                
            case 3:
                searchStudent();
                break;
                
            case 4:
                sortByCGPA();
                break;
                
            case 5:
                printf("Enter username to update: ");
                readLine(username, sizeof(username));
                updateStudent(username);
                break;
                
            case 6:
                printf("Goodbye!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    }
    return 0;
}
