#include <iostream>
#include "SchoolManagerSystem.h"
#include "Course.h"
#include "Student.h"

const int SENT_VAL = -999;
const std::string SENT_STR = "-999";

namespace
{
    // Unnamed namespace is used for helping functions
    void parse_input_line(std::string inputLine, std::string &name, std::string &code)
    {
        // Create substring for course code
        std::size_t pos = inputLine.find(' ');
        code = inputLine.substr(0, pos);

        // Create substring for course name
        if (pos != std::string::npos)
            name = inputLine.substr(pos + 1);
    }
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
                break;

            case 3:
                list_all_students();
                break;

            case 4:
                std::cout << "\nCOURSE LIST:" << std::endl;
                list_all_courses();
                break;

            default:
                std::cout << "Please enter a valid input. MAIN MENU" << std::endl;
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
            std::cout << "\n===========================\nSTUDENT MENU" << std::endl;
            std::cout << "0 Up" << std::endl;
            std::cout << "1 Add Student" << std::endl;
            std::cout << "2 Select Student" << std::endl;

            int choice;
            if (!(std::cin >> choice))
            {
                // Clearing the error flag and ignoring the invalid input
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Please enter a valid input STUDENT MENU." << std::endl;
                continue;
            }

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
        std::cout << "\n===========================\nSELECT STUDENT" << std::endl;

        // Getting name and id
        std::string name;
        int id;
        std::cin >> name >> id;

        // Find the student in the list and create a temporary object for it
        Student *selectedStudent = select_student(name, id);

        if (selectedStudent == nullptr)
            return;

        while (true)
        {
            std::cout << "\n0 UP" << std::endl;
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
                break;

                // case 3:
                //  drop_student_from_course(selectedStudent);

            default:
                std::cout << "Please enter a valid input. SELECT STUDENT MENU" << std::endl;
                break;
            }
        }

        return;
    }

    Student *SchoolSystem::select_student(std::string name, int id)
    {
        for (int i = 0; i < studentListSize; i++)
        {
            if (studentList[i].get_name() == name)
            {
                // If the ID and name are the same, return the student
                if (studentList[i].get_id() == id)
                    return &studentList[i];

                // TODO: Continue checking if the ID does not match
            }
        }
        std::cout << "Student Not Found" << std::endl;
        return nullptr;
    }

    void SchoolSystem::add_student_to_course(Student *newStudent)
    {
        // TODO: Display message if there are no available classes to take

        //  new temporary course list that holds the courses not taken by the student
        Course **availableCourses = new Course *[courseListSize];

        // temporary course list of courses taken by the student
        Course *coursesTaken = newStudent->get_courses();

        std::cout << "\n0 UP" << std::endl;

        int count = 0;
        for (int i = 0; i < courseListSize; i++)
        {
            bool flag = false;
            int j = 0;
            for (j = 0; j < newStudent->get_course_size(); j++)
            {
                // If the course is taken by the student continue
                if (courseList[i].get_code() == coursesTaken[j].get_code())
                {
                    flag = true;
                    break;
                }
            }
            if (flag == true)
                continue;

            else
            {
                // If course is not taken, add to available course list and display
                availableCourses[count] = &courseList[i];
                std::cout << count + 1 << " "
                          << availableCourses[count]->get_code() << " "
                          << availableCourses[count]->get_name() << std::endl;
                count++;
            }
        }
        std::cout << "count: " << count << std::endl;
        // Get users choice for course
        int choice;
        std::cin >> choice;

        if (choice == 0)
        {
            delete[] availableCourses;
            // delete[] coursesTaken;
            return;
        }

        else if (choice > count || choice < 0)
            std::cout << "Invalid choice." << std::endl;
        else
        {
            newStudent->add_course(*availableCourses[choice - 1]);
            availableCourses[choice - 1]->add_student(newStudent);
        }

        delete[] availableCourses;

        return;
    }

    void SchoolSystem::delete_student(Student *toDelete)
    {
        int i;
        for (i = 0; i < studentListSize; i++)
        {
            if (studentList[i].get_name() == toDelete->get_name())
            {
                // If the ID and name are the same, return the student
                if (studentList[i].get_id() == toDelete->get_id())
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
            std::cout << "\n===========================\nCOURSE MENU" << std::endl;
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
        std::string name, code, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line(inputLine, name, code);

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
        std::cout << "\n===========================\nSELECT COURSE" << std::endl;

        // Getting course information
        std::string name, code, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line(inputLine, name, code);

        // Find the course in the list and create a temporary object for it
        Course selectedCourse = select_course(name, code);

        if (selectedCourse.get_code() == SENT_STR)
            return;

        while (true)
        {
            std::cout << "\n0 UP" << std::endl;
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
                list_students_in_course(selectedCourse);
                break;

            default:
                std::cout
                    << "Please enter a valid input SELECT COURSE MENU."
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
        std::cout << "Course Not Found" << std::endl;
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
        for (int j = i; j < courseListSize - 1; j++)
            courseList[j] = courseList[j + 1];

        // Decrement size of array
        courseListSize--;

        std::cout << "\nNew Course List:" << std::endl;
        list_all_courses();
    }

    void SchoolSystem::list_students_in_course(const Course &select)
    {
        std::cout << "\nStudents Enrolled:" << std::endl;
        for (int i = 0; i < select.get_students_size(); i++)
        {
            std::cout << i + 1 << ". " << select.get_student(i).get_name()
                      << " " << select.get_student(i).get_id() << std::endl;
        }
    }

    void SchoolSystem::list_all_courses()
    {
        for (int i = 0; i < courseListSize; i++)
        {
            std::cout << i + 1 << ". " << courseList[i].get_code()
                      << " " << courseList[i].get_name() << std::endl;
        }
        std::cout << std::endl;
    }

    void SchoolSystem::list_all_students()
    {
        std::cout << "\nSTUDENT LIST:" << std::endl;
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