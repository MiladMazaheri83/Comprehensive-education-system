#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <cmath>
#include <vector>
#include <map>
#include "Data.hpp"
#include "SystemDefine.hpp"
using namespace std;

class System
{
public:
    string mainUserId = "";
    Data data;
    string mainUser = NOT_ENTERED;
    string getMyCourses(const string &id);
    string personalPage(const string &userId);
    void logout();
    void validateInputMethod(const string &methodInput);
    void validateCommandInput(const string &inputCommand);
    void checkPermission(const string &inputCommand);
    void unknownUserPermission(const string &inputCommand);
    void checkStudentPermission(const string &inputCommand);
    void checkProfessorPermission(const string &inputCommand);
    void checkUTManagerAccess(const string &inputCommand);
    void getPost(const vector<string> &command);
    void myCourses(const int &courseId);
    void POST(vector<string> &command);
    void GET(const vector<string> &command);
    void post(vector<string> &command);
    void connect(const vector<string> &command);
    void notification(const vector<string> &command);
    void courseOffer(const int &courseCapacity, const int &courseClassNumber, const string &courseId, const string &professorId, const string &examData, const string &time);
    void courses(const vector<string> &command);
    void deletePost(const vector<string> &command);
    void deleteCourse(const int &courseId);
    void profilePhoto(const string profileImagePath);
    void postTAForm(vector<string> &command);
    void taRequest(const vector<string> &command);
    void closeTAForm(const vector<string> &command);
    void coursePost(vector<string> &command);
    void getCoursePost(const vector<string> &command);
    void courseChannel(const vector<string> &command);
    void checkEnterPermission(const string &Id, const string &password, const string &userState);
    System(char *filesPath[]);
};

void checkNumberValidity(string Number);

#endif // SYSTEM_HPP