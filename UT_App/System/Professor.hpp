#ifndef PROFESSOR_HPP
#define PROFESSPOR_HPP

#include "Account.hpp"

class Professor : public Account
{
private:
    string position;
    vector<int> TA_formId;

public:
    Professor(string Id, string name, int majorId, string position);
    ~Professor();
    string getType() const override {return "Professor";}
    string getPosition(){return position;}
    void setProfessorPosition(const string &rank);
};

#endif // PROFESSOR_HPP