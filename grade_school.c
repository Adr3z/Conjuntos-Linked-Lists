#include "grade_school.h"

void init_roster(roster_t *roster)
{
    roster->students = NULL;
    roster->size = 0;
}

void free_roster(roster_t *roster)
{
    while (roster->students != NULL) {
        node_t *tmp = roster->students;
        roster->students = roster->students->next;
        free(tmp->data.name);
        free(tmp);
    }
    roster->size = 0;
}

bool add_student(roster_t *roster, const char *name, uint8_t grade) 
{
    node_t *current = roster->students;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            return false; 
        }
        current = current->next;
    }

    node_t *new_student = (node_t *)malloc(sizeof(node_t));
    if (new_student == NULL) {
        exit(1); 
    }

    new_student->data.name = (char *)malloc(strlen(name) + 1);
    if (new_student->data.name == NULL) {
        free(new_student); 
        exit(1); 
    }
    strcpy(new_student->data.name, name);

    new_student->data.grade = grade;
    new_student->next = roster->students; 
    roster->students = new_student;

    roster->size++;
    return true;
}

bool remove_student(roster_t *roster, const char *name) 
{
    node_t *current = roster->students;
    node_t *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            if (prev == NULL) {
                // Si el estudiante a eliminar es el primero, actualiza el inicio del roster
                roster->students = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->data.name);
            free(current);
            roster->size--;
            return true;
        }
        prev = current;
        current = current->next;
    }

    return false; 
}
