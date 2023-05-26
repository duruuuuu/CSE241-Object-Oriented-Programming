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
        if (idPos != 0)
            name = inputLine.substr(0, idPos - 1);

        // Extract ID substring from input line and convert to int
        idStr = inputLine.substr(idPos);
    }
}

namespace PA4
{
    SchoolSystem::SchoolSystem()
        : courseListSize(0), studentListSize(0), courseListCapacity(INIT_CAPACITY), studentListCapacity(INIT_CAPACITY)
    {
        courseList = new Course *[courseListCapacity];
        studentList = new Student *[studentListCapacity];
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
            std::cout << ">> ";

            // Getting user input
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
                // Exit program
                return;

            case 1:
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
            std::cout << ">> ";

            int choice;
            if (!(std::cin >> choice))
            {
                // Clearing the error flag and ignoring the invalid input
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            switch (choice)
            {
            case 0:
                // Exit student menu
                return;

            case 1:
                add_student();
                break;

            case 2:
                select_student_menu();
                break;

            default:
                break;
            }
        }
        return;
    }

    void SchoolSystem::add_student()
    {
        // Getting student information
        std::cout << ">> ";
        std::string name, id, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line_student(inputLine, name, id);

        // Check if the student already exists or if an ID is duplicated,
        // Exists the function if the input is invalid
        for (int i = 0; i < studentListSize; i++)
        {
            if (studentList[i]->get_id() == id && studentList[i]->get_name() == name)
                return;

            else if (studentList[i]->get_id() == id && studentList[i]->get_name() != name)
                return;
        }

        // If an ID or name was not entered, return to previous menu
        if (id.empty() || name.empty())
            return;

        // If the capactiy of the array is enough, add the student to the list
        if (studentListSize < studentListCapacity)
        {
            studentList[studentListSize] = new Student(name, id);
            studentListSize++;
        }

        // If the list is at capacity, resize the list and add the student
        else
        {
            resize_student_list();
            studentList[studentListSize] = new Student(name, id);
            studentListSize++;
        }

        return;
    }

    void SchoolSystem::resize_student_list()
    {
        // Double the capacity
        studentListCapacity *= 2;

        // Create a new list with the new capacity
        Student **newStudentList = new Student *[studentListCapacity];
        for (int i = 0; i < studentListSize; i++)
            newStudentList[i] = studentList[i];

        delete[] studentList;         // Delete previous list
        studentList = newStudentList; // Update List
    }

