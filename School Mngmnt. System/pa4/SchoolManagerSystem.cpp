#include <iostream>
#include "SchoolManagerSystem.h"
#include "Course.h"
#include "Student.h"

const int SENT_VAL = -999;
const std::string SENT_STR = "-999";

namespace
{
    // Unnamed namespace is used for helping functions

}

namespace PA4
{
    void SchoolSystem::function1() { std::cout << "Hello System" << std::endl; }

    SchoolSystem::SchoolSystem()
    {
        courseListSize = 0;
        courseListCapacity = 10;
        courseList = new Course[courseListCapacity];

        studentListSize = 0;
        studentListCapacity = 10;
        studentList = new Student[studentListCapacity];
    }

    SchoolSystem::~SchoolSystem()
    {
        if (courseList != NULL)
            delete[] courseList;

        if (studentList != NULL)
            delete[] studentList;
    }

    void SchoolSystem::main_menu()
    {
        while (true)
        {
            // Printing menu
            std::cout << "===========================\nMAIN MENU" << std::endl;
            std::cout << "0 Exit" << std::endl;
            std::cout << "1 Student" << std::endl;
            std::cout << "2 Course" << std::endl;
            std::cout << "3 List All Students" << std::endl;
            std::cout << "4 List All Courses" << std::endl;

            int choice;
            std::cin >> choice;

            switch (choice)
            {
            case 0:
                // If the choice is 0, exit the program
                return;

            case 1:
                // Display student menu
                student_menu();
                break;

            case 2:
                course_menu();

            case 3:
                list_all_students();
                break;

            case 4:
                list_all_courses();
                break;

            default:
                std::cout << "Please enter a valid input." << std::endl;
                break;
            }
        }
        return;
    }

    void SchoolSystem::student_menu()
    {
        while (true)
        {
            // Printing menu
            std::cout << "\nSTUDENT MENU" << std::endl;
            std::cout << "0 Up" << std::endl;
            std::cout << "1 Add Student" << std::endl;
            std::cout << "2 Select Student" << std::endl;

            int choice;
            std::cin >> choice;
            switch (choice)
            {
            case 0:
                return;

            case 1:
                // Adding a student
                add_student();
                break;

            case 2:
                // Selecting a student which is already in the list
                select_student_menu();
                break;

            default:
                std::cout << "Please enter a valid input STUDENT MENU." << std::endl;
                break;
            }
        }
        return;
    }

    void SchoolSystem::add_student()
    {
        // Getting student information
        std::string name;
        int id;
        std::cin >> name >> id;

        // If the capactiy of the array is enough, add the student to the lsit
        if (studentListSize < studentListCapacity)
            studentList[studentListSize++] = Student(name, id);

        /**
          *TODO: implement Resize function
          // If the list is at capacity, resize the list and add the student
          else
          {
              resize_student_list();
             studentList[studentListSize++] = temp;
          }
        */

        return;
    }

    void SchoolSystem::select_student_menu()
    {
        // Printing menu
        std::cout << "\nSELECT STUDENT" << std::endl;

        // Getting name and id
        std::string name;
        int id;
        std::cin >> name >> id;

        // Find the student in the list and create a temporary object for it
        Student selectedStudent = select_student(name, id);

        if (selectedStudent.get_id() == SENT_VAL)
            return;

        while (true)
        {
            std::cout << "0 UP" << std::endl;
            std::cout << "1 Delete Student" << std::endl;
            std::cout << "2 Add Selected Student to a Course" << std::endl;

            int choice;
            std::cin >> choice;

            switch (choice)
            {
            case 0:
                // If the choice is up, return to the upper menu
                return;

            case 1:
                // Adding a student
                delete_student(selectedStudent);
                return;

            case 2:
                // Selecting a student which is already in the list
                add_student_to_course(selectedStudent);

            default:
                std::cout << "Please enter a valid input." << std::endl;
                break;
            }
        }

        return;
    }

    Student SchoolSystem::select_student(std::string name, int id)
    {
        for (int i = 0; i < studentListSize; i++)
        {
            if (studentList[i].get_name() == name)
            {
                // If the ID and name are the same, return the student
                if (studentList[i].get_id() == id)
                    return studentList[i];

                // TODO: Continue checking if the ID does not match
            }
        }
        std::cout << "Student Not Found" << std::endl;
        return Student(SENT_VAL);
    }

    void SchoolSystem::add_student_to_course(const Student &newStudent)
    {
        // TODO
    }

