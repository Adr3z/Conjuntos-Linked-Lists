#include "test-framework/unity.h"
#include "grade_school.h"

static roster_t roster;

void setUp(void)
{
   init_roster(&roster);
}

void tearDown(void)
{
   free_roster(&roster);
}

static void check_rosters(const student_t *expected_students, size_t expected_size, 
                           const roster_t *expected_roster)
{
   TEST_ASSERT_EQUAL_size_t_MESSAGE(expected_size, expected_roster->size,
                                    "Incorrect number of students");
   const node_t *roster_student_ptr = expected_roster->students;
   const student_t *student_ptr = expected_students; 
   while (roster_student_ptr != NULL 
            && student_ptr < expected_students + expected_size)   
   {
      TEST_ASSERT_EQUAL_STRING(roster_student_ptr->data.name, student_ptr->name);
      roster_student_ptr = roster_student_ptr->next;
      student_ptr++;
   }
}

static void test_roster_is_empty_when_no_student_added(void)
{
   TEST_IGNORE();   // delete this line to run test
   TEST_ASSERT_EQUAL(0, roster.size);
   TEST_ASSERT_NULL(roster.students);
}

static void test_cannot_remove_on_empty_list(void)
{
   TEST_IGNORE();   // delete this line to run test
   remove_student(&roster, "Aimee");
   TEST_ASSERT_EQUAL(0, roster.size);
   TEST_ASSERT_NULL(roster.students);
}

static void test_add_student(void)
{
   //TEST_IGNORE();   // delete this line to run test
   TEST_ASSERT_TRUE(add_student(&roster, "Aimee", 2));
}

