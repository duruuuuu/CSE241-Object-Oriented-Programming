#ifndef COURSE_H_
#define COURSE_H_

#include "Student.h"

namespace PA4
{
    class Student;
    class Course
    {
    public:
        // Constructors & Destructor
        Course();                                        // Default constructor
        Course(const Course &copy);                      // Copy constructor
        Course(std::string n, std::string c);            // constructor which takes name and code info
        Course(std::string n, int c, Student *students); // Constructor that takes all member data info
        ~Course();                                       // destructor

        // Setter Functions
        void set_name_code(std::string n, std::string c);
        void set_student(Student *student, int index);
        void set_students_size(int size);

        // Getter Functions
        std::string get_name() const;
        std::string get_code() const;
        Student **get_students() const;
        Student get_student(int index) const;
        Student *get_student_address(int index);
        int get_students_size() const { return studentsEnrolledSize; }

        Course &operator=(const Course &other);

        bool is_enrolled(Student *student) const;
        void add_student(Student *newStudent);
        void drop_student(Student *toDrop);

    private:
        std::string name;
        std::string code;

        Student **studentsEnrolled;
        int studentsEnrolledSize;
        int studentsEnrolledCapacity;

        void resize_student_list();
    };
}

#endif // COURSE_H_