    void SchoolSystem::delete_student(const Student &toDelete)
    {
        int i;
        for (i = 0; i < studentListSize; i++)
        {
            if (studentList[i].get_name() == toDelete.get_name())
            {
                // If the ID and name are the same, return the student
                if (studentList[i].get_id() == toDelete.get_id())
                    break;

                // TODO: Continue checking if the ID does not match
            }
        }

        // Shift all elements after index to the left
        for (int j = i; j < studentListSize - 1; j++)
        {
            studentList[j] = studentList[j + 1];
        }

        // Decrement size of array
        studentListSize--;
    }

    void SchoolSystem::course_menu()
    {
        while (true)
        {
            // Printing menu
            std::cout << "\nCOURSE MENU" << std::endl;
            std::cout << "0 Up" << std::endl;
            std::cout << "1 Add Course" << std::endl;
            std::cout << "2 Select Course" << std::endl;

            int choice;
            std::cin >> choice;
            switch (choice)
            {
            case 0:
                return;

            case 1:
                // Adding a course
                add_course();
                break;

            case 2:
                // Selecting a course which is already in the list
                select_course_menu();
                break;

            default:
                std::cout << "Please enter a valid input STUDENT MENU." << std::endl;
                break;
            }
        }
        return;
    }

    void SchoolSystem::add_course()
    {
        // Getting course information
        std::string name, code;
        std::cin >> name >> code;

        // If the capactiy of the array is enough, add the student to the lsit
        if (courseListSize < courseListCapacity)
            courseList[courseListSize++] = Course(name, code);

        /**
          *TODO: implement Resize function
          // If the list is at capacity, resize the list and add the student
          else
          {
              resize_student_list();
             studentList[studentListSize++] = temp;
          }
        */

        return;
    }

    void SchoolSystem::select_course_menu()
    { // Printing menu
        std::cout << "\nSELECT COURSE" << std::endl;

        // Getting name and id
        std::string name, code;
        std::cin >> name >> code;

        // Find the student in the list and create a temporary object for it
        Course selectedCourse = select_course(name, code);

        if (selectedCourse.get_code() == SENT_STR)
            return;

        while (true)
        {
            std::cout << "0 UP" << std::endl;
            std::cout << "1 Delete Course" << std::endl;
            std::cout << "2 List Students in Course" << std::endl;

            int choice;
            std::cin >> choice;

            switch (choice)
            {
            case 0:
                // If the choice is up, return to the upper menu
                return;

            case 1:
                // Adding a student
                delete_course(selectedCourse);
                return;

            case 2:
                // Selecting a student which is already in the list
                // add_student_to_course(selectedCourse);
                break;

            default:
                std::cout
                    << "Please enter a valid input."
                    << std::endl;
                break;
            }
        }

        return;
    }

    Course SchoolSystem::select_course(std::string name, std::string code)
    {
        for (int i = 0; i < courseListSize; i++)
        {
            if (courseList[i].get_name() == name)
            {
                // If the ID and name are the same, return the student
                if (courseList[i].get_code() == code)
                    return courseList[i];

                // TODO: Continue checking if the ID does not match
            }
        }
        std::cout << "Student Not Found" << std::endl;
        return Course(SENT_STR, SENT_STR);
    }

    void SchoolSystem::delete_course(const Course &toDelete)
    {
        int i;
        for (i = 0; i < courseListSize; i++)
        {
            if (courseList[i].get_name() == toDelete.get_name())
            {
                // If the ID and name are the same, return the student
                if (courseList[i].get_code() == toDelete.get_code())
                    break;

                // TODO: Continue checking if the ID does not match
            }
        }

        // Shift all elements after index to the left
        for (int j = i; j < studentListSize - 1; j++)
        {
            courseList[j] = courseList[j + 1];
        }

        // Decrement size of array
        studentListSize--;
    }

    void SchoolSystem::list_all_courses()
    {
        for (int i = 0; i < courseListSize; i++)
        {
            std::cout << i + 1 << ". " << courseList[i].get_name()
                      << " " << courseList[i].get_code() << std::endl;
        }
        std::cout << std::endl;
    }

    void SchoolSystem::list_all_students()
    {
        for (int i = 0; i < studentListSize; i++)
        {
            std::cout << i + 1 << ". " << studentList[i].get_name()
                      << " " << studentList[i].get_id() << std::endl;
        }
        std::cout << std::endl;
    }

    void SchoolSystem::run()
    {
        main_menu();
    }
}