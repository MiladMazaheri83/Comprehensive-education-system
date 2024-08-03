#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>

#include "../UT_App/Server/server.hpp"
#include "../UT_App/System/System.hpp"

class LoginHandler : public RequestHandler
{
private:
    System *system;

public:
    LoginHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class LogoutHandler : public RequestHandler
{
private:
    System *system;

public:
    LogoutHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class PostHandler : public RequestHandler
{
private:
    System *system;
    Server *server;

public:
    PostHandler(System *system, Server *server) : system(system), server(server) {}
    void uploadPostImage(const string file, const string userId, string &imagePath);
    void addPost(const string imagePath, const string userId, const string title, const string message);
    Response *callback(Request *) override;
};

class OfferCourse : public RequestHandler
{
private:
    System *system;

public:
    OfferCourse(System *system) : system(system){}
    Response *callback(Request *) override;
};

class AddProfileHandler : public RequestHandler
{
private:
    System *system;
    Server *server;

public:
    AddProfileHandler(System *system, Server *server) : system(system), server(server) {}
    void uploadProfileImage(const string file, const string userId, string &imagePath);
    Response *callback(Request *) override;
};

class ChangeProfileHandler : public RequestHandler
{
private:
    System *system;

public:
    ChangeProfileHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class SendPostHandler : public RequestHandler
{
private:
    System *system;

public:
    SendPostHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class DeleteProfileHandler : public RequestHandler
{
private:
    System *system;

public:
    DeleteProfileHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class HomeHandler : public RequestHandler
{
private:
    System *system;

public:
    HomeHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class SearchHandler : public RequestHandler
{
private:
    System *system;

public:
    SearchHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class ShowCoursesHandler : public RequestHandler
{
private:
    System *system;

public:
    ShowCoursesHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class ShowMyCoursesHandler : public RequestHandler
{
private:
    System *system;

public:
    ShowMyCoursesHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class CourseOfferingHandler : public RequestHandler
{
private:
    System *system;

public:
    CourseOfferingHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class AddCourseHandler : public RequestHandler
{
private:
    System *system;

public:
    AddCourseHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

class DeleteCourseHandler : public RequestHandler
{
private:
    System *system;

public:
    DeleteCourseHandler(System *system) : system(system) {}
    Response *callback(Request *) override;
};

#endif // HANDLERS_HPP_INCLUDE