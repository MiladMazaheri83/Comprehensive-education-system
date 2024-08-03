#include "Data.hpp"
#include <iostream>

Data::Data(char *filesPath[]) : MAJORS_FILE(filesPath[MAJOR_PATH_INDEX]), STUDENT_FILE(filesPath[STUDENT_PATH_INDEX]), COURSES_FILE(filesPath[COURSE_PATH_INDEX]), PROFESSORS_FILE(filesPath[PROFESSOR_PATH_INDEX])
{
    initializeUT_managersData();
    initializeMajorData();
    initializeLessonsData();
    initializeStudentData();
    initializeProfessorData();
}

Data::~Data() {}

void Data::initializeUT_managersData()
{
    auto main_Manager = make_unique<UT_manager>(UT_MANAGER_DEFAULT_ID, UT_MANAGER_NAME, UT_MANAGER);
    managers.push_back(move(main_Manager));
}

void Data::initializeMajorData()
{
    vector<vector<string>> MajorGrid = MAJORS_FILE.getDataTable();
    for (const vector<string> &ROW : MajorGrid)
    {
        Major major = {stoi(ROW[MID_INDEX]), ROW[MAJOR_NAME_INDEX]};
        majors.push_back(major);
    }
}

void Data::initializeStudentData()
{
    vector<vector<string>> studentGrid = STUDENT_FILE.getDataTable();
    for (const vector<string> &ROW : studentGrid)
    {
        auto student = make_unique<Student>(ROW[SID_INDEX], ROW[STUDENT_NAME_INDEX], stoi(ROW[STUDENT_MAJOR_ID_INDEX]), stoi(ROW[STUDENT_SEMESTER_INDEX]));
        accounts.push_back(move(student));
    }
}

void Data::initializeProfessorData()
{
    vector<vector<string>> professorGrid = PROFESSORS_FILE.getDataTable();
    for (const vector<string> &ROW : professorGrid)
    {
        for (const string &position : professorRanks)
        {
            if (ROW[PROFESSOR_POSITION_INDEX] == position)
            {
                auto professor = make_unique<Professor>(ROW[PID_INDEX], ROW[PROFESSOR_NAME_INDEX], stoi(ROW[PROFESSOR_MAJOR_ID_INDEX]), ROW[PROFESSOR_POSITION_INDEX]);
                accounts.push_back(move(professor));
            }
        }
    }
}

void Data::initializeLessonsData()
{
    vector<vector<string>> courseGrid = COURSES_FILE.getDataTable();
    for (const vector<string> &ROW : courseGrid)
    {
        Lesson lesson = {stoi(ROW[CID_INDEX]), ROW[COURSE_NAME_INDEX], stoi(ROW[COURSE_CREDIT_INDEX]), stoi(ROW[COURSE_PREREQUESITE_INDEX])};
        vector<string> majorsidBuffer = splitString(ROW[COURSE_MAJORS_ID_INDEX], SEMICOLON_CHAR);
        for (auto &majorId : majorsidBuffer)
        {
            lesson.majorsId.push_back(stoi(majorId));
        }
        lessons.push_back(lesson);
    }
}

string Data::searchIdStatus(const string &Id)
{
    if (checkManagerExistence(Id))
    {
        return UT_MANAGER;
    }
    shared_ptr<Account> account = getAccountById(Id);
    if (account->getType() == UT_STUDENT)
    {
        return UT_STUDENT;
    }
    else
    {
        return UT_PROFESSOR;
    }
    return NOT_ENTERED;
}

bool Data::checkManagerExistence(const string &id)
{
    for (auto &manager : managers)
    {
        if (manager->getManagerId() == id)
            return true;
    }
    return false;
}

bool Data::checkPassword(const string &id, const string &password, const string &userState)
{
    if (userState == UT_STUDENT)
    {
        if (password == STUDENT_FILE.getData(id, PASSWORD_WORD))
            return true;
    }
    else if (userState == UT_PROFESSOR)
    {
        if (password == PROFESSORS_FILE.getData(id, PASSWORD_WORD))
            return true;
    }
    else if (userState == UT_MANAGER)
    {
        if (checkManagerPassword(id, password))
            return true;
    }
    return false;
}

