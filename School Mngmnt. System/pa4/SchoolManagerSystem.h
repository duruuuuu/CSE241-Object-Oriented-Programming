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
        void list_all_students();
        void list_all_courses();

        void add_student();
        void select_student_menu();

        void resize_student_list();
        Student select_student(std::string name, int id);
        void run();

    private:
        Course *courseList;
        Student *studentList;
        int courseListSize;
        int courseListCapacity;
        int studentListSize;
        int studentListCapacity;
    };
}

#endif // SCHOOL_MANAGER_SYSTEM_H_