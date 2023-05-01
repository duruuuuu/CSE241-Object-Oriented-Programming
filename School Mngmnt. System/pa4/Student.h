#ifndef STUDENT_H_
#define STUDENT_H_

#include "Course.h"

namespace PA4
{
    class Course;
    class Student
    {
    public:
        Student();                                               // Default Constructor
        Student(const Student &copy);                            // Copy Constructor
        Student(std::string n, std::string id);                  // Constructor that takes name and ID
        Student(std::string n, std::string id, Course *courses); // Constructor that takes all member data info
        ~Student();                                              // Destructor

        Student &operator=(const Student &other);

        // Setter Functions
        void set_name_id(std::string n, std::string id);
        void set_courses(const Course &courses);

        // Getter Functions
        std::string get_name() const;
        std::string get_id() const;
        int get_course_size() const { return coursesTakenSize; }
        Course **get_courses() const;
        Course get_course(int index) const;

        void add_course(Course *newCourse);
        void drop_course(Course *toDrop);

        bool is_enrolled(Course *course) const;

    private:
        std::string name;
        std::string ID;

        Course **coursesTaken;
        int coursesTakenSize;
        int coursesTakenCapacity;

        void resize_course_list();
    };
}

#endif // STUDENT_H_