#include "System.hpp"

void System::POST(vector<string> &command)
{
    if (command[ONE_INDEX] == POST_WORD && ((mainUser == UT_MANAGER) || (mainUser == UT_PROFESSOR) || (mainUser == UT_STUDENT)))
        post(command);
    else if (command[ONE_INDEX] == CONNECT && ((mainUser == UT_PROFESSOR) || (mainUser == UT_STUDENT)))
        connect(command);
    else if (command[ONE_INDEX] == TA_FORM && (mainUser == UT_PROFESSOR))
        postTAForm(command);
    else if (command[ONE_INDEX] == CLOSE_TA_FORM && (mainUser == UT_PROFESSOR))
        closeTAForm(command);
    else if (command[ONE_INDEX] == TA_REQUEST && (mainUser == UT_STUDENT))
        taRequest(command);
    else if (command[ONE_INDEX] == COURSE_POST && ((mainUser == UT_PROFESSOR) || (mainUser == UT_STUDENT)))
        coursePost(command);
    else
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
}

void System::logout()
{
    mainUser = NOT_ENTERED;
    mainUserId = "";
}

void System::post(vector<string> &command)
{
    if (command.size() == POST_VALID_NUMBER_OF_ARGUMENT_ONE)
    {
        shared_ptr<SocialPost> newPost = make_shared<SocialPost>(data.getNewPostId(mainUserId), mainUserId, "", EMPTY_STRING, "CommandKeyData(command, TITLE)");
        data.addPost(newPost, mainUserId);
        data.sendSystemNotification(data.notifGenerator(NEW_POST_NOTIF, mainUserId, true), mainUserId);
    }
    else if (command.size() == POST_VALID_NUMBER_OF_ARGUMENT_TWO)
    {
        shared_ptr<SocialPost> newPost = make_shared<SocialPost>(data.getNewPostId(mainUserId), mainUserId, "CommandKeyData(command, MESSAGE)", "CommandKeyData(command, IMAGE)", "CommandKeyData(command, TITLE)");
        data.addPost(newPost, mainUserId);
        data.sendSystemNotification(data.notifGenerator(NEW_POST_NOTIF, mainUserId, true), mainUserId);
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
    throw runtime_error(SUCCESSFUL_COMMAND);
}

void System::connect(const vector<string> &command)
{
    checkNumberValidity("CommandKeyData(command, ID_INPUT)");
    if (command.size() == CONNECT_VALID_NUMBER_OF_ARGUMENT)
    {
        data.follow(mainUserId, "CommandKeyData(command, ID_INPUT)");
        data.addToMainUserFollowing(mainUserId, "CommandKeyData(command, ID_INPUT");
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
    throw runtime_error(SUCCESSFUL_COMMAND);
}

void System::courseOffer(const int &courseCapacity, const int &courseClassNumber, const string &courseId, const string &professorId, const string &examData, const string &time)
{
    checkNumberValidity(courseId);
    if (stoi(courseId) == ZERO)
        throw runtime_error(INCORRECT_REQUEST);
    checkNumberValidity(professorId);
    checkNumberValidity(to_string(courseCapacity));
    checkNumberValidity(to_string(courseClassNumber));
    shared_ptr<Course> newCourseOffer = make_shared<Course>();
    data.initializeCourseOfferData(newCourseOffer, courseId, courseCapacity, courseClassNumber);
    data.assignProfessor(newCourseOffer, professorId);
    data.setCourseTime(newCourseOffer, professorId, examData, time);
    data.addCourseToArchive(newCourseOffer);
    data.sendSystemNotification(data.notifGenerator(NEW_COURSE_OFFERING_NOTIF, professorId, true), mainUserId);
}

void System::profilePhoto(const string profileImagePath)
{
    data.addProfileToAccount(mainUserId, profileImagePath);
}

void System::postTAForm(vector<string> &command)
{
    int courseId = stoi("CommandKeyData(command, COURSE_ID)");
    if (command.size() == POST_TA_FORM_VALID_NUMBER_OF_ARGUMENT_ONE)
    {
        shared_ptr<TA_formPost> newPost = make_shared<TA_formPost>(data.getNewPostId(mainUserId), mainUserId, "CommandKeyData(command, MESSAGE)", EMPTY_STRING, courseId);
        data.addTAform(newPost, mainUserId, courseId);
        data.sendSystemNotification(data.notifGenerator(NEW_FORM_NOTIF, mainUserId, true), mainUserId);
    }
    else if (command.size() == POST_TA_FORM_VALID_NUMBER_OF_ARGUMENT_TWO)
    {
        shared_ptr<TA_formPost> newPost = make_shared<TA_formPost>(data.getNewPostId(mainUserId), mainUserId, "CommandKeyData(command, MESSAGE)", "CommandKeyData(command, IMAGE)", courseId);
        data.addTAform(newPost, mainUserId, courseId);
        data.sendSystemNotification(data.notifGenerator(NEW_FORM_NOTIF, mainUserId, true), mainUserId);
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
    throw runtime_error(SUCCESSFUL_COMMAND);
}

void System::taRequest(const vector<string> &command)
{
    string professorId = "CommandKeyData(command, PROFESSOR_ID)";
    int formId = stoi("CommandKeyData(command, FORM_ID)");
    checkNumberValidity(professorId);
    checkNumberValidity(to_string(formId));
    if (command.size() == TA_REQUEST_VALID_NUMBER_OF_ARGUMENT)
    {
        data.requestTAform(mainUserId, professorId, formId);
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
    throw runtime_error(SUCCESSFUL_COMMAND);
}

void System::closeTAForm(const vector<string> &command)
{
    string professorResponse;
    int formId = stoi("CommandKeyData(command, ID_INPUT)");
    checkNumberValidity(to_string(formId));
    if (command.size() == CLOSE_TA_FORM_VALID_NUMBER_OF_ARGUMENT)
    {
        data.showNumberOfTARequests(mainUserId, formId);
        while (data.thereIsStillTARequest(mainUserId, formId))
        {
            data.showStudentThatRequestedTA(mainUserId, formId);
            getline(cin, professorResponse);
            data.processOnProfessorResponse(professorResponse, mainUserId, formId);
        }
        data.deleteTAForm(mainUserId, formId);
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
    throw runtime_error(SUCCESSFUL_COMMAND);
}

void System::coursePost(vector<string> &command)
{
    checkNumberValidity("CommandKeyData(command, ID_INPUT)");
    int courseId = stoi("CommandKeyData(command, ID_INPUT)");
    if (command.size() == COURSE_POST_VALID_NUMBER_OF_ARGUMENT_ONE)
    {
        shared_ptr<SocialPost> newPost = make_shared<SocialPost>(data.getNewChannelPostId(courseId), mainUserId, "CommandKeyData(command, MESSAGE", EMPTY_STRING, "CommandKeyData(command, TITLE)");
        data.addPostToChannel(newPost, courseId, mainUserId);
        data.sendSystemNotificationToChannel(data.notifGenerator(NEW_COURSE_POST_NOTIF, to_string(courseId), false), stoi("CommandKeyData(command, ID_INPUT)"));
    }
    else if (command.size() == COURSE_POST_VALID_NUMBER_OF_ARGUMENT_TWO)
    {
        shared_ptr<SocialPost> newPost = make_shared<SocialPost>(data.getNewChannelPostId(courseId), mainUserId, "CommandKeyData(command, MESSAGE)", "CommandKeyData(command, IMAGE)", "CommandKeyData(command, TITLE)");
        data.addPostToChannel(newPost, courseId, mainUserId);
        data.sendSystemNotificationToChannel(data.notifGenerator(NEW_COURSE_POST_NOTIF, to_string(courseId), false), stoi("CommandKeyData(command, ID_INPUT)"));
    }
    else
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
    throw runtime_error(SUCCESSFUL_COMMAND);
}