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
    Student::Student()
        : coursesTakenSize(0), coursesTakenCapacity(INIT_CAPACITY)
    {
        // Default Constructor creates an empty array of courses taken by the student
        coursesTaken = new Course *[coursesTakenCapacity];
    }

    Student::Student(const Student &copy)
        : name(copy.name), ID(copy.ID), coursesTakenSize(copy.coursesTakenSize), coursesTakenCapacity(copy.coursesTakenCapacity)
    {

        // Create a new array for the copied courses
        coursesTaken = new Course *[coursesTakenCapacity];

        // Copy the courses from the original student
        for (int i = 0; i < coursesTakenSize; i++)
            coursesTaken[i] = copy.coursesTaken[i];
    }

    Student::Student(std::string n, std::string id)
        : coursesTakenSize(0), coursesTakenCapacity(INIT_CAPACITY), name(n), ID(id)
    {
        coursesTaken = new Course *[coursesTakenCapacity];
    }

    Student::~Student()
    {
        if (coursesTaken != NULL)
            delete[] coursesTaken;
    }

    Student &Student::operator=(const Student &other)
    {
        // Check for self-assignment
        if (this != &other)
        {
            // Copy the name and ID
            name = other.name;
            ID = other.ID;

            delete[] coursesTaken; // Delete previous courses if any
            coursesTakenSize = other.coursesTakenSize;
            coursesTakenCapacity = other.coursesTakenCapacity;
            // Create new list and copy elements
            coursesTaken = new Course *[coursesTakenCapacity];
            for (int i = 0; i < coursesTakenSize; i++)
                coursesTaken[i] = other.coursesTaken[i];
        }
        return *this;
    }

    void Student::set_name_id(std::string n, std::string id)
    {
        name = n;
        ID = id;
    }

    std::string Student::get_name() const { return name; }
    std::string Student::get_id() const { return ID; }
    Course **Student::get_courses() const { return coursesTaken; }

    void Student::add_course(Course *newCourse)
    {
        // Adding the course to the index of the current size and incrementing the size
        // If the capactiy has been reached, resize the array
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
        // Doubling the capactiy and creating a new array with it
        coursesTakenCapacity *= 2;
        Course **newList = new Course *[coursesTakenCapacity];

        // Copying all the elements to the new array
        for (int i = 0; i < coursesTakenSize; i++)
            newList[i] = coursesTaken[i];

        // Deleting the old array and assigning the new one to it
        delete[] coursesTaken;
        coursesTaken = newList;
    }

    Course Student::get_course(int index) const
    {
        return *coursesTaken[index];
    }

    void Student::drop_course(Course *toDrop)
    {
        int i; // Index of course to drop
        for (i = 0; i < coursesTakenSize; i++)
        {
            if (toDrop->get_code() == coursesTaken[i]->get_code())
                break;
        }

        // Delete course from the student's list by shifting the list to the left from the index of dropped course
        for (int j = i; j < coursesTakenSize - 1; j++)
            coursesTaken[j] = coursesTaken[j + 1];

        coursesTakenSize--;

        toDrop->drop_student(this); // Remove student from the course's
    }

    bool Student::is_enrolled(Course *course) const
    {
        // compare the courses in the list until (if) the chosen course is found
        for (int i = 0; i < coursesTakenSize; ++i)
        {
            if (coursesTaken[i]->get_code() == course->get_code())
                return true;
        }
        return false;
    }
}