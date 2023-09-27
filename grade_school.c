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