bool Data::checkManagerPassword(const string &id, const string &password)
{
    for (auto &manager : managers)
    {
        if (manager->getManagerId() == id)
        {
            if (manager->authenticate(password))
            {
                return true;
            }
        }
    }
    return false;
}

void Data::sendSystemNotification(const string &notification, const string &mainUserId)
{
    if (checkManagerExistence(mainUserId))
    {
        sentToAll(notification);
    }
    else
    {
        sendToFollowers(notification, mainUserId);
    }
}

void Data::sendSystemNotificationToChannel(const string &notification, const int &courseId)
{
    shared_ptr<Course> course = getCourseById(courseId);
    for (const string &accountId : course->noticesChannel.membersId)
    {
        shared_ptr<Account> account = getAccountById(accountId);
        account->addNotificationToCash(notification);
    }
}

void Data::sentToAll(const string &notification)
{
    for (auto &account : accounts)
    {
        account->addNotificationToCash(notification);
    }
}

void Data::sendToFollowers(const string &notification, const string &mainUserId)
{
    shared_ptr<Account> account = getAccountById(mainUserId);
    for (const string &Id : account->getAccountFollowings())
    {
        shared_ptr<Account> followingAccount = getAccountById(Id);
        followingAccount->addNotificationToCash(notification);
    }
    for (const string &Id : account->getAccountFollowers())
    {
        shared_ptr<Account> followerAccount = getAccountById(Id);
        followerAccount->addNotificationToCash(notification);
    }
}

string combineStrings(vector<string> stringList, string delimiter)
{
    string result;
    for (long unsigned int i = FIRST_ELEMENT_INDEX; i < stringList.size(); ++i)
    {
        result += stringList[i];
        if (i != stringList.size() - ONE_INDEX)
        {
            result += delimiter;
        }
    }
    return result;
}

shared_ptr<Account> Data::getAccountById(const string &Id)
{
    for (auto &account : accounts)
    {
        if (account->getAccountId() == Id)
        {
            return account;
        }
    }
    throw runtime_error(ABSENCE_DATA);
}

int Data::getNewPostId(const string &userId)
{
    long unsigned int newPostId;
    std::cout << userId << "\n\n\n\n\n\n\n";
    if (checkManagerExistence(userId))
    {
        for (auto &manager : managers)
        {
            if (manager->getManagerId() == userId)
            {
                newPostId = manager->numberOfTotalReleasePosts + MAKE_BIGEGER;
            }
        }
    }
    else
    {
        shared_ptr<Account> account = getAccountById(userId);
        newPostId = account->numberOfTotalReleasePosts + MAKE_BIGEGER;
    }
    return newPostId;
}

int Data::getNewChannelPostId(const int &courseId)
{
    shared_ptr<Course> course = getCourseById(courseId);
    return ((course->noticesChannel.numberOfreleasedPosts) + MAKE_BIGEGER);
}

void Data::addPost(shared_ptr<SocialPost> &newPost, const string &userId)
{
    if (checkManagerExistence(userId))
    {
        releaseManagerPost(userId);
        addPostToArchive(newPost);
    }
    else
    {
        shared_ptr<Account> account = getAccountById(userId);
        account->numberOfTotalReleasePosts++;
        account->releasePost();
        addPostToArchive(newPost);
    }
}

void Data::addPostToChannel(shared_ptr<SocialPost> &newPost, const int &courseId, const string &mainUserId)
{
    shared_ptr<Course> course = getCourseById(courseId);
    isCourseTA(courseId, mainUserId);
    course->noticesChannel.numberOfreleasedPosts++;
    course->noticesChannel.posts.push_front(move(newPost));
}

