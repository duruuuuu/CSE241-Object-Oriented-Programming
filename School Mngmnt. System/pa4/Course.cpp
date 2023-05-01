#include <iostream>
#include "Course.h"
#include "Student.h"

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
        std::cout << "\nTEST\nStudents Enrolled Size: "
                  << studentsEnrolledSize << std::endl;

        if (studentsEnrolledSize < studentsEnrolledCapacity)
        {
            studentsEnrolled[studentsEnrolledSize] = newStudent;
            studentsEnrolledSize++;
        }

        else
        {
            resize_student_list();
            studentsEnrolled[studentsEnrolledSize] = newStudent;
            studentsEnrolledSize++;
        }

        std::cout << "New List:" << std::endl;
        for (int i = 0; i < studentsEnrolledSize; i++)
            std::cout << studentsEnrolled[i]->get_name() << std::endl;
    }

    void Course::resize_student_list()
    {
        studentsEnrolledCapacity *= 2;
        Student **newList = new Student *[studentsEnrolledCapacity];

        for (int i = 0; i < studentsEnrolledSize; i++)
            newList[i] = studentsEnrolled[i];

        delete[] studentsEnrolled;
        studentsEnrolled = newList;
    }

    Student Course::get_student(int index) const
    {
        return *studentsEnrolled[index];
    }

    Student *Course::get_student_address(int index)
    {
        return studentsEnrolled[index];
    }

    void Course::set_student(Student *student, int index)
    {
        studentsEnrolled[index] = student;
    }

    void Course::set_students_size(int size)
    {
        studentsEnrolledSize = size;
    }

    bool Course::is_enrolled(Student *student) const
    {
        for (int i = 0; i < studentsEnrolledSize; ++i)
        {
            if (studentsEnrolled[i] == student)
                return true;
        }
        return false;
    }
}