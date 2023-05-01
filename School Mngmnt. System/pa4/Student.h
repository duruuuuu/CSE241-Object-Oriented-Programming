#ifndef STUDENT_H_
#define STUDENT_H_

#include "Course.h"

namespace PA4
{
    class Course;
    class Student
    {
    public:
        // Constructors & Destructor
        Student();
        Student(const Student &copy);
        Student(std::string n, std::string id);
        Student(std::string n, std::string id, Course *courses);
        // Student(const Course &courses);
        ~Student();

        // Setter Functions
        void set_name_id(std::string n, std::string id);
        void set_courses(const Course &courses);

        // Getter Functions
        std::string get_name() const;
        std::string get_id() const;
        Course **get_courses() const;
        int get_course_size() const { return coursesTakenSize; }

        Student &operator=(const Student &other);

        void add_course(Course *newCourse);
        void drop_course(Course *toDrop);
        Course get_course(int index) const;
        void resize_course_list();
        bool is_enrolled(Course *course) const;

    private:
        std::string name;
        std::string ID;

        //
        Course **coursesTaken;
        int coursesTakenSize;
        int coursesTakenCapacity;
    };
}

#endif // STUDENT_H_