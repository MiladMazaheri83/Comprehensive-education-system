#ifndef DATA_HPP
#define DATA_HPP

#include <memory>
#include <vector>
#include "FileHandler.hpp"
#include "Post.hpp"
#include "Account.hpp"
#include "Professor.hpp"
#include "Student.hpp"
#include "UT_manager.hpp"
#include "Define.hpp"
#include "SocialPost.hpp"
#include "TA_formPost.hpp"
#include "DataDefine.hpp"

struct Major
{
    int mid;
    string majorName;
};

struct Channel
{
    int numberOfreleasedPosts = ZERO;
    list<shared_ptr<Post>> posts;
    vector<string> membersId;
};

struct Lesson
{
    int cid;
    string name;
    int credit;
    int prerequisite;
    vector<int> majorsId;
};

struct Course
{
    int Id;
    string name;
    string professorName;
    string professorId;
    int credit;
    int prerequisite;
    int classNumber;
    int capacity;
    vector<int> majorsId;
    string time;
    string examDate;
    Channel noticesChannel;
    mutable vector<string> studentsId;
    mutable vector<string> allCourseTA_Id;
};

struct TA_form
{
    int form_id;
    string professorId;
    int courseId;
    list<string> TARequest_studentId;
};

class Data
{
private:
    vector<Major> majors;
    vector<shared_ptr<Post>> posts;
    vector<shared_ptr<Course>> courses;
    vector<Lesson> lessons;
    vector<shared_ptr<TA_form>> TA_forms;
    vector<shared_ptr<Account>> accounts;
    vector<unique_ptr<UT_manager>> managers;
    FileHandler MAJORS_FILE;
    FileHandler STUDENT_FILE;
    FileHandler COURSES_FILE;
    FileHandler PROFESSORS_FILE;
    shared_ptr<Account> getAccountById(const string &Id);
    shared_ptr<Course> getCourseById(const int &courseId);
    shared_ptr<Post> getPostByIds(const int &postId, const string &userId);
    shared_ptr<Post> getChannelPostByIds(const int &postId, const int &courseId);
    shared_ptr<TA_form> getTAformById(const string &userId, const int &formId);
    string findMajor(const int &majorId);
    string nameOfCourses(const string &accountId);
    string printPost(const string &userId, const int &postId);
    void printChannelPost(const int &courseId, const int &postId, const bool botton);
    bool checkManagerExistence(const string &id);
    void initializeStudentData();
    void initializeProfessorData();
    void initializeMajorData();
    void initializeUT_managersData();
    void initializeLessonsData();
    void printAllChannelPost(const int &courseId);
    void releaseManagerPost(const string &userId);
    void checkPostExistance(const string &userId, const int &postId);
    void checkChannelPostExistance(const int &courseId, const int &postId);
    void sentToAll(const string &notification);
    void addPostToArchive(const shared_ptr<SocialPost> &newPost);
    void addTAformToArchive(const shared_ptr<TA_formPost> &newPost);
    void findNotifAccountName(string &name, const string &Id);
    void findNotifCourseName(string &name, const int &Id);
    void sendToFollowers(const string &notification, const string &mainUserId);
    void checkExamDate(const vector<int> coursesId, const string &examDate);
    void isCourseTA(const int &courseId, const string &mainUserId);
    bool checkMajorPermission(const shared_ptr<Course> &course, const string &Id);
    bool checkManagerPassword(const string &id, const string &password);

public:
    string searchIdStatus(const string &Id);
    string notifGenerator(const string &NEW, const string &Id, const bool &person);
    string printAllPosts(const string &userId);
    string showPostPublisherData(const string &userId);
    string getProfileImagePathe(const string id);
    string showAllCourses();
    string getStudentsCoursesData(const string &mainUserId);
    string getPageInfo(const string &userId);
    int getNewChannelPostId(const int &courseId);
    int getNewPostId(const string &userId);
    void removePost(const string &Id, const int &postId);
    void removeCourse(const string &Id, const int &courseId);
    void courseRegister(const int &Id, const string &userId);
    void showCourse(const int &Id);
    void addCourseToArchive(const shared_ptr<Course> &course);
    void checkStudentRegisterationStatus(const shared_ptr<Course> &course, const string &Id);
    void addProfileToAccount(const string &userId, const string &imagePath);
    void initializeCourseOfferData(shared_ptr<Course> &newCourse, const string &cid, const int &courseCapacity, const int &courseClassNumber);
    void getNotification(const string &userId);
    void showPostData(const string &userId, const int &postId);
    void showChannelPostData(const int &courseId, const int &postId);
    void getChannelInfo(const int &courseId);
    void setCourseTime(shared_ptr<Course> &course, const string &Id, const string &examDate, const string &classTime);
    void assignProfessor(shared_ptr<Course> &newCourse, const string &professorId);
    void follow(const string &followerId, const string &userId);
    void addToMainUserFollowing(const string &followerId, const string &userId);
    void addPost(shared_ptr<SocialPost> &newPost, const string &userId);
    void sendSystemNotification(const string &notification, const string &mainUserId);
    bool checkPassword(const string &id, const string &password, const string &userState);
    void deletePostFromArchive(const int &postId);
    void requestTAform(const string &mainUserId, const string &professorId, const int &formId);
    void addTAform(const shared_ptr<TA_formPost> &newPost, const string &userId, const int &courseId);
    void showNumberOfTARequests(const string &mainUserId, const int &formId);
    bool thereIsStillTARequest(const string &mainUserId, const int &formId);
    void showStudentThatRequestedTA(const string &mainUserId, const int &formId);
    void processOnProfessorResponse(const string &professorResponse, const string &mainUserId, const int &formId);
    void deleteTAForm(const string &mainUserId, const int &formId);
    void sendSystemNotificationToChannel(const string &notification, const int &courseId);
    void addPostToChannel(shared_ptr<SocialPost> &newPost, const int &courseId, const string &mainUserId);

    Data(char *filesPath[]);
    ~Data();
};

void checkTimeInterference(const vector<ClassTime> &classesTime, const ClassTime &referTime);
void checkDayValidity(const string &dayName);
ClassTime makeClassTime(const string &time);

#endif // DATA_HPP