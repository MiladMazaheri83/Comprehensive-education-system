#include "Account.hpp"

Account::Account(string Id, string name, int majorId) : Id(Id), name(name), majorId(majorId) {}
Account::~Account() {}

string Account::getAccountName() { return name; }
string Account::getAccountProfileImage() { return profileImagePath; }
string Account::getAccountId() { return Id; }
int Account::getAccountMajorId() { return majorId; }
list<int> Account::getAccountPosts() { return posts; }
list<string> Account::getAccountNotifications() { return notifications; }
vector<string> Account::getAccountFollowers() { return followersId; }
vector<string> Account::getAccountFollowings() { return followingsId; }
vector<int> Account::getAccountCourses() { return courses; }
vector<ClassTime> Account::getClassesTime() { return classesTime; }

void Account::addNotificationToCash(const string &notification)
{
    notifications.push_front(notification);
}

void Account::releasePost()
{
    posts.push_front(numberOfTotalReleasePosts);
}

void Account::makeEmptyNotificationList()
{
    notifications.clear();
}

void Account::deleteAccountPost(const int &postId)
{
    for (auto post = posts.begin(); post != posts.end();)
    {
        if (*post == postId)
        {
            post = posts.erase(post);
        }
        else
        {
            ++post;
        }
    }
}

void Account::deleteAccountCourse(const int &courseId)
{
    for (auto course = courses.begin(); course != courses.end();)
    {
        if (*course == courseId)
        {
            course = courses.erase(course);
        }
        else
        {
            ++course;
        }
    }
}

void Account::AddToFollow(string followId, bool isFollower)
{
    if (isFollower)
    {
        followersId.push_back(followId);
    }
    else
    {
        followingsId.push_back(followId);
    }
}

void Account::addClassTime(const ClassTime &time)
{
    classesTime.push_back(time);
}

void Account::addCourseToAccount(const int &courseId)
{
    courses.push_back(courseId);
}

void Account::setProfileImage(const string &imagePath)
{
    profileImagePath = imagePath;
}