    void SchoolSystem::select_student_menu()
    {

        // Getting name and id
        std::cout << ">> ";
        std::string name, id, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line_student(inputLine, name, id);

        // Find the student in the list and create a temporary object for it, return if student not found
        Student *selectedStudent = select_student(id, name);
        if (selectedStudent == nullptr)
            return;

        while (true)
        {
            std::cout << "\n0 UP" << std::endl;
            std::cout << "1 Delete Student" << std::endl;
            std::cout << "2 Add Selected Student to a Course" << std::endl;
            std::cout << "3 Drop Selected Student from a Course" << std::endl;
            std::cout << ">> ";

            int choice;
            if (!(std::cin >> choice))
            {
                //  Clearing the error flag and ignoring the invalid input
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            switch (choice)
            {
            case 0:
                return;

            case 1:
                delete_student(selectedStudent);
                return;

            case 2:
                add_student_to_course(selectedStudent);
                break;

            case 3:
                drop_student_from_course(selectedStudent);
                break;

            default:
                break;
            }
        }

        return;
    }

    Student *SchoolSystem::select_student(std::string id, std::string name)
    {
        // If the ID and name are the same, return the student's address
        // If there is any error in the input, return a null pointer
        for (int i = 0; i < studentListSize; i++)
        {
            if (studentList[i]->get_id() == id)
            {
                if (!name.empty() && name != studentList[i]->get_name())
                    return nullptr;

                return studentList[i];
            }
            else
                continue;
        }

        return nullptr;
    }

    void SchoolSystem::add_student_to_course(Student *newStudent)
    {
        int count = 0;          // Number of available classes
        Course *selectedCourse; // Course that is selected by the user to add student to

        std::cout << "\n0 UP" << std::endl;

        // Printing the available classes
        for (int i = 0; i < courseListSize; i++)
        {
            if (!courseList[i]->is_enrolled(newStudent))
            {
                std::cout << count + 1 << " " << courseList[i]->get_code()
                          << " " << courseList[i]->get_name() << std::endl;
                count++;
            }
        }

        // IF there are no classes to take, exit the function
        if (count == 0)
            return;

        std::cout << ">> ";
        // users choice for course
        int choice;
        if (!(std::cin >> choice))
        {
            // Clearing the error flag and ignoring the invalid input
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        // Exit choice
        if (choice == 0)
            return;

        // Invalid choice
        else if (choice > count || choice < 0)
            return;

        // Valid choice
        else
        {
            // Keeps track of the courses that are avaiable to take
            int availableCoursesIndex = 0;
            for (int i = 0; i < courseListSize; i++)
            {
                if (!courseList[i]->is_enrolled(newStudent))
                {
                    availableCoursesIndex++;
                    if (availableCoursesIndex == choice)
                    {
                        // If the student is not enrolled to a class and the index mathces the choice, stop the loop
                        selectedCourse = courseList[i];
                        break;
                    }
                }
            }

            // Add the selected course to the student and the student to the course
            newStudent->add_course(selectedCourse);
            selectedCourse->add_student(newStudent);
            return;
        }
    }

    void SchoolSystem::delete_student(Student *toDelete)
    {
        // Delete student from any courses they are enrolled in
        for (int i = 0; i < courseListSize; ++i)
        {
            if (courseList[i]->is_enrolled(toDelete))
                courseList[i]->drop_student(toDelete);
        }

        // Finds the student to be deleted in the system's list and holds its index
        int i;
        for (i = 0; i < studentListSize; i++)
        {
            if (studentList[i] == toDelete)
                break;

            else
                continue;
        }
        delete studentList[i]; // Free the deleted student's pointer

        // Shift all elements after student to delete to the left
        for (int j = i; j < studentListSize - 1; j++)
            studentList[j] = studentList[j + 1];

        // Decrement size of array
        studentListSize--;
    }

    void SchoolSystem::drop_student_from_course(Student *toDrop)
    {
        int count = 0;          // Number of available classes
        Course *selectedCourse; // Temp placeholder for course selected by user

        std::cout << "\n0 UP" << std::endl;

        // Displays students that the student is enrolled in
        for (int i = 0; i < courseListSize; i++)
        {
            if (courseList[i]->is_enrolled(toDrop))
            {
                std::cout << count + 1 << " " << courseList[i]->get_code()
                          << " " << courseList[i]->get_name() << std::endl;
                count++;
            }
        }

        // If there are no available courses to drop, exit
        if (count == 0)
            return;

        // users choice for course
        std::cout << ">> ";
        int choice;
        if (!(std::cin >> choice))
        {
            // Clearing the error flag and ignoring the invalid input
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        // Exit choice
        if (choice == 0)
            return;

        // Invalid choice
        else if (choice > count || choice < 0)
            return;

        // Finding the course that the user chose and assigning it to a placeholder object
        else
        {
            int availableCoursesIndex = 0;
            for (int i = 0; i < courseListSize; i++)
            {
                if (courseList[i]->is_enrolled(toDrop))
                {
                    availableCoursesIndex++;
                    if (availableCoursesIndex == choice)
                    {
                        selectedCourse = courseList[i];
                        break;
                    }
                }
            }

            // Dropping student from course
            toDrop->drop_course(selectedCourse);
            return;
        }
    }

    void SchoolSystem::course_menu()
    {
        while (true)
        {
            // Printing menu
            std::cout << "COURSE MENU" << std::endl;
            std::cout << "0 Up" << std::endl;
            std::cout << "1 Add Course" << std::endl;
            std::cout << "2 Select Course" << std::endl;
            std::cout << ">> ";

            int choice; // User's input for their choice of action
            if (!(std::cin >> choice))
            {
                // Clearing the error flag and ignoring the invalid input
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            switch (choice)
            {
            case 0:
                return;

            case 1:
                add_course();
                break;

            case 2:
                select_course_menu();
                break;

            default:
                break;
            }
        }
        return;
    }

    void SchoolSystem::add_course()
    {
        // Getting course information
        std::cout << ">> ";
        std::string name, code, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line_course(inputLine, name, code);

        // If the course information entered was incomplete
        if (code.empty() || name.empty())
            return;

        // If the capactiy of the array is enough, add the course to the list by creating a new dynamic pointer for it
        if (courseListSize < courseListCapacity)
        {
            courseList[courseListSize] = new Course(name, code);
            courseListSize++;
        }

        // If the list is at capacity, resize the list and add the student
        else
        {
            resize_course_list();
            courseList[courseListSize] = new Course(name, code);
            courseListSize++;
        }

        return;
    }

    void SchoolSystem::resize_course_list()
    {
        // Double the capacity, create a new array, copy all the elements, delete old array and reassign to new array
        courseListCapacity *= 2;
        Course **newCourseList = new Course *[courseListCapacity];
        for (int i = 0; i < courseListSize; i++)
            newCourseList[i] = courseList[i];

        delete[] courseList;
        courseList = newCourseList;
    }

    void SchoolSystem::select_course_menu()
    {
        // Printing menu
        std::cout << ">> ";

        // Getting course information
        std::string name, code, inputLine;
        std::cin.ignore();
        std::getline(std::cin, inputLine);
        parse_input_line_course(inputLine, name, code);

        // Find the course in the list and create a temporary object for it
        Course *selectedCourse = select_course(code, name);

        if (selectedCourse == nullptr)
            return;

        while (true)
        {
            std::cout << "0 UP" << std::endl;
            std::cout << "1 Delete Course" << std::endl;
            std::cout << "2 List Students in Course" << std::endl;
            std::cout << ">> ";

            int choice;
            if (!(std::cin >> choice))
            {
                // Clearing the error flag and ignoring the invalid input
                std::cin.clear();
                std::cin.ignore(10000, '\n');
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
                    << std::endl;
                break;
            }
        }

        return;
    }

    Course *SchoolSystem::select_course(std::string code, std::string name)
    {
        // Return the pointer of the selected course by checking course ID and name, or nullptr if the course does not exist
        for (int i = 0; i < courseListSize; i++)
        {
            if (courseList[i]->get_code() == code)
            {
                if ((!name.empty()) && name != courseList[i]->get_name())
                    return nullptr;
                return courseList[i];
            }
        }
        return nullptr;
    }

    void SchoolSystem::delete_course(Course *toDelete)
    {
        // Drop course from any students who are enrolled in it
        for (int i = 0; i < studentListSize; ++i)
        {
            if (studentList[i]->is_enrolled(toDelete))
                studentList[i]->drop_course(toDelete);
        }

        // Find the course to delete and hold its index
        int i;
        for (i = 0; i < courseListSize; i++)
        {
            if (courseList[i] == toDelete)
                break;
        }
        delete courseList[i]; // Delete the pointer of the course to be deleted

        // Shift all elements after index to the left
        for (int j = i; j < courseListSize - 1; j++)
            courseList[j] = courseList[j + 1];

        // Decrement size of array
        courseListSize--;

        // Display new course list
        std::cout << "\nUpdated Course List:" << std::endl;
        list_all_courses();
    }

    void SchoolSystem::list_students_in_course(const Course *select)
    {
        // Loop to list students in a specific course
        std::cout << "\nStudents Enrolled:" << std::endl;
        for (int i = 0; i < select->get_students_size(); i++)
        {
            std::cout << i + 1 << ". " << select->get_student(i).get_name()
                      << " " << select->get_student(i).get_id() << std::endl;
        }
        std::cout << std::endl;
    }

    void SchoolSystem::list_all_courses()
    {
        // Listing courses in a loop
        for (int i = 0; i < courseListSize; i++)
        {
            std::cout << i + 1 << ". " << courseList[i]->get_code()
                      << " " << courseList[i]->get_name() << std::endl;
        }
        std::cout << std::endl;
    }

    void SchoolSystem::list_all_students()
    {
        // Listing students in a loop
        std::cout << "\nSTUDENT LIST:" << std::endl;
        for (int i = 0; i < studentListSize; i++)
        {
            std::cout << i + 1 << ". " << studentList[i]->get_name()
                      << " " << studentList[i]->get_id() << std::endl;
        }
        std::cout << std::endl;
    }

    void SchoolSystem::run()
    {
        // Public Function that starts the School System Program
        main_menu();
    }

}