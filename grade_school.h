#ifndef GRADE_SCHOOL_H
#define GRADE_SCHOOL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


typedef struct {
   uint8_t grade;
   char *name;
} student_t;

typedef struct node {
   student_t data;
   struct node *next;
} node_t;

typedef struct {
   node_t *students;
   size_t size;
} roster_t;

void init_roster(roster_t *roster);
void free_roster(roster_t *roster);
bool add_student(roster_t *roster, const char *name, uint8_t grade);
bool remove_student(roster_t *roster, const char *name);
roster_t get_grade(const roster_t *roster, uint8_t desired_grade);

#endif
