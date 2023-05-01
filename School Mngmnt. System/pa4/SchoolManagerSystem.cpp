#include <iostream>
#include "SchoolManagerSystem.h"
#include "Course.h"
#include "Student.h"

const int INIT_CAPACITY = 10;

namespace
{
    // Unnamed namespace is used for helping functions
    void parse_input_line_course(std::string inputLine, std::string &name, std::string &code)
    {
        // Create substring for course code
        std::size_t pos = inputLine.find(' ');
        code = inputLine.substr(0, pos);

        // Create substring for course name
        if (pos != std::string::npos)
            name = inputLine.substr(pos + 1);
    }
    void parse_input_line_student(std::string inputLine, std::string &name, std::string &idStr)
    {
        size_t idPos = 0;
        while (idPos < inputLine.length() && !isdigit(inputLine[idPos]))

            idPos++;

        // Extract the name substring from the input line
        name = inputLine.substr(0, idPos - 1);

        // Extract ID substring from input line and convert to int
        idStr = inputLine.substr(idPos);
    }
}

namespace PA4
{
    void SchoolSystem::function1() { std::cout << "Hello System" << std::endl; }

    SchoolSystem::SchoolSystem()
    {
        courseListSize = 0;
        courseListCapacity = INIT_CAPACITY;
        courseList = new Course[courseListCapacity];

        studentListSize = 0;
        studentListCapacity = INIT_CAPACITY;
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
        std::string name, id, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line_student(inputLine, name, id);

        // Check if the student already exists or if an ID is duplicated
        for (int i = 0; i < studentListSize; i++)
        {
            if (studentList[i].get_id() == id && studentList[i].get_name() == name)
            {
                std::cout << "This student already exists" << std::endl;
                return;
            }
            else if (studentList[i].get_id() == id && studentList[i].get_name() != name)
            {
                std::cout
                    << "A student with this ID already exists. Please enter a valid ID number." << std::endl;
                return;
            }
        }

        // If the capactiy of the array is enough, add the student to the lsit
        if (studentListSize < studentListCapacity)
        {
            studentList[studentListSize] = Student(name, id);
            studentListSize++;
        }
        // If the list is at capacity, resize the list and add the student
        else
        {
            resize_student_list();
            studentList[studentListSize] = Student(name, id);
            studentListSize++;
        }

        return;
    }

    void SchoolSystem::resize_student_list()
    {
        studentListCapacity *= 2;
        Student *newStudentList = new Student[studentListCapacity];
        for (int i = 0; i < studentListSize; i++)
            newStudentList[i] = studentList[i];
        std::cout << "hey" << std::endl;

        delete[] studentList;
        studentList = newStudentList;
    }

    void SchoolSystem::select_student_menu()
    {
        bool check = true;
        // Printing menu
        std::cout << "\n===========================\nSELECT STUDENT" << std::endl;

        // Getting name and id
        std::string name, id, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line_student(inputLine, name, id);

        // Find the student in the list and create a temporary object for it
        Student *selectedStudent = select_student(id);

        if (selectedStudent == nullptr)
            return;

        while (true)
        {
            std::cout << "\n0 UP" << std::endl;
            std::cout << "1 Delete Student" << std::endl;
            std::cout << "2 Add Selected Student to a Course" << std::endl;

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
                // If the choice is up, return to the upper menu
                return;

            case 1:
                // Adding a student
                delete_student(selectedStudent);
                return;

            case 2:
                // Selecting a student which is already in the list
                check = add_student_to_course(selectedStudent);
                if (check)
                {
                    std::cout << "\n"
                              << selectedStudent->get_name() << " Succesfully added to "
                              << selectedStudent->get_course(selectedStudent->get_course_size() - 1).get_name() << std::endl;
                }
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

    Student *SchoolSystem::select_student(std::string id)
    {
        for (int i = 0; i < studentListSize; i++)
        {
            // If the ID and name are the same, return the student
            if (studentList[i].get_id() == id)
                return &studentList[i];

            else
                continue;
        }
        std::cout << "Student Not Found" << std::endl;
        return nullptr;
    }

    bool SchoolSystem::add_student_to_course(Student *newStudent)
    {
        int count = 0;          // Number of available classes
        Course *selectedCourse; // Course that is selected by the user to add student to

        std::cout << "\n0 UP" << std::endl;

        // number of classes available and index tracker for available classes
        for (int i = 0; i < courseListSize; i++)
        {
            if (!courseList[i].is_enrolled(newStudent))
            {
                std::cout << count + 1 << " " << courseList[i].get_code()
                          << " " << courseList[i].get_name() << std::endl;
                count++;
            }
        }

        if (count == 0)
        {
            std::cout << "There are no available classes to take." << std::endl;
            return false;
        }

        // users choice for course
        int choice;
        if (!(std::cin >> choice))
        {
            // Clearing the error flag and ignoring the invalid input
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a valid input." << std::endl;
            return false;
        }

        if (choice == 0)
        {
            return false;
        }

        else if (choice > count || choice < 0)
        {
            std::cout << "Invalid choice." << std::endl;
            return false;
        }
        else
        {
            int availableCoursesIndex = 0;
            for (int i = 0; i < courseListSize; i++)
            {
                if (!courseList[i].is_enrolled(newStudent))
                {
                    availableCoursesIndex++;
                    if (availableCoursesIndex == choice)
                    {
                        selectedCourse = &courseList[i];
                        break;
                    }
                }
            }
            newStudent->add_course(selectedCourse);
            selectedCourse->add_student(newStudent);
            return true;
        }
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

                else
                    continue;
            }
        }

        // Shift all elements after index to the left
        for (int j = i; j < studentListSize - 1; j++)
        {
            studentList[j] = studentList[j + 1];
        }

        // Decrement size of array
        studentListSize--;

        // Delete student from any courses they are enrolled in
        delete_student_from_course(toDelete);
    }

