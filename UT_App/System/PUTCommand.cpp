#include "System.hpp"

void System::myCourses(const int &courseId)
{
    checkNumberValidity(to_string(courseId));
    if (courseId == ZERO)
        throw runtime_error(INCORRECT_REQUEST);
    data.courseRegister(courseId, mainUserId);
    data.sendSystemNotification(data.notifGenerator(GET_COURSE_NOTIF, mainUserId, true), mainUserId);
}