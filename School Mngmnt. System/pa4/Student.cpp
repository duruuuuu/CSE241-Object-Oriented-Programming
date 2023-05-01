#include <iostream>
#include "Student.h"
#include "Course.h"

const int INIT_CAPACITY = 10;

namespace
{
    // Unnamed namespace is useds for helping functions
}

namespace PA4
{
    Student::Student()
    {

        // Default Constructor creates an empty array of courses taken by the student
        coursesTakenSize = 0;
        coursesTakenCapacity = INIT_CAPACITY;
        coursesTaken = new Course *[coursesTakenCapacity];
    }

    Student::Student(const Student &copy)
        : name(copy.name), ID(copy.ID), coursesTakenSize(copy.coursesTakenSize),
          coursesTakenCapacity(copy.coursesTakenCapacity)
    {

        // Create a new array for the copied courses
        coursesTaken = new Course *[coursesTakenCapacity];

        // Copy the courses from the original student
        for (int i = 0; i < coursesTakenSize; i++)
            coursesTaken[i] = copy.coursesTaken[i];
    }

    Student::Student(std::string n, std::string id)
    {

        name = n;
        ID = id;

        coursesTakenSize = 0;
        coursesTakenCapacity = 10;
        coursesTaken = new Course *[coursesTakenCapacity];
    }

    // Student(std::string n, int id, Course *courses);

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
            coursesTaken = new Course *[coursesTakenCapacity];
            for (int i = 0; i < coursesTakenSize; i++)
            {
                coursesTaken[i] = other.coursesTaken[i];
            }
        }
        return *this;
    }

    void Student::set_name_id(std::string n, std::string id)
    {
        name = n;
        ID = id;
    }
    // void Student::set_courses(const Course &courses)

    std::string Student::get_name() const { return name; }
    std::string Student::get_id() const { return ID; }
    Course **Student::get_courses() const { return coursesTaken; }

    void Student::add_course(Course *newCourse)
    {
        if (coursesTakenSize < coursesTakenCapacity)
        {
            coursesTaken[coursesTakenSize] = newCourse;
            coursesTakenSize++;
        }

        else
        {
            resize_course_list();
            coursesTaken[coursesTakenSize] = newCourse;
            coursesTakenSize++;
        }
    }

    void Student::resize_course_list()
    {
        coursesTakenCapacity *= 2;
        Course **newList = new Course *[coursesTakenCapacity];

        for (int i = 0; i < coursesTakenSize; i++)
            newList[i] = coursesTaken[i];

        delete[] coursesTaken;
        coursesTaken = newList;
    }

    Course Student::get_course(int index) const
    {
        return *coursesTaken[index];
    }

    void Student::drop_course(Course *toDrop)
    {
        int i;
        for (i = 0; i < coursesTakenSize; i++)
        {
            if (toDrop == coursesTaken[i])
                break;
        }

        for (int j = i; j < coursesTakenSize - 1; j++)
            coursesTaken[j] = coursesTaken[j + 1];

        coursesTakenSize--;

        toDrop->drop_student(this);
    }

    bool Student::is_enrolled(Course *course) const
    {
        for (int i = 0; i < coursesTakenSize; ++i)
        {
            if (coursesTaken[i] == course)
                return true;
        }
        return false;
    }
}