#include "System.hpp"

void System::GET(const vector<string> &command)
{
    if (command[ONE_INDEX] == POST_WORD && ((mainUser == UT_MANAGER) || (mainUser == UT_PROFESSOR) || (mainUser == UT_STUDENT)))
        getPost(command);
    else if (command[ONE_INDEX] == NOTIFICATION && ((mainUser == UT_PROFESSOR) || (mainUser == UT_STUDENT)))
        notification(command);
    else if (command[ONE_INDEX] == COURSES && ((mainUser == UT_PROFESSOR) || (mainUser == UT_STUDENT)))
        courses(command);
    else if (command[ONE_INDEX] == COURSE_POST && ((mainUser == UT_PROFESSOR) || (mainUser == UT_STUDENT)))
        getCoursePost(command);
    else if (command[ONE_INDEX] == COURSE_CHANNEL && ((mainUser == UT_PROFESSOR) || (mainUser == UT_STUDENT)))
        courseChannel(command);
    else
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
}

void System::getPost(const vector<string> &command)
{
    checkNumberValidity("CommandKeyData(command, ID_INPUT)");
    checkNumberValidity("CommandKeyData(command, POST_ID_INPUT)");
    if (stoi("CommandKeyData(command, POST_ID_INPUT)") == ZERO)
        throw runtime_error(INCORRECT_REQUEST);
    if (command.size() == GET_POST_VALID_NUMBER_OF_ARGUMENT)
    {
        data.showPostData("CommandKeyData(command, ID_INPUT)", stoi("CommandKeyData(command, POST_ID_INPUT)"));
    }
    else
    {
        throw INCORRECT_REQUEST;
    }
}

void System::notification(const vector<string> &command)
{
    if (command.size() == NOTIFICATION_VALID_NUMBER_OF_ARGUMENT)
    {
        data.getNotification(mainUserId);
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
}

string System::personalPage(const string &userId)
{
    return data.getPageInfo(userId);
}

void System::courses(const vector<string> &command)
{
    if (command.size() == COURSES_VALID_NUMBER_OF_ARGUMENT_ONE)
    {
    }
    else if (command.size() == COURSES_VALID_NUMBER_OF_ARGUMENT_TWO)
    {
        if (stoi("CommandKeyData(command, ID_INPUT)") == ZERO)
            throw runtime_error(INCORRECT_REQUEST);
        checkNumberValidity("CommandKeyData(command, ID_INPUT)");
        data.showCourse(stoi("CommandKeyData(command, ID_INPUT)"));
    }
    else
    {
        throw INCORRECT_REQUEST;
    }
}

string System::getMyCourses(const string &id)
{
    return data.getStudentsCoursesData(id);
}

void System::getCoursePost(const vector<string> &command)
{
    checkNumberValidity("CommandKeyData(command, ID_INPUT)");
    checkNumberValidity("CommandKeyData(command, POST_ID_INPUT)");
    if (stoi("CommandKeyData(command, POST_ID_INPUT)") == ZERO)
        throw runtime_error(INCORRECT_REQUEST);
    if (command.size() == GET_COURSE_POST_VALID_NUMBER_OF_ARGUMENT)
    {
        data.showChannelPostData(stoi("CommandKeyData(command, ID_INPUT)"), stoi("CommandKeyData(command, POST_ID_INPUT)"));
    }
    else
    {
        throw INCORRECT_REQUEST;
    }
}

void System::courseChannel(const vector<string> &command)
{
    checkNumberValidity("CommandKeyData(command, ID_INPUT)");
    if (command.size() == COURSE_CHANNEL_VALID_NUMBER_OF_ARGUMENT)
    {
        data.getChannelInfo(stoi("CommandKeyData(command, ID_INPUT)"));
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
}