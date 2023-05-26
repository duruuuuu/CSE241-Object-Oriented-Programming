#ifndef SCHOOL_MANAGER_SYSTEM_H_
#define SCHOOL_MANAGER_SYSTEM_H_

#include "Student.h"
#include "Course.h"

namespace PA4
{
    class SchoolSystem
    {
    public:
        void run(); // Function to start the System class

        SchoolSystem();  // Default constructor
        ~SchoolSystem(); // Destructor

    private:
        // Course and Student lists hold pointers to the obojects
        Course **courseList;     // List of courses in the system
        Student **studentList;   // List of students in the system
        int courseListSize;      // Size of course list in the system
        int courseListCapacity;  // Capactiy of course list in the system
        int studentListSize;     // Size of student list list in the system
        int studentListCapacity; // Capactiy of student list list in the system

        void main_menu();
        void student_menu();
        void course_menu();

        void select_student_menu();
        void select_course_menu();

        void add_student();
        void delete_student(Student *toDelete);
        void add_student_to_course(Student *newStudent);
        void drop_student_from_course(Student *toDrop);
        Student *select_student(std::string id, std::string name);
        void resize_student_list();

        void add_course();
        void delete_course(Course *toDelete);
        void list_students_in_course(const Course *select);
        Course *select_course(std::string code, std::string name);
        void resize_course_list();

        void list_all_students();
        void list_all_courses();
    };
}

#endif // SCHOOL_MANAGER_SYSTEM_H_