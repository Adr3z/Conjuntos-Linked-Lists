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

    char *name_copy = (char *)malloc(strlen(name) + 1);
    assert(name_copy != NULL);
    strcpy(name_copy, name);

    node_t *new_student = (node_t *)malloc(sizeof(node_t));
    assert( new_student != NULL);
    new_student->data.grade = grade;
    new_student->data.name = name_copy;
    new_student->next = roster->students;
    roster->students = new_student;
    roster->size++;
    return true;
}
