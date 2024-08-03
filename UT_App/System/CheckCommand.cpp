#include "System.hpp"

void System::validateInputMethod(const string &methodInput)
{
    int flag = true;
    for (const string &method : Methods)
    {
        if (method == methodInput)
        {
            flag = false;
        }
    }
    if (flag)
    {
        throw runtime_error(INCORRECT_REQUEST);
    }
}

void System::validateCommandInput(const string &inputCommand)
{
    int flag = true;
    for (auto &command : ALL_COMMAND)
    {
        if (command == inputCommand)
        {
            flag = false;
        }
    }
    if (flag)
    {
        throw runtime_error(ABSENCE_DATA);
    }
}

void System::checkPermission(const string &inputCommand)
{
    if (mainUser == NOT_ENTERED)
    {
        unknownUserPermission(inputCommand);
    }
    else if (mainUser == UT_MANAGER)
    {
        checkUTManagerAccess(inputCommand);
    }
    else if (mainUser == UT_PROFESSOR)
    {
        checkProfessorPermission(inputCommand);
    }
    else if (mainUser == UT_STUDENT)
    {
        checkStudentPermission(inputCommand);
    }
}

void System::checkStudentPermission(const string &inputCommand)
{
    int flag = true;
    for (auto &command : studentCommands)
    {
        if (command == inputCommand)
        {
            flag = false;
        }
    }
    if (flag)
    {
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
}

void System::checkProfessorPermission(const string &inputCommand)
{
    int flag = true;
    for (auto &command : professorCommands)
    {
        if (command == inputCommand)
        {
            flag = false;
        }
    }
    if (flag)
    {
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
}

void System::checkUTManagerAccess(const string &inputCommand)
{
    int flag = true;
    for (auto &command : UTManagerCommands)
    {
        if (command == inputCommand)
        {
            flag = false;
        }
    }
    if (flag)
    {
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
}

void System::unknownUserPermission(const string &inputCommand)
{
    if (ONLY_UNKNOWN_COMMAND != inputCommand)
    {
        throw runtime_error(NOT_SUCCESSFUL_ACCESS);
    }
}