#ifndef SCHOOL_MANAGER_SYSTEM_H_
#define SCHOOL_MANAGER_SYSTEM_H_

#include "Student.h"
#include "Course.h"

namespace PA4
{
    class SchoolSystem
    {
    public:
        void function1();

        // Constructors & Destructor
        SchoolSystem();
        ~SchoolSystem();

        void main_menu();
        void student_menu();
        void course_menu();
        void select_student_menu();

        void list_all_students();
        void list_all_courses();

        void add_student();
        void delete_student(Student *toDelete);
        void resize_student_list();
        void resize_course_list();

        Student *select_student(std::string id);
        bool add_student_to_course(Student *newStudent);

        void add_course();
        void select_course_menu();
        Course *select_course(std::string code);
        void delete_course(Course *toDelete);
        void run();
        void list_students_in_course(const Course *select);
        void delete_student_from_course(Student *toDelete);

    private:
        Course *courseList;      // Dynamically allocated array of courses
        Student *studentList;    // Dynamically allocated array of students
        int courseListSize;      // Size of course list
        int courseListCapacity;  // Capactiy of course lis
        int studentListSize;     // Size of student list
        int studentListCapacity; // Capactiy of student list
    };
}

#endif // SCHOOL_MANAGER_SYSTEM_H_