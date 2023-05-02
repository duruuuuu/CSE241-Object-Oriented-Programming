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
        void set_students_size(int size);

        // Getter Functions
        std::string get_name() const;
        std::string get_code() const;
        Student **get_students() const;
        Student get_student(int index) const;
        int get_students_size() const { return studentsEnrolledSize; }

        Course &operator=(const Course &other);

        bool is_enrolled(Student *student) const;
        void add_student(Student *newStudent);
        void drop_student(Student *toDrop);

    private:
        std::string name;
        std::string code;

        Student **studentsEnrolled; // Array of pointers pointing to students
        int studentsEnrolledSize;
        int studentsEnrolledCapacity;

        void resize_student_list();
    };
}

#endif // COURSE_H_