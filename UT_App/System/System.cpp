#include "System.hpp"

System::System(char *filesPath[]) : data(filesPath) {}

void checkNumberValidity(string Number)
{
    if (stoi(Number) < ZERO)
        throw runtime_error(INCORRECT_REQUEST);
    float Number_float = stof(Number);
    int Number_int = stoi(Number);
    if (Number_float > Number_int)
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
}

void System::checkEnterPermission(const string &Id, const string &password, const string &userState)
{
    if (!data.checkPassword(Id, password, userState))
    {
        mainUser = NOT_ENTERED;
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
}