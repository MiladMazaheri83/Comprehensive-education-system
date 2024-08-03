#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <string>
#include <vector>

const std::string NOT_ENTERED = "Unknown";
const std::string UT_PROFESSOR = "Professor";
const std::string UT_STUDENT = "Student";
const std::string UT_MANAGER = "UT_account";
const std::string SUCCESSFUL_COMMAND = "OK";
const std::string WHITESPACE = " ";
const std::string EMPTY_DATA = "Empty";
const std::string ABSENCE_DATA = "Not Found";
const std::string INCORRECT_REQUEST = "Bad Request";
const std::string NOT_SUCCESSFUL_ACCESS = "Permission Denied";
const std::string ONLY_UNKNOWN_COMMAND = "login";
const std::vector<std::string> professorRanks = {"instructor", "assistant professor", "associate professor", "professor"};
const std::vector<std::string> Methods = {"POST", "PUT", "DELETE", "GET"};
const std::vector<std::string> WeekDays = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};
const std::vector<std::string> professorCommands = {
    "logout",
    "courses",
    "post",
    "personal_page",
    "connect",
    "notification",
    "profile_photo",
    "course_post",
    "course_channel",
    "course_post",
    "ta_form",
    "close_ta_form"};
const std::vector<std::string> studentCommands = {
    "logout",
    "courses",
    "post",
    "personal_page",
    "connect",
    "notification",
    "profile_photo",
    "my_courses",
    "course_post",
    "course_channel",
    "course_post",
    "ta_request"};
const std::vector<std::string> UTManagerCommands = {"logout", "post", "course_offer", "profile_photo"};
const std::vector<std::string> ALL_COMMAND = {
    "POST login",
    "POST logout",
    "GET courses",
    "POST post",
    "DELETE post",
    "GET personal_page",
    "GET post",
    "POST connect",
    "GET notification",
    "POST course_offer",
    "PUT my_courses",
    "DELETE my_courses",
    "GET my_courses",
    "POST profile_photo",
    "POST course_post",
    "GET course_channel",
    "GET course_post",
    "POST ta_form",
    "POST close_ta_form",
    "POST ta_request"};

#endif // DEFINE_HPP