void Data::isCourseTA(const int &courseId, const string &mainUserId)
{
    bool flag = true;
    shared_ptr<Course> course = getCourseById(courseId);
    if (course->professorId == mainUserId)
    {
        flag = false;
    }
    for (const string &TA_id : course->allCourseTA_Id)
    {
        if (TA_id == mainUserId)
            flag = false;
    }
    if (flag)
    {
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
}

void Data::addPostToArchive(const shared_ptr<SocialPost> &newPost)
{
    posts.push_back(newPost);
}

void Data::addTAformToArchive(const shared_ptr<TA_formPost> &newPost)
{
    posts.push_back(newPost);
}

string Data::notifGenerator(const string &NEW, const string &Id, const bool &person)
{
    string Name;
    if (person)
    {
        findNotifAccountName(Name, Id);
    }
    else
    {
        findNotifCourseName(Name, stoi(Id));
    }

    return Id + WHITESPACE + Name + QOUT_MARK + WHITESPACE + NEW;
}

void Data::findNotifAccountName(string &name, const string &Id)
{
    if (checkManagerExistence(Id))
    {
        name = UT_MANAGER;
    }
    else
    {
        shared_ptr<Account> account = getAccountById(Id);
        name = account->getAccountName();
    }
}
void Data::findNotifCourseName(string &name, const int &Id)
{
    for (const shared_ptr<Course> &course : courses)
    {
        if (course->Id == Id)
        {
            name = course->name;
        }
    }
}

void Data::releaseManagerPost(const string &userId)
{
    for (auto &manager : managers)
    {
        if (manager->getManagerId() == userId)
        {
            manager->releasePost();
        }
    }
}

void Data::follow(const string &followerId, const string &userId)
{
    if (userId == followerId)
    {
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
    if (checkManagerExistence(userId))
    {
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
    shared_ptr<Account> account = getAccountById(userId);
    for (const string &followerAccountId : account->getAccountFollowers())
    {
        if (followerId == followerAccountId)
        {
            throw runtime_error(INCORRECT_REQUEST);
        }
    }
    account->AddToFollow(followerId, true);
}

void Data::addToMainUserFollowing(const string &followerId, const string &userId)
{
    shared_ptr<Account> account = getAccountById(followerId);
    account->AddToFollow(userId, false);
}

void Data::showPostData(const string &userId, const int &postId)
{
    checkPostExistance(userId, postId);
    showPostPublisherData(userId);
    printPost(userId, postId);
}

void Data::showChannelPostData(const int &courseId, const int &postId)
{
    checkChannelPostExistance(courseId, postId);
    showCourse(courseId);
    printChannelPost(courseId, postId, true);
}

string Data::printPost(const string &userId, const int &postId)
{
    string body;
    shared_ptr<Post> post = getPostByIds(postId, userId);
    if (SocialPost *socialPost = dynamic_cast<SocialPost *>(post.get()))
    {
        body += "<div class=\"post\">";
        if (socialPost->imagePath != "")
        {
            body += "<img src=\"" + socialPost->imagePath + "\" alt=\"" + socialPost->imagePath + "\" class=\"post-photo\">";
        }
        body += "<h2>" + socialPost->title + "</h2>";
        body += "<p>" + socialPost->message + "</p></div>";
    }
    if (TA_formPost *TAform = dynamic_cast<TA_formPost *>(post.get()))
    {
        shared_ptr<Course> course = getCourseById(TAform->courseId);
        cout << postId << WHITESPACE << TEXT_TA_POST_PART_ONE << course->name
             << WHITESPACE << COURSE << endl;
        showCourse(TAform->courseId);
        cout << DOUBLE_QOUTATION_OPEN << TAform->message << DOUBLE_QOUTATION_CLOSE << endl;
    }
    return body;
}

void Data::printChannelPost(const int &courseId, const int &postId, const bool botton)
{
    shared_ptr<Post> post = getChannelPostByIds(postId, courseId);
    shared_ptr<Account> account = getAccountById(post->userId);
    if (SocialPost *socialPost = dynamic_cast<SocialPost *>(post.get()))
    {
        if (botton)
            cout << postId << WHITESPACE << account->getAccountName() << WHITESPACE << DOUBLE_QOUTATION_OPEN
                 << socialPost->title << DOUBLE_QOUTATION_CLOSE << WHITESPACE << DOUBLE_QOUTATION_OPEN
                 << socialPost->message << DOUBLE_QOUTATION_CLOSE << endl;
        else
            cout << postId << WHITESPACE << account->getAccountName() << WHITESPACE << DOUBLE_QOUTATION_OPEN
                 << socialPost->title << DOUBLE_QOUTATION_CLOSE << endl;
    }
}

shared_ptr<Post> Data::getPostByIds(const int &postId, const string &userId)
{
    for (const shared_ptr<Post> &post : posts)
    {
        if ((post->userId == userId) && (post->getPostId() == postId))
        {
            return post;
        }
    }
    return nullptr;
}

shared_ptr<Post> Data::getChannelPostByIds(const int &postId, const int &courseId)
{
    shared_ptr<Course> course = getCourseById(courseId);
    for (const shared_ptr<Post> &post : course->noticesChannel.posts)
    {
        if ((post->getPostId() == postId))
        {
            return post;
        }
    }
    return nullptr;
}

void Data::checkPostExistance(const string &userId, const int &postId)
{
    shared_ptr<Post> post = getPostByIds(postId, userId);
    if (post == nullptr)
        throw runtime_error(ABSENCE_DATA);
}

void Data::checkChannelPostExistance(const int &courseId, const int &postId)
{
    shared_ptr<Post> post = getChannelPostByIds(postId, courseId);
    if (post == nullptr)
        throw runtime_error(ABSENCE_DATA);
}

string Data::getProfileImagePathe(const string id)
{
    if (checkManagerExistence(id))
    {
        for (auto &manager : managers)
        {
            if (manager->getManagerId() == id)
            {
                return manager->getProfileImagePath();
            }
        }
    }
    else
    {
        shared_ptr<Account> account = getAccountById(id);
        return account->getAccountProfileImage();
    }
    return EMPTY_STRING;
}

string Data::showPostPublisherData(const string &userId)
{
    string body = "";
    if (checkManagerExistence(userId))
    {
        body += "<img src=\"" + UT_MANAGER_PROFILE_PATH + "\" alt=\"Profile Photo\" class=\"profile-photo\" id=\"profile-photo\">";
        body += "<div class=\"personal-info\">";
        body += "<p>Manager ID: " + userId + "</p>";
        body += "<p>Name: " + UT_MANAGER + "</p>";
        body += "<p>Position: Manager</p></div>";
        return body;
    }
    else
    {
        shared_ptr<Account> account = getAccountById(userId);
        if (Student *student = dynamic_cast<Student *>(account.get()))
        {
            body += "<img src=\"" + student->getAccountProfileImage() + "\" alt=\"Profile Photo\" class=\"profile-photo\" id=\"profile-photo\">";
            body += "<div class=\"personal-info\">";
            body += "<p>User ID: " + userId + "</p>";
            body += "<p>Name: " + account->getAccountName() + "</p>";
            body += "<p>Major: " + findMajor(account->getAccountMajorId()) + "</p>";
            body += "<p>Credit: " + to_string(student->getSemester()) + "</p></div>";
            return body;
        }
        else if (Professor *professor = dynamic_cast<Professor *>(account.get()))
        {
            body += "<img src=\"" + professor->getAccountProfileImage() + "\" alt=\"Profile Photo\" class=\"profile-photo\" id=\"profile-photo\">";
            body += "<div class=\"personal-info\">";
            body += "<p>User ID: " + userId + "</p>";
            body += "<p>Name: " + account->getAccountName() + "</p>";
            body += "<p>Major: " + findMajor(account->getAccountMajorId()) + "</p>";
            body += "<p>Position: " + professor->getType() + "</p></div>";
            return body;
        }
    }
    return body;
}

string Data::findMajor(const int &majorId)
{
    for (Major &major : majors)
    {
        if (major.mid == majorId)
        {
            return major.majorName;
        }
    }
    return EMPTY_STRING;
}

string Data::nameOfCourses(const string &accountId)
{
    vector<string> coursesNames;
    shared_ptr<Account> account = getAccountById(accountId);
    for (int &courseId : account->getAccountCourses())
    {
        shared_ptr<Course> course = getCourseById(courseId);
        coursesNames.push_back(course->name);
    }
    return combineStrings(coursesNames, COMMA);
}

void Data::getNotification(const string &userId)
{
    shared_ptr<Account> account = getAccountById(userId);
    if (account->getAccountNotifications().size() == EMPTY)
    {
        throw runtime_error(EMPTY_DATA);
    }
    for (const string &notification : account->getAccountNotifications())
    {
        cout << notification << endl;
    }
    account->makeEmptyNotificationList();
}

string Data::getPageInfo(const string &userId)
{
    string body;
    body += showPostPublisherData(userId);
    body += printAllPosts(userId);
    return body;
}

void Data::getChannelInfo(const int &courseId)
{
    showCourse(courseId);
    printAllChannelPost(courseId);
}

string Data::printAllPosts(const string &userId)
{
    string body;
    if (checkManagerExistence(userId))
    {
        for (auto &manager : managers)
        {
            if (manager->getManagerId() == userId)
            {
                for (const int &postId : manager->getManagerPosts())
                {
                    body += printPost(userId, postId);
                }
            }
        }
    }
    else
    {
        shared_ptr<Account> account = getAccountById(userId);
        for (const int &postId : account->getAccountPosts())
        {
            body += printPost(userId, postId);
        }
    }
    return body;
}

void Data::printAllChannelPost(const int &courseId)
{
    shared_ptr<Course> course = getCourseById(courseId);
    for (shared_ptr<Post> &post : course->noticesChannel.posts)
    {
        printChannelPost(courseId, post->getPostId(), false);
    }
}
void Data::initializeCourseOfferData(shared_ptr<Course> &newCourse, const string &cid, const int &courseCapacity, const int &courseClassNumber)
{
    newCourse->Id = courses.size() + MAKE_BIGEGER;
    newCourse->credit = stoi(COURSES_FILE.getData(cid, CREDIT));
    newCourse->name = COURSES_FILE.getData(cid, NAME);
    newCourse->prerequisite = stoi(COURSES_FILE.getData(cid, PREREQUISITE));
    string majors = COURSES_FILE.getData(cid, MAJORS_ID);
    vector<string> majorsidBuffer = splitString(majors, SEMICOLON_CHAR);
    for (auto &majorId : majorsidBuffer)
    {
        newCourse->majorsId.push_back(stoi(majorId));
    }
    newCourse->capacity = courseCapacity;
    newCourse->classNumber = courseClassNumber;
}

void Data::assignProfessor(shared_ptr<Course> &newCourse, const string &professorId)
{
    shared_ptr<Account> account = getAccountById(professorId);
    if (account->getType() == UT_PROFESSOR)
    {
        if (checkMajorPermission(newCourse, professorId))
        {
            newCourse->professorName = account->getAccountName();
            newCourse->professorId = professorId;
            newCourse->noticesChannel.membersId.push_back(professorId);
        }
    }
    else
    {
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
}

bool Data::checkMajorPermission(const shared_ptr<Course> &course, const string &Id)
{
    shared_ptr<Account> account = getAccountById(Id);
    for (const int &major : course->majorsId)
    {
        if (major == account->getAccountMajorId())
        {
            return true;
        }
    }
    throw runtime_error(NOT_SUCCESSFUL_ACCESS);
}

void Data::setCourseTime(shared_ptr<Course> &course, const string &Id, const string &examDate, const string &classTime)
{
    shared_ptr<Account> account = getAccountById(Id);
    ClassTime referTime = makeClassTime(classTime);
    checkTimeInterference(account->getClassesTime(), referTime);
    course->time = classTime;
    course->examDate = examDate;
    account->addCourseToAccount(course->Id);
    account->addClassTime(referTime);
}

void Data::addCourseToArchive(const shared_ptr<Course> &course)
{
    courses.push_back(course);
}

shared_ptr<Course> Data::getCourseById(const int &courseId)
{
    for (const shared_ptr<Course> &course : courses)
    {
        if (course->Id == courseId)
        {
            return course;
        }
    }
    throw runtime_error(ABSENCE_DATA);
}

void checkTimeInterference(const vector<ClassTime> &classesTime, const ClassTime &referTime)
{
    checkDayValidity(referTime.day);
    for (const ClassTime &classTime : classesTime)
    {
        if (classTime.day == referTime.day)
        {
            if (classTime.startTime < referTime.startTime && classTime.endTime > referTime.startTime)
                throw runtime_error(NOT_SUCCESSFUL_ACCESS);
            if (classTime.startTime < referTime.endTime && classTime.endTime > referTime.endTime)
                throw runtime_error(NOT_SUCCESSFUL_ACCESS);
            if (classTime.endTime < referTime.endTime && classTime.endTime > referTime.startTime)
                throw runtime_error(NOT_SUCCESSFUL_ACCESS);
            if (classTime.startTime < referTime.endTime && classTime.startTime > referTime.startTime)
                throw runtime_error(NOT_SUCCESSFUL_ACCESS);
            if (classTime.startTime == referTime.startTime || classTime.endTime == referTime.endTime)
                throw runtime_error(NOT_SUCCESSFUL_ACCESS);
        }
    }
}

ClassTime makeClassTime(const string &time)
{
    ClassTime referTime;
    vector<string> buffer;
    buffer = splitString(time, QOUT_MARK_CHAR);
    referTime.day = buffer[FIRST_ELEMENT_INDEX];
    buffer = splitString(buffer[ONE_INDEX], DASH_CHAR);
    referTime.startTime = stoi(buffer[FIRST_ELEMENT_INDEX]);
    referTime.endTime = stoi(buffer[ONE_INDEX]);

    if ((referTime.startTime > referTime.endTime) || (referTime.startTime > DAY_HOURS || referTime.startTime < ZERO))
        throw runtime_error(INCORRECT_REQUEST);
    if (referTime.endTime > DAY_HOURS || referTime.endTime < ZERO)
        throw runtime_error(INCORRECT_REQUEST);

    return referTime;
}

void checkDayValidity(const string &dayName)
{
    bool flag = true;
    for (const string &day : WeekDays)
    {
        if (day == dayName)
        {
            flag = false;
        }
    }
    if (flag)
    {
        throw INCORRECT_REQUEST;
    }
}

string Data::showAllCourses()
{
    string courseData = EMPTY_STRING;
    for (const shared_ptr<Course> &course : courses)
    {
        courseData += R"(<div class="course-card"><div class="course-header"><span class="course-id">)";
        courseData += to_string(course->Id);
        courseData += R"(</span><span class="course-name">)";
        courseData += course->name;
        courseData += R"(</span></div><div class="course-data"><div class="course-details">
                            <strong>Exam Date:</strong>)";
        courseData += course->examDate;
        courseData += R"(</div><div class="course-details"><strong>Time:</strong>)";
        courseData += course->time;
        courseData += R"(</div><div class="course-details"><strong>Class Number:</strong>)";
        courseData += to_string(course->classNumber);
        courseData += R"(</div><div class="course-details"><strong>Capacity:</strong>)";
        courseData += to_string(course->capacity) + "</div></div></div>";
    }
    return courseData;
}

void Data::showCourse(const int &Id)
{
    shared_ptr<Course> course = getCourseById(Id);
    cout << course->Id << WHITESPACE << course->name << WHITESPACE << course->capacity
         << WHITESPACE << course->professorName << WHITESPACE << course->time << WHITESPACE << course->examDate
         << WHITESPACE << course->classNumber << endl;
}

void Data::courseRegister(const int &Id, const string &userId)
{
    shared_ptr<Course> course = getCourseById(Id);
    checkStudentRegisterationStatus(course, userId);
    course->studentsId.push_back(userId);
    course->noticesChannel.membersId.push_back(userId);
}

void Data::checkStudentRegisterationStatus(const shared_ptr<Course> &course, const string &Id)
{
    bool flag = true;
    shared_ptr<Account> account = getAccountById(Id);
    if (Student *student = dynamic_cast<Student *>(account.get()))
    {
        if (student->getSemester() < course->credit)
        {
            throw runtime_error(NOT_SUCCESSFUL_ACCESS);
        }
        for (const int &majorId : course->majorsId)
        {
            if (student->getAccountMajorId() == majorId)
                flag = false;
        }
        if (flag)
        {
            throw runtime_error(NOT_SUCCESSFUL_ACCESS);
        }
        ClassTime referTime = makeClassTime(course->time);
        checkTimeInterference(student->getClassesTime(), referTime);
        checkExamDate(student->getAccountCourses(), course->examDate);
        student->addCourseToAccount(course->Id);
        student->addClassTime(referTime);
    }
}

void Data::checkExamDate(const vector<int> coursesId, const string &examDate)
{
    for (const int &courseId : coursesId)
    {
        shared_ptr<Course> course = getCourseById(courseId);
        if (course->examDate == examDate)
        {
            throw runtime_error(NOT_SUCCESSFUL_ACCESS);
        }
    }
}

void Data::removePost(const string &Id, const int &postId)
{
    shared_ptr<Account> account = getAccountById(Id);
    account->deleteAccountPost(postId);
    deletePostFromArchive(postId);
}

void Data::removeCourse(const string &Id, const int &courseId)
{
    shared_ptr<Account> account = getAccountById(Id);
    account->deleteAccountCourse(courseId);
}

void Data::deletePostFromArchive(const int &postId)
{
    for (auto post = posts.begin(); post != posts.end();)
    {
        if ((*post)->getPostId() == postId)
        {
            post = posts.erase(post);
        }
        else
        {
            ++post;
        }
    }
}

string Data::getStudentsCoursesData(const string &mainUserId)
{
    string courseData = EMPTY_STRING;
    shared_ptr<Account> account = getAccountById(mainUserId);
    for (const int &courseId : account->getAccountCourses())
    {
        shared_ptr<Course> course = getCourseById(courseId);
        courseData += R"(<div class="course-card"><div class="course-header"><span class="course-id">)";
        courseData += to_string(course->Id);
        courseData += R"(</span><span class="course-name">)";
        courseData += course->name;
        courseData += R"(</span></div><div class="course-data"><div class="course-details">
                            <strong>Exam Date:</strong>)";
        courseData += course->examDate;
        courseData += R"(</div><div class="course-details"><strong>Time:</strong>)";
        courseData += course->time;
        courseData += R"(</div><div class="course-details"><strong>Class Number:</strong>)";
        courseData += to_string(course->classNumber);
        courseData += R"(</div><div class="course-details"><strong>Capacity:</strong>)";
        courseData += to_string(course->capacity) + "</div>";
        courseData += R"(</div></div>)";
    }
    return courseData;
}

void Data::addProfileToAccount(const string &userId, const string &imagePath)
{
    if (checkManagerExistence(userId))
    {
        for (auto &manager : managers)
        {
            if (manager->getManagerId() == userId)
                manager->setProfile(imagePath);
        }
    }
    else
    {
        shared_ptr<Account> account = getAccountById(userId);
        account->setProfileImage(imagePath);
    }
}

void Data::addTAform(const shared_ptr<TA_formPost> &newPost, const string &userId, const int &courseId)
{
    getCourseById(courseId);
    shared_ptr<Account> account = getAccountById(userId);
    if (account->getType() == UT_PROFESSOR)
    {
        account->numberOfTotalReleasePosts++;
        account->releasePost();
        addTAformToArchive(newPost);
        shared_ptr<TA_form> form = make_shared<TA_form>();
        form->form_id = newPost->getPostId();
        form->professorId = userId;
        form->courseId = courseId;
        TA_forms.push_back(move(form));
    }
}

void Data::requestTAform(const string &mainUserId, const string &professorId, const int &formId)
{
    shared_ptr<TA_form> form = getTAformById(professorId, formId);
    shared_ptr<Course> course = getCourseById(form->courseId);
    shared_ptr<Account> account = getAccountById(mainUserId);
    if (Student *student = dynamic_cast<Student *>(account.get()))
    {
        if (student->getSemester() < course->credit)
        {
            throw runtime_error(NOT_SUCCESSFUL_ACCESS);
        }
    }
    form->TARequest_studentId.push_back(mainUserId);
    course->noticesChannel.membersId.push_back(mainUserId);
}

shared_ptr<TA_form> Data::getTAformById(const string &userId, const int &formId)
{
    for (shared_ptr<TA_form> &form : TA_forms)
    {
        if (form->form_id == formId && form->professorId == userId)
        {
            return form;
        }
    }
    throw runtime_error(ABSENCE_DATA);
}

void Data::showNumberOfTARequests(const string &mainUserId, const int &formId)
{
    shared_ptr<TA_form> form = getTAformById(mainUserId, formId);
    cout << TEXT_CLOSE_TA_FORM_FIRST_PART << WHITESPACE << form->TARequest_studentId.size()
         << WHITESPACE << TEXT_CLOSE_TA_FORM_SECOND_PART << endl;
}

bool Data::thereIsStillTARequest(const string &mainUserId, const int &formId)
{
    shared_ptr<TA_form> form = getTAformById(mainUserId, formId);
    if (form->TARequest_studentId.size() != EMPTY)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Data::showStudentThatRequestedTA(const string &mainUserId, const int &formId)
{
    shared_ptr<TA_form> form = getTAformById(mainUserId, formId);
    auto id = form->TARequest_studentId.begin();
    advance(id, FIRST_ELEMENT_INDEX);
    string studentId = *id;
    shared_ptr<Account> account = getAccountById(studentId);
    if (Student *student = dynamic_cast<Student *>(account.get()))
    {
        cout << student->getAccountId() << WHITESPACE << student->getAccountName()
             << WHITESPACE << student->getSemester() << QOUT_MARK << WHITESPACE;
    }
}

void Data::processOnProfessorResponse(const string &professorResponse, const string &mainUserId, const int &formId)
{
    shared_ptr<TA_form> form = getTAformById(mainUserId, formId);
    shared_ptr<Course> course = getCourseById(form->courseId);
    auto id = form->TARequest_studentId.begin();
    advance(id, FIRST_ELEMENT_INDEX);
    string studentId = *id;
    shared_ptr<Account> account = getAccountById(studentId);
    if (professorResponse == ACCEPT)
    {
        auto id = form->TARequest_studentId.begin();
        advance(id, FIRST_ELEMENT_INDEX);
        string studentId = *id;
        course->allCourseTA_Id.push_back(studentId);
        form->TARequest_studentId.pop_front();
        account->addNotificationToCash(notifGenerator(ACCEPTED_NOTIF, to_string(form->courseId), false));
    }
    else if (professorResponse == REJECT)
    {
        form->TARequest_studentId.pop_front();
        account->addNotificationToCash(notifGenerator(REJECTED_NOTIF, to_string(form->courseId), false));
    }
}

void Data::deleteTAForm(const string &mainUserId, const int &formId)
{
    for (auto TA_form = TA_forms.begin(); TA_form != TA_forms.end();)
    {
        if ((*TA_form)->professorId == mainUserId && (*TA_form)->form_id == formId)
        {
            TA_form = TA_forms.erase(TA_form);
        }
        else
        {
            ++TA_form;
        }
    }
    shared_ptr<Account> account = getAccountById(mainUserId);
    account->deleteAccountPost(formId);
    deletePostFromArchive(formId);
}