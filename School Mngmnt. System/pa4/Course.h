#ifndef COURSE_H_
#define COURSE_H_

#include "Student.h"

namespace PA4
{
    class Student;
    class Course
    {
    public:
        void function1();

        // Constructors & Destructor
        Course();
        Course(const Course &copy);
        Course(std::string n, std::string c);
        // Course(std::string n, int c, Student *students);

        Course(const Student &students);
        ~Course();

        // Setter Functions
        void set_name_code(std::string n, std::string c);
        // void set_students(const Course &courses);
        void set_student(Student *student, int index);
        void set_students_size(int size);

        // Getter Functions
        std::string get_name() const;
        std::string get_code() const;
        Student **get_students() const;

        Course &operator=(const Course &other);

        bool is_enrolled(Student *student) const;
        void add_student(Student *newStudent);
        Student get_student(int index) const;
        Student *get_student_address(int index);
        int get_students_size() const { return studentsEnrolledSize; }
        void resize_student_list();

    private:
        std::string name;
        std::string code;

        // studentsEnroller pointer points to a dynamic array of students
        Student **studentsEnrolled;
        int studentsEnrolledSize;
        int studentsEnrolledCapacity;
    };
}

#endif // COURSE_H_