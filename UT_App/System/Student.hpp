#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "Account.hpp"

class Student : public Account
{
private:
    int semester;

public:
    Student(string Id, string name, int majorId, int semester);
    ~Student();
    string getType() const override { return "Student"; }
    int getSemester() { return semester; }
    void setStudentSemester(const int &studentSemester);
};

#endif // STUDENT_HPP