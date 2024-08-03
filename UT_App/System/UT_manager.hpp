#ifndef UTMANAGER_HPP
#define UTMANAGER_HPP

#include <string>
#include <vector>
#include <list>
using namespace std;

class UT_manager
{
private:
    string ManagerId;
    string ManagerName;
    string ManagerPassword;
    string profileImagePath = "UT_Mark.png";
    list<int> ManagerPosts;

public:
    long unsigned int numberOfTotalReleasePosts = 0;
    UT_manager(string managerId, string managerName, string managerPassword);
    ~UT_manager();
    bool authenticate(const string &password);
    void setProfile(const string &imagePath);
    string getManagerId();
    string getUTManagerName();
    string getProfileImagePath();
    void releasePost();
    list<int> getManagerPosts();
};

#endif // UTMANAGER_HPP