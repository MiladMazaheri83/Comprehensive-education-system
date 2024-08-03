#include "System.hpp"

void System::deleteCourse(const int &courseId)
{
    checkNumberValidity(to_string(courseId));
    if (courseId == ZERO)
        throw runtime_error(INCORRECT_REQUEST);
    data.removeCourse(mainUserId, courseId);
    data.sendSystemNotification(data.notifGenerator(DELETE_COURSE_NOTIF, mainUserId, true), mainUserId);
}

void System::deletePost(const vector<string> &command)
{
    checkNumberValidity("CommandKeyData(command, ID_INPUT)");
    if (stoi("CommandKeyData(command, ID_INPUT)") == ZERO)
        throw runtime_error(INCORRECT_REQUEST);
    if (command.size() == DELETE_POST_VALID_NUMBER_OF_ARGUMENT)
    {
        data.removePost(mainUserId, stoi("CommandKeyData(command, ID_INPUT)"));
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
    throw runtime_error(SUCCESSFUL_COMMAND);
}