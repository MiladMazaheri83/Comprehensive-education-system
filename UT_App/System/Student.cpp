#include "Student.hpp"

Student::Student(string Id, string name, int majorId, int semester)
    : Account(Id, name, majorId), semester(semester) {}
Student::~Student() {}

void Student::setStudentSemester(const int &studentSemester)
{
    semester = studentSemester;
}