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

node_t *create_student_node(const char *name, uint8_t grade) 
{
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
    new_student->next = NULL;

    return new_student;
}

void add_student_sorted(roster_t *roster, node_t *new_student)
{
    node_t *current = roster->students;
    node_t *prev = NULL;

    while (current != NULL) {
        if (new_student->data.grade < current->data.grade ||
            (new_student->data.grade == current->data.grade && strcmp(new_student->data.name, current->data.name) < 0)) {
            if (prev == NULL) {
                new_student->next = roster->students;
                roster->students = new_student;
            } else {
                prev->next = new_student;
                new_student->next = current;
            }
            roster->size++;
            return;
        }
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        roster->students = new_student;
    } else {
        prev->next = new_student;
    }
    roster->size++;
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

    node_t *new_student = create_student_node(name, grade);
    add_student_sorted(roster, new_student);
    return true;
}

bool remove_student(roster_t *roster, const char *name) 
{
    node_t *current = roster->students;
    node_t *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            if (prev == NULL) {
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
