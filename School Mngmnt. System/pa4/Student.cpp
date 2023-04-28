#include <iostream>
#include "Student.h"
#include "Course.h"

namespace
{
    // Unnamed namespace is useds for helping functions
}

namespace PA4
{
    void Student::function1() { std::cout << "Hello Student" << std::endl; }

    Student::Student()
    {
        // Default Constructor creates an empty array of courses taken by the student
        coursesTakenSize = 0;
        coursesTakenCapacity = 10;
        coursesTaken = new Course[coursesTakenCapacity];
    }

    Student::Student(const Student &copy)
        : name(copy.name), ID(copy.ID), coursesTakenSize(copy.coursesTakenSize),
          coursesTakenCapacity(copy.coursesTakenCapacity)
    {
        // Create a new array for the copied courses
        coursesTaken = new Course[coursesTakenCapacity];

        // Copy the courses from the original student
        for (int i = 0; i < coursesTakenSize; i++)
        {
            coursesTaken[i] = copy.coursesTaken[i];
        }
    }

    Student::Student(std::string n, int id)
    {
        name = n;
        ID = id;

        coursesTakenSize = 0;
        coursesTakenCapacity = 10;
        coursesTaken = new Course[coursesTakenCapacity];
    }

    // Student(std::string n, int id, Course *courses);

    Student::Student(std::string n)
    {
        name = n;
        ID = -1;

        coursesTakenSize = 0;
        coursesTakenCapacity = 10;
        coursesTaken = new Course[coursesTakenCapacity];
    }

    Student::Student(int id)
    {
        ID = id;

        coursesTakenSize = 0;
        coursesTakenCapacity = 10;
        coursesTaken = new Course[coursesTakenCapacity];
    }

    // Student(Course &courses);

    Student::~Student()
    {
        if (coursesTaken != NULL)
            delete[] coursesTaken;
    }

    // Assignment Operator
    Student &Student::operator=(const Student &other)
    {
        // Check for self-assignment
        if (this != &other)
        {
            // Copy the name and ID
            name = other.name;
            ID = other.ID;

            // Copy the courses
            delete[] coursesTaken;
            coursesTakenSize = other.coursesTakenSize;
            coursesTakenCapacity = other.coursesTakenCapacity;
            coursesTaken = new Course[coursesTakenCapacity];
            for (int i = 0; i < coursesTakenSize; i++)
            {
                coursesTaken[i] = other.coursesTaken[i];
            }
        }
        return *this;
    }

    void Student::set_name(std::string n) { name = n; }
    void Student::set_id(int id) { ID = id; }
    void Student::set_name_id(std::string n, int id)
    {
        name = n;
        ID = id;
    }
    // void Student::set_courses(const Course &courses)

    std::string Student::get_name() const { return name; }
    int Student::get_id() const { return ID; }
    Course *Student::get_courses() const { return coursesTaken; }
}