static void test_student_added_to_roster(void)
{
   TEST_IGNORE();
   student_t expected[] = { { 2, "Aimee" } }; 
   
   add_student(&roster, "Aimee", 2);
   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_remove_student(void)
{
   TEST_IGNORE();   // delete this line to run test
   
   TEST_ASSERT_TRUE(add_student(&roster, "Aimee", 2));
   TEST_ASSERT_TRUE(remove_student(&roster, "Aimee"));
   TEST_ASSERT_EQUAL(0, roster.size);
   TEST_ASSERT_NULL(roster.students);
}

static void test_cannot_remove_student_with_misspeled_name(void)
{
   TEST_IGNORE();   // delete this line to run test
   
   TEST_ASSERT_TRUE(add_student(&roster, "Aimee", 2));
   TEST_ASSERT_FALSE(remove_student(&roster, "aimee"));
   TEST_ASSERT_EQUAL(1, roster.size);
   TEST_ASSERT_NOT_NULL(roster.students);
}

static void test_adding_multiple_students_in_same_grade_in_roster(void)
{
   TEST_IGNORE();
   
   TEST_ASSERT_TRUE(add_student(&roster, "Blair", 2));
   TEST_ASSERT_TRUE(add_student(&roster, "James", 2));
   TEST_ASSERT_TRUE(add_student(&roster, "Paul", 2));
}

static void test_multiple_students_in_same_grade_are_added_to_roster(void)
{
   TEST_IGNORE();
   student_t expected[] = {
         { 2, "Blair" }, 
         { 2, "James" },
         { 2, "Paul" } 
   }; 
   
   add_student(&roster, "Blair", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "Paul", 2);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_remove_first_student(void)
{
   TEST_IGNORE();
   student_t expected[] = {
         { 2, "James" },
         { 2, "Paul" }, 
   }; 
   
   add_student(&roster, "Blair", 2);
   add_student(&roster, "Paul", 2);
   add_student(&roster, "James", 2);
   remove_student(&roster, "Blair");

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_remove_middle_student(void)
{
   TEST_IGNORE();
   student_t expected[] = {
         { 2, "Blair" }, 
         { 2, "Paul" },
   }; 
   
   add_student(&roster, "James", 2);
   add_student(&roster, "Blair", 2);
   add_student(&roster, "Paul", 2);
   remove_student(&roster, "James");

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_remove_last_student(void)
{
   TEST_IGNORE();
   student_t expected[] = {
         { 2, "Blair" }, 
         { 2, "James" },
   }; 
   
   add_student(&roster, "Blair", 2);
   add_student(&roster, "Paul", 2);
   add_student(&roster, "James", 2);
   remove_student(&roster, "Paul");

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}


static void test_cannot_add_student_to_same_grade_more_than_once(void)
{
   TEST_IGNORE();
   TEST_ASSERT_TRUE(add_student(&roster, "Blair", 2));
   TEST_ASSERT_TRUE(add_student(&roster, "James", 2));
   TEST_ASSERT_FALSE(add_student(&roster, "James", 2));
   TEST_ASSERT_TRUE(add_student(&roster, "Paul", 2));
}

static void test_cannot_remove_student_more_than_once(void)
{
   TEST_IGNORE();
   TEST_ASSERT_TRUE(add_student(&roster, "James", 2));
   TEST_ASSERT_TRUE(add_student(&roster, "Blair", 2));
   TEST_ASSERT_TRUE(remove_student(&roster, "James"));
   TEST_ASSERT_TRUE(add_student(&roster, "Paul", 2));
   TEST_ASSERT_FALSE(remove_student(&roster, "James"));
   TEST_ASSERT_EQUAL(2, roster.size);
   TEST_ASSERT_NOT_NULL(roster.students);
}

static void test_student_not_added_to_same_grade_in_roster_more_than_once(void)
{
   TEST_IGNORE();
   student_t expected[] = {
      { 2, "Blair" }, 
      { 2, "James" },
      { 2, "Paul" } 
   };
   
   add_student(&roster, "Blair", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "Paul", 2);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_student_not_removed_more_than_once(void)
{
   TEST_IGNORE();
   student_t expected[] = {
      { 2, "Blair" }, 
      { 2, "Paul" } 
   };
   
   add_student(&roster, "James", 2);
   add_student(&roster, "Blair", 2);
   remove_student(&roster, "James");
   add_student(&roster, "Paul", 2);
   remove_student(&roster, "James");

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}


static void test_can_add_removed_student(void)
{
   TEST_IGNORE();
   TEST_ASSERT_TRUE(add_student(&roster, "James", 2));
   TEST_ASSERT_TRUE(add_student(&roster, "Blair", 2));
   TEST_ASSERT_TRUE(remove_student(&roster, "James"));
   TEST_ASSERT_TRUE(add_student(&roster, "Paul", 2));
   TEST_ASSERT_TRUE(add_student(&roster, "James", 2));
   TEST_ASSERT_EQUAL(3, roster.size);
   TEST_ASSERT_NOT_NULL(roster.students);
}

static void test_adding_students_in_multiple_grades(void)
{
   TEST_IGNORE();
   TEST_ASSERT_TRUE(add_student(&roster, "Chelsea", 3));
   TEST_ASSERT_TRUE(add_student(&roster, "Logan", 7));
}

static void test_students_in_multiple_grades_are_added_to_roster(void)
{
   TEST_IGNORE();
   student_t expected[] = {
      { 3, "Chelsea" }, 
      { 7, "Logan" } 
   };
   
   add_student(&roster, "Chelsea", 3);
   add_student(&roster, "Logan", 7);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_cannot_add_same_student_to_multiple_grades_in_roster(void)
{
   TEST_IGNORE();
   TEST_ASSERT_TRUE(add_student(&roster, "Blair", 2));
   TEST_ASSERT_TRUE(add_student(&roster, "James", 2));
   TEST_ASSERT_FALSE(add_student(&roster, "James", 3));
   TEST_ASSERT_TRUE(add_student(&roster, "Paul", 3));
}

static void test_student_not_added_to_multiple_grades_in_roster(void)
{
   TEST_IGNORE();
   student_t expected[] = {
      { 2, "Blair" }, 
      { 2, "James" },
      { 3, "Paul" } 
   };
   
   add_student(&roster, "Blair", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "James", 3);
   add_student(&roster, "Paul", 3);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_students_are_sorted_by_grades_in_roster(void)
{
   TEST_IGNORE();
   student_t expected[] = {
      { 1, "Anna" }, 
      { 2, "Peter" },
      { 3, "Jim" } 
   };
   
   add_student(&roster, "Jim", 3);
   add_student(&roster, "Peter", 2);
   add_student(&roster, "Anna", 1);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_students_are_sorted_by_name_in_roster(void)
{
   TEST_IGNORE();
   student_t expected[] = {
      { 2, "Alex" }, 
      { 2, "Peter" },
      { 2, "Zoe" } 
   };
   
   add_student(&roster, "Peter", 2);
   add_student(&roster, "Zoe", 2);
   add_student(&roster, "Alex", 2);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_students_are_sorted_by_grades_and_then_by_names_in_roster(void)
{
   TEST_IGNORE();
   student_t expected[] = {
      { 1, "Anna" }, 
      { 1, "Barb" },
      { 1, "Charlie" },
      { 2, "Alex" }, 
      { 2, "Peter" },
      { 2, "Zoe" }, 
      { 3, "Jim" } 
   };
   
   add_student(&roster, "Peter", 2);
   add_student(&roster, "Anna", 1);
   add_student(&roster, "Barb", 1);
   add_student(&roster, "Zoe", 2);
   add_student(&roster, "Alex", 2);
   add_student(&roster, "Jim", 3);
   add_student(&roster, "Charlie", 1);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &roster);
}

static void test_grade_empty_if_no_students_in_roster(void)
{
   TEST_IGNORE();
   uint8_t desired_grade = 1;

   roster_t actual = get_grade(&roster, desired_grade);
   TEST_ASSERT_EQUAL(0, actual.size);
   free_roster(&actual);
}

static void test_grade_empty_if_no_students_in_grade(void)
{
   TEST_IGNORE();
   uint8_t desired_grade = 1;

   add_student(&roster, "Peter", 2);
   add_student(&roster, "Zoe", 2);
   add_student(&roster, "Alex", 2);
   add_student(&roster, "Jim", 3);

   roster_t actual = get_grade(&roster, desired_grade);
   TEST_ASSERT_EQUAL(0, actual.size);
   free_roster(&actual);
}

static void test_student_not_added_to_same_grade_more_than_once(void)
{
   TEST_IGNORE();
   uint8_t desired_grade = 2;
   student_t expected[] = {
      { 2, "Blair" }, 
      { 2, "James" },
      { 2, "Paul" } 
   };

   add_student(&roster, "Blair", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "Paul", 2);

   roster_t actual = get_grade(&roster, desired_grade);
   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &actual);
   free_roster(&actual);
}

static void test_remove_student_from_desired_grade(void)
{
   TEST_IGNORE();
   uint8_t desired_grade = 2;
   student_t expected[] = {
      { 2, "Blair" }, 
      { 2, "Paul" } 
   };

   add_student(&roster, "Blair", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "Paul", 2);

   roster_t actual = get_grade(&roster, desired_grade);
   remove_student(&actual, "James");
   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &actual);
   free_roster(&actual);
}

static void test_student_not_added_to_multiple_grades(void)
{
   TEST_IGNORE();
   uint8_t desired_grade = 2;
   student_t expected[] = {
      { 2, "Blair" }, 
      { 2, "James" }
   };

   add_student(&roster, "Blair", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "James", 3);
   add_student(&roster, "Paul", 3);

   roster_t actual = get_grade(&roster, desired_grade);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &actual);
   free_roster(&actual);
}

static void test_student_not_added_to_other_grade_for_multiple_grades(void)
{
   TEST_IGNORE();
   uint8_t desired_grade = 3;
   student_t expected[] = {
      { 3, "Paul" } 
   };

   add_student(&roster, "Blair", 2);
   add_student(&roster, "James", 2);
   add_student(&roster, "James", 3);
   add_student(&roster, "Paul", 3);

   roster_t actual = get_grade(&roster, desired_grade);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &actual);
   free_roster(&actual);
}

static void test_students_are_sorted_by_name_in_grade(void)
{
   TEST_IGNORE();
   uint8_t desired_grade = 5;
   student_t expected[] = {
      { 5, "Bradley" }, 
      { 5, "Franklin" } 
   };

   add_student(&roster, "Franklin", 5);
   add_student(&roster, "Bradley", 5);
   add_student(&roster, "Jeff", 1);

   roster_t actual = get_grade(&roster, desired_grade);

   check_rosters(expected, sizeof(expected)/sizeof(expected[0]), &actual);
   free_roster(&actual);
}
 
int main(void)
{
   UnityBegin("test_grade_school.c");

   RUN_TEST(test_roster_is_empty_when_no_student_added);
   RUN_TEST(test_cannot_remove_on_empty_list);
   RUN_TEST(test_add_student);
   RUN_TEST(test_student_added_to_roster);
   RUN_TEST(test_remove_student);
   RUN_TEST(test_cannot_remove_student_with_misspeled_name);
   RUN_TEST(test_adding_multiple_students_in_same_grade_in_roster);
   RUN_TEST(test_multiple_students_in_same_grade_are_added_to_roster);
   RUN_TEST(test_remove_first_student);   
   RUN_TEST(test_remove_middle_student);      
   RUN_TEST(test_remove_last_student);   
   RUN_TEST(test_cannot_add_student_to_same_grade_more_than_once);
   RUN_TEST(test_cannot_remove_student_more_than_once);
   RUN_TEST(test_student_not_added_to_same_grade_in_roster_more_than_once);
   RUN_TEST(test_student_not_removed_more_than_once);   
   RUN_TEST(test_can_add_removed_student);   
   RUN_TEST(test_adding_students_in_multiple_grades);
   RUN_TEST(test_students_in_multiple_grades_are_added_to_roster);
   RUN_TEST(test_cannot_add_same_student_to_multiple_grades_in_roster);
   RUN_TEST(test_student_not_added_to_multiple_grades_in_roster);
   RUN_TEST(test_students_are_sorted_by_grades_in_roster);
   RUN_TEST(test_students_are_sorted_by_name_in_roster);
   RUN_TEST(test_students_are_sorted_by_grades_and_then_by_names_in_roster);
   RUN_TEST(test_grade_empty_if_no_students_in_roster);
   RUN_TEST(test_grade_empty_if_no_students_in_grade);
   RUN_TEST(test_student_not_added_to_same_grade_more_than_once);
   RUN_TEST(test_remove_student_from_desired_grade);
   RUN_TEST(test_student_not_added_to_multiple_grades);
   RUN_TEST(test_student_not_added_to_other_grade_for_multiple_grades);
   RUN_TEST(test_students_are_sorted_by_name_in_grade); 

   return UnityEnd();
}