    void SchoolSystem::delete_student_from_course(Student *toDelete)
    {
        for (int x = 0; x < courseListSize; x++)
        {
            int i;
            for (i = 0; i < courseList[x].get_students_size(); i++)
            {
                if (courseList[x].get_student(i).get_id() == toDelete->get_id())

                    break;

                else
                    continue;
            }

            // Shift all elements after index to the left
            for (int j = i; j < courseList[x].get_students_size() - 1; j++)
                courseList[x].set_student(courseList[x].get_student_address(j), j + 1);

            // Decrement size of array
            courseList[x].set_students_size(courseList[x].get_students_size() - 1);
        }
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
        parse_input_line_course(inputLine, name, code);

        // If the capactiy of the array is enough, add the student to the lsit
        if (courseListSize < courseListCapacity)
        {
            courseList[courseListSize] = Course(name, code);
            courseListSize++;
        }

        // If the list is at capacity, resize the list and add the student
        else
        {
            resize_student_list();
            courseList[studentListSize] = Course(name, code);
            courseListSize++;
        }

        return;
    }

    void SchoolSystem::resize_course_list()
    {
        courseListCapacity *= 2;
        Course *newCourseList = new Course[studentListCapacity];
        for (int i = 0; i < courseListSize; i++)
            newCourseList[i] = courseList[i];
        std::cout << "hey" << std::endl;

        delete[] courseList;
        courseList = newCourseList;
    }

    void SchoolSystem::select_course_menu()
    { // Printing menu
        std::cout << "\n===========================\nSELECT COURSE" << std::endl;

        // Getting course information
        std::string name, code, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line_course(inputLine, name, code);

        // Find the course in the list and create a temporary object for it
        Course *selectedCourse = select_course(code);

        if (selectedCourse == nullptr)
            return;

        while (true)
        {
            std::cout << "\n0 UP" << std::endl;
            std::cout << "1 Delete Course" << std::endl;
            std::cout << "2 List Students in Course" << std::endl;

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

    Course *SchoolSystem::select_course(std::string code)
    {
        for (int i = 0; i < courseListSize; i++)
        {
            if (courseList[i].get_code() == code)
                return &courseList[i];
        }
        std::cout << "Course Not Found" << std::endl;
        return nullptr;
    }

    void SchoolSystem::delete_course(Course *toDelete)
    {
        int i;
        for (i = 0; i < courseListSize; i++)
        {
            if (courseList[i].get_code() == toDelete->get_code())
                break;
        }

        // Shift all elements after index to the left
        for (int j = i; j < courseListSize - 1; j++)
            courseList[j] = courseList[j + 1];

        // Decrement size of array
        courseListSize--;

        std::cout << "\nNew Course List:" << std::endl;
        list_all_courses();
    }

    void SchoolSystem::list_students_in_course(const Course *select)
    {
        std::cout << "\nStudents Enrolled:" << std::endl;
        for (int i = 0; i < select->get_students_size(); i++)
        {
            std::cout << i + 1 << ". " << select->get_student(i).get_name()
                      << " " << select->get_student(i).get_id() << std::endl;
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