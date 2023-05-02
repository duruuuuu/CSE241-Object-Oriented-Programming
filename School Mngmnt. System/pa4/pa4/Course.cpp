#include <iostream>
#include "Student.h"
#include "Course.h"

const int INIT_CAPACITY = 10;

namespace
{
    // Unnamed namespace is used for helping functions
}

namespace PA4
{
    Course::Course()
        : studentsEnrolledSize(0), studentsEnrolledCapacity(INIT_CAPACITY)
    {
        // Default constructor
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
        : name(n), code(c), studentsEnrolledSize(0), studentsEnrolledCapacity(INIT_CAPACITY)
    {
        studentsEnrolled = new Student *[studentsEnrolledCapacity];
    }

    Course::~Course()
    {
        if (studentsEnrolled != NULL)
            delete[] studentsEnrolled;
    }

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
                studentsEnrolled[i] = other.studentsEnrolled[i];
        }

        return *this;
    }

    void Course::set_name_code(std::string n, std::string c)
    {
        name = n;
        code = c;
    }

    std::string Course::get_name() const { return name; }
    std::string Course::get_code() const { return code; }
    Student **Course::get_students() const { return studentsEnrolled; }

    void Course::add_student(Student *newStudent)
    {
        // Makes sure there is enough allocated memory in the array,
        // If there is not, it resizes the array, adds the new student and increments the size
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
    }

    void Course::resize_student_list()
    {
        // Double the capacity and create a new array with it
        studentsEnrolledCapacity *= 2;
        Student **newList = new Student *[studentsEnrolledCapacity];

        // Copy all the elements to new array
        for (int i = 0; i < studentsEnrolledSize; i++)
            newList[i] = studentsEnrolled[i];

        // Delete and reassign old array
        delete[] studentsEnrolled;
        studentsEnrolled = newList;
    }

    Student Course::get_student(int index) const
    {
        return *studentsEnrolled[index];
    }

    void Course::drop_student(Student *toDrop)
    {
        int i;
        for (i = 0; i < studentsEnrolledSize; i++)
        { //? COMPARE POINTERS OR IDS
            if (toDrop->get_id() == studentsEnrolled[i]->get_id())
                break;
        }

        for (int j = i; j < studentsEnrolledSize - 1; j++)
            studentsEnrolled[j] = studentsEnrolled[j + 1];

        studentsEnrolledSize--;
    }

    void Course::set_students_size(int size)
    {
        studentsEnrolledSize = size;
    }

    bool Course::is_enrolled(Student *student) const
    {
        for (int i = 0; i < studentsEnrolledSize; ++i)
        {
            if (studentsEnrolled[i]->get_id() == student->get_id())
                return true;
        }
        return false;
    }

}