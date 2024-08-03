#ifndef ACOUNT_HPP
#define ACOUNT_HPP

#include <string>
#include <vector>
#include <list>
#include <map>
#include <variant>
using namespace std;

const std::string NOT_ENTERED_IMAGE_PATH = "NOT_ENTERED.png";

struct ClassTime
{
    string day;
    int startTime;
    int endTime;
};

class Account
{
private:
    string Id;
    string name;
    string profileImagePath = NOT_ENTERED_IMAGE_PATH;
    int majorId;
    vector<int> courses;
    list<int> posts;
    vector<string> followersId;
    vector<string> followingsId;
    list<string> notifications;
    vector<ClassTime> classesTime;

public:
    long unsigned int numberOfTotalReleasePosts = 0;
    Account(string Id, string name, int majorId);
    virtual string getType() const = 0;
    virtual ~Account();
    void addNotificationToCash(const string &notification);
    void AddToFollow(string followId, bool isFollower);
    void deleteAccountCourse(const int &courseId);
    void deleteAccountPost(const int &postId);
    void setProfileImage(const string &imagePath);
    void makeEmptyNotificationList();
    string getAccountId();
    string getAccountName();
    string getAccountProfileImage();
    int getAccountMajorId();
    list<int> getAccountPosts();
    list<string> getAccountNotifications();
    vector<int> getAccountCourses();
    vector<string> getAccountFollowers();
    vector<string> getAccountFollowings();
    vector<ClassTime> getClassesTime();
    void addCourseToAccount(const int &courseId);
    void addClassTime(const ClassTime &time);
    void releasePost();
};

#endif // ACOUNT_HPP