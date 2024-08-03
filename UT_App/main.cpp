#include "./System/System.hpp"
#include "./Server/server.hpp"
#include "../utils/handlers.hpp"

const int PORT = 8080;

void mapServerPaths(Server &server, System &system)
{
    server.setNotFoundErrPage("static/404.html");
    server.get("/view.png", new ShowImage("static/view.png"));
    server.get("/UT_Mark.png", new ShowImage("static/UT_Mark.png"));
    server.get("/NOT_ENTERED.png", new ShowImage("static/NOT_ENTERED.png"));
    server.get("/UT.jpg", new ShowImage("static/UT.jpg"));
    server.get("/", new ShowPage("static/login.html"));
    server.get("/notFound", new ShowPage("static/notFound.html"));
    server.get("/notAccess", new ShowPage("static/notAccess.html"));
    server.get("/home", new HomeHandler(&system));
    server.post("/DeleteProfile", new DeleteProfileHandler(&system));
    server.get("/ChangeProfile", new ChangeProfileHandler(&system));
    server.get("/ShowCourses", new ShowCoursesHandler(&system));
    server.get("/myCourses", new ShowMyCoursesHandler(&system));
    server.get("/search", new SearchHandler(&system));
    server.post("/AddCourse", new AddCourseHandler(&system));
    server.post("/DeleteCourse", new DeleteCourseHandler(&system));
    server.get("/offerCourse", new CourseOfferingHandler(&system));
    server.post("/login", new LoginHandler(&system));
    server.post("/offerNewCourse", new OfferCourse(&system));
    server.post("/logout", new LogoutHandler(&system));
    server.post("/CreatePost", new PostHandler(&system, &server));
    server.post("/addProfile", new AddProfileHandler(&system, &server));
    server.get("/Post", new SendPostHandler(&system));
}

int main(int argc, char *filesPath[])
{
    System system(filesPath);
    try
    {
        Server server(PORT);
        mapServerPaths(server, system);
        std::cout << "Server running on port: " << PORT << std::endl;
        server.run();
    }
    catch (const invalid_argument &e)
    {
        cout << INCORRECT_REQUEST << endl;
    }
    catch (const Server::Exception &error)
    {
        cerr << error.getMessage() << endl;
    }
    return 0;
}