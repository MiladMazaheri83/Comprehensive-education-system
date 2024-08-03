#include "handlers.hpp"
#include "handlerConst.hpp"
#include <filesystem>
namespace fs = std::filesystem;

#include <cstdlib>
#include <iostream>

Response *LoginHandler::callback(Request *req)
{
    Response *res = new Response();
    string guestCareer;
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    try
    {
        guestCareer = system->data.searchIdStatus(username);
        system->checkEnterPermission(username, password, guestCareer);
        system->mainUser = guestCareer;
        system->mainUserId = username;
        res = Response::redirect("/home");
        res->setSessionId(username);
        return res;
    }
    catch (const std::exception &e)
    {
        if (e.what() == NOT_SUCCESSFUL_ACCESS)
        {
            res = Response::redirect("/notAccess");
        }
        if (e.what() == ABSENCE_DATA)
        {
            res = Response::redirect("/notFound");
        }
        res->setSessionId(NOT_ENTERED);
        return res;
    }
}

Response *LogoutHandler::callback(Request *req)
{
    system->logout();
    Response *res = Response::redirect("/");
    res->setSessionId(NOT_ENTERED);
    return res;
}

Response *HomeHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string HomeBody;
    if (system->mainUser != NOT_ENTERED)
    {
        HomeBody += HOMEPAGE_1;
        if (system->mainUser == UT_STUDENT)
        {
            HomeBody += R"(<li><a href="/myCourses" id="my-courses-link">My Courses</a></li>)";
        }
        if (system->mainUser == UT_MANAGER)
        {
            HomeBody += R"(<li><a href="/offerCourse" id="offer-course-link">Add Course</a></li>)";
        }
        HomeBody += HOMEPAGE_2;
        HomeBody += system->personalPage(system->mainUserId);
        HomeBody += HOMEPAGE_3;
        res->setBody(HomeBody);
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *SearchHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    string pageBody;
    string userId;
    string personalInfo;
    try
    {
        userId = req->getQueryParam("query");
        personalInfo = system->personalPage(userId);
    }
    catch (const std::exception &e)
    {
        if (e.what() == ABSENCE_DATA)
        {
            res = Response::redirect("/notFound");
        }
    }

    if (system->mainUser != NOT_ENTERED)
    {
        pageBody += HOMEPAGE_1;
        if (system->mainUser == UT_STUDENT)
        {
            pageBody += R"(<li><a href="/home">Home</a></li>)";
            pageBody += R"(<li><a href="/myCourses" id="my-courses-link">My Courses</a></li>)";
        }
        if (system->mainUser == UT_MANAGER)
        {
            pageBody += R"(<li><a href="/home">Home</a></li>)";
            pageBody += R"(<li><a href="/offerCourse" id="offer-course-link">Add Course</a></li>)";
        }
        pageBody += HOMEPAGE_2;
        pageBody += personalInfo;
        pageBody += HOMEPAGE_3;
        res->setBody(pageBody);
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *ChangeProfileHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    if (system->mainUser != NOT_ENTERED)
    {
        body += CHANGE_PROFILE_BOX_1;
        body += R"(<img id="profile-photo" src=")" + system->data.getProfileImagePathe(system->mainUserId);
        body += R"(" alt="Profile Photo">)";
        body += CHANGE_PROFILE_BOX_2 + CHANGE_PROFILE_BOX_3 + CHANGE_PROFILE_BOX_4;
        res->setBody(body);
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *SendPostHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    if (system->mainUser != NOT_ENTERED)
    {
        body += POST_BOX;
        res->setBody(body);
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *PostHandler::callback(Request *req)
{
    Response *res = new Response();
    if (system->mainUser != NOT_ENTERED)
    {
        string file = EMPTY_STRING;
        string imagePath = EMPTY_STRING;
        string title = req->getBodyParam("title");
        string message = req->getBodyParam("message");
        string userId = system->mainUserId;
        file = req->getBodyParam("image");
        if (file != EMPTY_STRING)
        {
            uploadPostImage(file, userId, imagePath);
        }
        addPost(imagePath, userId, title, message);
        res = Response::redirect("/home");
        return res;
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *OfferCourse::callback(Request *req)
{
    Response *res = new Response();
    if (system->mainUser != NOT_ENTERED)
    {
        const int courseCapacity = stoi(req->getBodyParam("capacity"));
        const int courseClassNumber = stoi(req->getBodyParam("classNumber"));
        const string courseId = req->getBodyParam("courseId");
        const string professorId = req->getBodyParam("professorId");
        const string examData = req->getBodyParam("examDate");
        const string time = req->getBodyParam("day") + ":" + req->getBodyParam("Time");
        try
        {
            system->courseOffer(courseCapacity, courseClassNumber, courseId, professorId, examData, time);
            res = Response::redirect("/home");
            return res;
        }
        catch (const std::exception &e)
        {
            if (e.what() == INCORRECT_REQUEST)
            {
                res = Response::redirect("/offerCourse");
            }
            if (e.what() == NOT_SUCCESSFUL_ACCESS)
            {
                res = Response::redirect("/notAccess");
            }
            if (e.what() == ABSENCE_DATA)
            {
                res = Response::redirect("/notFound");
            }
            return res;
        }
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *DeleteProfileHandler::callback(Request *req)
{
    Response *res = new Response();
    if (system->mainUser != NOT_ENTERED)
    {
        system->profilePhoto(NOT_ENTERED_IMAGE_PATH);
        res = Response::redirect("/home");
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *AddProfileHandler::callback(Request *req)
{
    Response *res = new Response();
    if (system->mainUser != NOT_ENTERED)
    {
        string imagePath = EMPTY_STRING;
        string file = req->getBodyParam("image");
        uploadProfileImage(file, system->mainUserId, imagePath);
        system->profilePhoto(imagePath);
        res = Response::redirect("/home");
        return res;
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

void PostHandler::uploadPostImage(const string file, const string userId, string &imagePath)
{
    imagePath = "/images/userId=" + system->mainUserId + "-postId=" + to_string(system->data.getNewPostId(userId));
    string image_loc = "/userId=" + system->mainUserId + "-postId=" + to_string(system->data.getNewPostId(userId));
    fs::path outputPath = fs::current_path() / "images";
    fs::create_directories(outputPath);
    outputPath += image_loc;
    utils::writeToFile(file, outputPath);
    server->get(imagePath, new ShowImage(outputPath));
}

void AddProfileHandler::uploadProfileImage(const string file, const string userId, string &imagePath)
{
    imagePath = "/images/userId=" + system->mainUserId;
    string image_loc = "/userId=" + system->mainUserId;
    fs::path outputPath = fs::current_path() / "images";
    fs::create_directories(outputPath);
    outputPath += image_loc;
    utils::writeToFile(file, outputPath);
    server->get(imagePath, new ShowImage(outputPath));
}

void PostHandler::addPost(const string imagePath, const string userId, const string title, const string message)
{
    int newPostId = system->data.getNewPostId(userId);
    shared_ptr<SocialPost> newPost = make_shared<SocialPost>(newPostId, system->mainUserId, message, imagePath, title);
    system->data.addPost(newPost, system->mainUserId);
}

Response *ShowCoursesHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    if (system->mainUser != NOT_ENTERED)
    {
        body += SHOW_COURSE_PAGE_1;
        body += system->data.showAllCourses();
        body += SHOW_COURSE_PAGE_2;
        res->setBody(body);
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *ShowMyCoursesHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    if (system->mainUser != NOT_ENTERED)
    {
        body += MY_COURSE_PAGE_1;
        body += system->data.getProfileImagePathe(system->mainUserId);
        body += MY_COURSE_PAGE_2;
        body += system->getMyCourses(system->mainUserId);
        body += MY_COURSE_PAGE_3;
        res->setBody(body);
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *CourseOfferingHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    if (system->mainUser != NOT_ENTERED)
    {
        body += COURSE_OFFER_1;
        body += COURSE_OFFER_2;
        body += COURSE_OFFER_3;
        res->setBody(body);
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *AddCourseHandler::callback(Request *req)
{
    Response *res = new Response();
    if (system->mainUser != NOT_ENTERED)
    {
        const int courseId = stoi(req->getBodyParam("courseId"));
        try
        {
            system->myCourses(courseId);
            res = Response::redirect("/myCourses");
            return res;
        }
        catch (const std::exception &e)
        {
            if (e.what() == INCORRECT_REQUEST)
            {
                res = Response::redirect("/myCourses");
            }
            if (e.what() == NOT_SUCCESSFUL_ACCESS)
            {
                res = Response::redirect("/notAccess");
            }
            if (e.what() == ABSENCE_DATA)
            {
                res = Response::redirect("/notFound");
            }
            return res;
        }
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}

Response *DeleteCourseHandler::callback(Request *req)
{
    Response *res = new Response();
    if (system->mainUser != NOT_ENTERED)
    {
        const int courseId = stoi(req->getBodyParam("courseId"));
        try
        {
            system->deleteCourse(courseId);
            res = Response::redirect("/myCourses");
            return res;
        }
        catch (const std::exception &e)
        {
            if (e.what() == INCORRECT_REQUEST)
            {
                res = Response::redirect("/myCourses");
            }
            if (e.what() == NOT_SUCCESSFUL_ACCESS)
            {
                res = Response::redirect("/notAccess");
            }
            if (e.what() == ABSENCE_DATA)
            {
                res = Response::redirect("/notFound");
            }
            return res;
        }
    }
    else
    {
        res = Response::redirect("/notAccess");
    }
    return res;
}