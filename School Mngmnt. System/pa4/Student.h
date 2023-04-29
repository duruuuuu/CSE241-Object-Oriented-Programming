#ifndef STUDENT_H_
#define STUDENT_H_

#include "Course.h"

namespace PA4
{
    class Course;
    class Student
    {
    public:
        void function1();

        // Constructors & Destructor
        Student();
        Student(const Student &copy);
        Student(std::string n, int id);
        Student(std::string n, int id, Course *courses);
        Student(std::string n);
        Student(int id);
        // Student(const Course &courses);
        ~Student();

        // Setter Functions
        void set_name(std::string n);
        void set_id(int id);
        void set_name_id(std::string n, int id);
        void set_courses(const Course &courses);

        // Getter Functions
        std::string get_name() const;
        int get_id() const;
        Course **get_courses() const;

        Student &operator=(const Student &other);

    private:
        std::string name;
        int ID;

        // coursesTaken pointer points to an array of pointers that points to Courses
        Course **coursesTaken;
        int coursesTakenSize;
        int coursesTakenCapacity;
    };
}

#endif // STUDENT_H_