#include <iostream>
#include "SchoolManagerSystem.h"
#include "Course.h"
#include "Student.h"

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
            std::cout << "MAIN MENU" << std::endl;
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

                /**
                  *TODO: CASES 2,3,4
                            case 2:
                                course_menu();

                            case 3:
                                list_all_students();

                            case 4:
                                list_all_courses();
                */
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
            std::cout << "STUDENT MENU" << std::endl;
            std::cout << "0 Up" << std::endl;
            std::cout << "1 Add Student" << std::endl;
            std::cout << "2 Select Student" << std::endl;

            int choice;
            std::cin >> choice;
            std::cout << "choice: " << choice << std::endl;
            switch (choice)
            {
            case 0:
                std::cout << "hit case 0" << std::endl;
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
        std::string name;
        int id;

        // Getting student information
        std::cout << "Student Name: ";
        std::cin >> name;
        std::cout << "Student ID: ";
        std::cin >> id;

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
        std::cout << "SELECT STUDENT" << std::endl;

        std::string name;
        int id;

        std::cout << "Student Name: ";
        std::cin >> name;
        std::cout << "Student ID: ";
        std::cin >> id;

        // Find the student in the list and create a temporary object for it
        // Student selectedStudent = select_student(name, id);

        std::cout << "0 UP" << std::endl;
        std::cout << "1 Delete Student" << std::endl;
        std::cout << "2 Add Selected Student to a Course" << std::endl;

        int choice;
        std::cin >> choice;

        do
        {
            switch (choice)
            {
            case 0:
                // If the choice is up, return to the upper menu
                choice = -1;
                break;

            case 1:
                // Adding a student
                // delete_student();

            case 2:
                // Selecting a student which is already in the list
                select_student_menu();

            default:
                std::cout << "Please enter a valid input." << std::endl;
                break;
            }
        } while (choice != -1);

        return;
    }

    void SchoolSystem::run()
    {
        main_menu();
    }
}