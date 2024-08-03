#include "UT_manager.hpp"

UT_manager::UT_manager(string managerId, string managerName, string managerPassword)
    : ManagerId(managerId), ManagerName(managerName), ManagerPassword(managerPassword) {}

UT_manager::~UT_manager() {}

bool UT_manager::authenticate(const string &password)
{
    if (ManagerPassword == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string UT_manager::getManagerId() { return ManagerId; }
list<int> UT_manager::getManagerPosts() { return ManagerPosts; }
string UT_manager::getUTManagerName() { return ManagerName; }
void UT_manager::releasePost()
{
    numberOfTotalReleasePosts++;
    ManagerPosts.push_front(numberOfTotalReleasePosts);
}

void UT_manager::setProfile(const string &imagePath)
{
    profileImagePath = imagePath;
}

string UT_manager::getProfileImagePath()
{
    return profileImagePath;
}