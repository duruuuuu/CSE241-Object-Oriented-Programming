#include <iostream>
#include "Course.h"
#include "Student.h"

const std::string SENT_VAL = "-999";
const int INIT_CAPACITY = 10;

namespace
{
    // Unnamed namespace is useds for helping functions
}

namespace PA4
{
    void Course::function1() { std::cout << "Hello Course" << std::endl; }

    Course::Course()
    {
        studentsEnrolledSize = 0;
        studentsEnrolledCapacity = INIT_CAPACITY;
        studentsEnrolled = new Student *[studentsEnrolledCapacity];
    }

    Course::Course(const Course &copy)
        : name(copy.name), code(copy.code), studentsEnrolledSize(copy.studentsEnrolledSize), studentsEnrolledCapacity(copy.studentsEnrolledCapacity)
    {

        // Create new array for the copied students
        studentsEnrolled = new Student *[studentsEnrolledCapacity];

        // Copy the students from the original course
        for (int i = 0; i < studentsEnrolledSize; i++)
            studentsEnrolled[i] = copy.studentsEnrolled[i];
    }

    Course::Course(std::string n, std::string c)
        : name(n), code(c)
    {
        studentsEnrolledSize = 0;
        studentsEnrolledCapacity = INIT_CAPACITY;
        studentsEnrolled = new Student *[studentsEnrolledCapacity];
    }

    Course::~Course()
    {
        if (studentsEnrolled != NULL)
            delete[] studentsEnrolled;
    }

    void Course::set_name_code(std::string n, std::string c)
    {
        name = n;
        code = c;
    }

    std::string Course::get_name() const { return name; }
    std::string Course::get_code() const { return code; }
    Student **Course::get_students() const { return studentsEnrolled; }

    Course &Course::operator=(const Course &other)
    { // Check for self-assignment
        if (this != &other)
        {
            // Copy the name and ID
            name = other.name;
            code = other.code;

            // Copy the courses
            delete[] studentsEnrolled;
            studentsEnrolledSize = other.studentsEnrolledSize;
            studentsEnrolledCapacity = other.studentsEnrolledCapacity;
            studentsEnrolled = new Student *[studentsEnrolledCapacity];
            for (int i = 0; i < studentsEnrolledSize; i++)
            {
                studentsEnrolled[i] = other.studentsEnrolled[i];
            }
        }
        return *this;
    }

    void Course::add_student(Student *newStudent)
    {
        // TODO: Implement resize of capacity is reached
        if (studentsEnrolledSize < studentsEnrolledCapacity)
        {
            studentsEnrolled[studentsEnrolledSize] = newStudent;
            studentsEnrolledSize++;
        }
    }

    Student Course::get_student(int index) const
    {
        return studentsEnrolled[0][index];
    }
}